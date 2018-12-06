# FaceRecognition
face recognition application develop with C++, OpenCV

The application is trained with some images of a person (minim 2 image).

When you put your face on laptop camera, the application decice (this is realy Artificial Inlelligence !) alone, who is it on camera.

Step to run application:

1) select some images, and put them in a folder (Irina)
2) cd Irina
3) python crop_face.py
4) cd ..
5) g++ RecunoastereFaciala.cpp -o RecunoastereFaciala `pkg-config --cflags --libs opencv`
6) ./RecunoastereFaciala




