/*
 Gheorghe Sarbu, Ubuntu 18.04, g++
 */

#include "/usr/local/include/opencv2/core/core.hpp"
#include "/usr/local/include/opencv2/core.hpp"
#include "/usr/local/include/opencv2/highgui/highgui.hpp"
#include "/usr/local/include/opencv2/opencv.hpp"
#include "/usr/local/include/opencv2/imgcodecs.hpp"
#include "/usr/local/include/opencv2/imgproc.hpp"
#include "/usr/local/include/opencv2/objdetect.hpp"
#include "/usr/local/include/opencv2/face/facerec.hpp"
#include "/usr/local/include/opencv2/face.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace cv::face;
using namespace std;

static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

string g_listname_t[]= 
{
	
	
        "Irina"
};

int main(int argc, const char *argv[]) {
     
string fn_haar = "/opt/opencv/data/haarcascades/haarcascade_frontalface_default.xml";
    string fn_csv = "csv.ext";
    int deviceId = 0;			// laptop camera 
    vector<Mat> images;
    vector<int> labels;
    
    try {
        read_csv(fn_csv, images, labels);
    } catch (cv::Exception& e) {
        cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
        
        exit(1);
    }
    
    int im_width = images[0].cols;
    int im_height = images[0].rows;
    // Create a FaceRecognizer and train it on the given images:
    Ptr<FisherFaceRecognizer> model = FisherFaceRecognizer::create();
    model->train(images, labels);
    CascadeClassifier haar_cascade;
    haar_cascade.load(fn_haar);
    VideoCapture cap(deviceId);
    if(!cap.isOpened()) {
        cerr << "Capture Device ID " << deviceId << "cannot be opened." << endl;
        return -1;
    }
    // Holds the current frame from the Video device:
    Mat frame;
    for(;;) {
        cap >> frame;
        // Clone the current frame:
        Mat original = frame.clone();
        // Convert the current frame to grayscale:
        Mat gray;
        cvtColor(original, gray, CV_BGR2GRAY);
        // Find the faces in the frame:
        vector< Rect_<int> > faces;
        haar_cascade.detectMultiScale(gray, faces);
        
        for(int i = 0; i < faces.size(); i++) {
           
            Rect face_i = faces[i];
            // Crop the face from the image:
            Mat face = gray(face_i);
            Mat face_resized;
            cv::resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);
            int prediction = model->predict(face_resized);
            rectangle(original, face_i, CV_RGB(0, 255,0), 1);
            // Create the text we will annotate the box with:
            string box_text;
			box_text = format( "Prediction = " );
			// Get stringname
			if ( prediction >= 0 && prediction <=1 )
			{
				box_text.append( g_listname_t[prediction] );
			}
            else box_text.append( "Unknown" );
            int pos_x = std::max(face_i.tl().x - 10, 0);
            int pos_y = std::max(face_i.tl().y - 10, 0);
            putText(original, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 2.0);
        }
        
        imshow("face_recognizer", original);
        waitKey(10);
	char c = (char)waitKey(10);
	if( c == 27 || c == 'q' || c == 'Q' )
            break;
    }
    return 0;


}
