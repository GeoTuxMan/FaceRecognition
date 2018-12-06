# FaceRecognition
face recognition application develop with C++, OpenCV

The application is trained with some images of a person (minim 2 image).

When you put your face on laptop camera, the application decice (this is realy Artificial Inlelligence !) alone, who is it on camera.

Step to run application:

1) select some images, and put them in a folder (Irina)
2) cd Irina
3) python crop_face.py
4) cd ..
5) create a file `csv.ext` :
/home/george/Desktop/C++/OpenCV/RecunoastereFaciala/Irina/irina1_20_20_70_70.jpg;0
/home/george/Desktop/C++/OpenCV/RecunoastereFaciala/Irina/irina2_20_20_70_70.jpg;0
/home/george/Desktop/C++/OpenCV/RecunoastereFaciala/Irina/irina3_20_20_70_70.jpg;0
/home/george/Desktop/C++/OpenCV/RecunoastereFaciala/Irina/irina5_20_20_70_70.jpg;0

5) g++ RecunoastereFaciala.cpp -o RecunoastereFaciala `pkg-config --cflags --libs opencv`
6) ./RecunoastereFaciala




