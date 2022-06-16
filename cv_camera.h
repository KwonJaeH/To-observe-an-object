#pragma once
#include <opencv2/objdetect.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <iostream>
using namespace cv;
using namespace std;

namespace camera {

	/***************************   Function  ****************************/
	// init camera settings
	void init_Func();
	// if not open, then return true;
	bool openCheck();

	// show current image
	void readFrame();

	// extract face and eye in frame
	void extract_face_and_eye();
	// read current frame
	void showImage();
	// if finish, then return true
	bool turnOff();



	/***************************    Variable  ****************************/

	// haar ���� �ҷ�����
	CascadeClassifier face_cascade;	 // face
	CascadeClassifier eye_cascade;  // eye

	// Webcam
	VideoCapture cap(0);
	Mat frame;

	// Haar Cascade ��ü
	vector<Rect> faces; // ����� ��ü�� ������ ���簢���� ���� (x, y, width, height)
	vector<Rect> eyes; 
	Mat frame_gray;

	int width;	
	int height;	



	void init_Func() {
		// file
		face_cascade.load("C:/OpenCV_test/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml");
		eye_cascade.load("C:/OpenCV_test/opencv/sources/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml");

		width = cap.get(CAP_PROP_FRAME_WIDTH); // ��ķ�� width �ޱ�
		height = cap.get(CAP_PROP_FRAME_HEIGHT); // ��ķ�� height �ޱ�

		cap.set(CAP_PROP_FRAME_WIDTH, width);
		cap.set(CAP_PROP_FRAME_HEIGHT, height);
	}

	bool openCheck() {
		return !cap.isOpened();
	}

	void readFrame() {
		cap.read(frame);

		if (frame.empty())
		{
			printf("frame empty\n");
			return;
		}
	}

	void extract_face_and_eye() {

		cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
		equalizeHist(frame_gray, frame_gray);

		face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(50, 50));
		//eye_cascade.detectMultiScale(frame_gray, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(50, 50));
		
		// public void detectMultiScale(Mat image, MatOfRect objects, double scaleFactor, int minNeighbors, int flags, Size minSize)
		// image : ī�޶󿡼� ������ �������� �����Ͽ� �����ϰ��� �ϴ� ����� �ִ� Ȯ���ϱ� ���� ���� �̹���
		// objects : ����� ��ü�� ������ ���簢���� ����
		// scaleFactor : �̹��� �Ƕ�̵忡�� ���Ǵ� scale ��� ��(���� scale�� ���� ã��)
		// minNeighbors : �̹��� �Ƕ�̵忡�� �����̵� �����찡 ����� ������ Ƚ���� ������ �� �̻��̸� ��ȿ
		// flags :  �� ���� OpenCV���� �ʿ�
		// minSize : �����Ϸ��� �̹����� �ּ� ������� �ش� ������ ������ ����

		for (size_t i = 0; i < faces.size(); i++)
		{
			rectangle(frame, faces[i], Scalar(0, 255, 0), 2, 8, 0);
		}


		/*for (size_t i = 0; i < eyes.size(); i++)
		{
			rectangle(frame, eyes[i], Scalar(0, 255, 255), 2, 8, 0);
		}*/
	}

	void showImage() {
		imshow("Result", frame);
	}

	bool turnOff() {
		int key = waitKey(1);
		if (key == 27)
			return true;
		return false;
	}
}
