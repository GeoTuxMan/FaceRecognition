import cv2
import sys
import numpy as np

# Numele persoanelor (labels)
g_listname_t = [
    "Irina"
]

def read_csv(filename, separator=';'):
    images = []
    labels = []
    try:
        with open(filename, 'r') as file:
            for line in file:
                line = line.strip()
                if line:
                    path, classlabel = line.split(separator)
                    if path and classlabel:
                        img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)
                        if img is not None:
                            images.append(img)
                            labels.append(int(classlabel))
                        else:
                            print(f"Warning: Image {path} not found or cannot be loaded")
    except Exception as e:
        print(f"Error reading csv file: {e}")
        sys.exit(1)
    return images, labels

def main():
    fn_haar = "/opt/opencv/data/haarcascades/haarcascade_frontalface_default.xml"
    fn_csv = "csv.ext"
    deviceId = 0

    images, labels = read_csv(fn_csv)

    if len(images) == 0 or len(labels) == 0:
        print("No images or labels found, exiting")
        sys.exit(1)

    im_width = images[0].shape[1]
    im_height = images[0].shape[0]

    # Create FisherFaceRecognizer
    model = cv2.face.FisherFaceRecognizer_create()
    model.train(images, np.array(labels))

    haar_cascade = cv2.CascadeClassifier(fn_haar)

    cap = cv2.VideoCapture(deviceId)
    if not cap.isOpened():
        print(f"Capture Device ID {deviceId} cannot be opened.")
        sys.exit(1)

    while True:
        ret, frame = cap.read()
        if not ret:
            print("Failed to capture frame")
            break

        original = frame.copy()
        gray = cv2.cvtColor(original, cv2.COLOR_BGR2GRAY)

        faces = haar_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5)

        for (x, y, w, h) in faces:
            face = gray[y:y+h, x:x+w]
            face_resized = cv2.resize(face, (im_width, im_height), interpolation=cv2.INTER_CUBIC)

            prediction, confidence = model.predict(face_resized)

            cv2.rectangle(original, (x, y), (x + w, y + h), (0, 255, 0), 1)

            if 0 <= prediction < len(g_listname_t):
                box_text = f"Prediction = {g_listname_t[prediction]}"
            else:
                box_text = "Prediction = Unknown"

            pos_x = max(x - 10, 0)
            pos_y = max(y - 10, 0)
            cv2.putText(original, box_text, (pos_x, pos_y), cv2.FONT_HERSHEY_PLAIN, 1.0, (0, 255, 0), 2)

        cv2.imshow("face_recognizer", original)

        c = cv2.waitKey(10)
        if c == 27 or c == ord('q') or c == ord('Q'):
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()

