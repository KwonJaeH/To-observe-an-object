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

	/***************************    Variable  ****************************/

	// haar 파일 불러오기
	CascadeClassifier face_cascade;	 // face
	
	// Webcam
	VideoCapture cap(0);
	Mat frame;

	// Haar Cascade
	vector<Rect> faces; //직사각형의 벡터 (x, y, width, height)
	Mat frame_gray;

	int width;	
	int height;	

#define GO 3
#define BACK -3

#define RIGHT 1
#define LEFT -1
#define UP 2
#define DOWN -2
#define STAY 0

	// first 'center' coordinate, area of face
	int org_x, org_y, org_area;
	// currnet 'center' coordinate, area of face
	int current_x, current_y, current_area;

	const int moveThreshold = 10;
	const int areaThreshold = 12000;
	const double maximumDist = 50.0;



	/***************************   Function  ****************************/
	// init camera settings
	void init_Func();
	// if not open, then return true;
	bool openCheck();
	// show current image
	void readFrame();
	// read current frame
	void showImage();
	// if finish, then return true
	bool turnOff();
	// draw window for setting 
	void drawSettingWindow();
	// check setting finished
	bool SettingisFinished();
	// set original(first) face coordinate
	void setOrgFacePos();

	// return distance between before and current boxes
	double dist(int x, int y);
	// extract face and eye in frame
	void extract_face();
	// return degree of movement
	float returnMoveDegreeXYZ(int status);
	// detect movement each direction
	int isDetectedFaceMovement_direct_of_X();
	int isDetectedFaceMovement_direct_of_Y();
	int isDetectedFaceMovement_direct_of_Z();
	

	void init_Func() {
		// load file
		face_cascade.load("C:/OpenCV_test/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml");

		width = cap.get(CAP_PROP_FRAME_WIDTH); // 웹캠의 width 받기
		height = cap.get(CAP_PROP_FRAME_HEIGHT); // 웹캠의 height 받기

		cap.set(CAP_PROP_FRAME_WIDTH, width);
		cap.set(CAP_PROP_FRAME_HEIGHT, height);
	}

	bool openCheck() {
		return !cap.isOpened();
	}

	void readFrame() {
		cap.read(frame);

		// 직관적인 계산위해 화면 거울모드
		flip(frame, frame, 1);

		if (frame.empty())
		{
			printf("frame empty\n");
			return;
		}
	}
	void showImage() {
		imshow("Ready", frame);
	}

	bool turnOff() {
		int key = waitKey(1);
		if (key == 27)
			return true;
		return false;
	}

	void drawSettingWindow() {
		moveWindow("Ready", 400, 150);
	}

	bool SettingisFinished() {
		int key = waitKey(1);
		if (key == 13)
			return true;
		return false;
	}

	void setOrgFacePos() {
		org_x = current_x;
		org_y = current_y;
		org_area = current_area;
	}


	double dist(int x, int y) {
		return sqrt(pow((current_x - x, 2), 2) + pow((current_y - y, 2), 2));
	}

	void extract_face() {

		cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
		equalizeHist(frame_gray, frame_gray);

		face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(50, 50));
		
		// public void detectMultiScale(Mat image, MatOfRect objects, double scaleFactor, int minNeighbors, int flags, Size minSize)
		// image : 카메라에서 가져온 프레임을 가공하여 검출하고자 하는 대상이 있는 확인하기 위한 원본 이미지
		// objects : 검출된 객체를 포함한 직사각형의 벡터
		// scaleFactor : 이미지 피라미드에서 사용되는 scale 계수 값(여러 scale로 만들어서 찾음)
		// minNeighbors : 이미지 피라미드에서 슬라이딩 윈도우가 대상을 검출한 횟수가 지정한 값 이상이면 유효
		// flags :  구 버전 OpenCV에서 필요
		// minSize : 검출하려는 이미지의 최소 사이즈로 해당 값보다 작으면 무시

		for (size_t i = 0; i < faces.size(); i++)
		{
			rectangle(frame, faces[i], Scalar(0, 255, 0), 2, 8, 0);
			int now_x = faces[i].x + faces[i].width / 2;
			int now_y = faces[i].y + faces[i].height / 2;
			if (maximumDist > dist(now_x, now_y)) {
				current_x = now_x;
				current_y = now_y;
				current_area = faces[i].width * faces[i].height;
			}
		}
	}

	float returnMoveDegreeXYZ(int status) {
		float movedegree = 0;
		switch (status) {
		case RIGHT: case LEFT:
			movedegree = (float)abs(current_x - org_x) / moveThreshold;
			org_x = current_x;
			break;
		case UP: case DOWN:
			movedegree = (float)abs(current_y - org_y) / moveThreshold;
			org_y = current_y;
			break;
		case GO:case BACK:
			movedegree = (float)abs(current_area - org_area) / areaThreshold;
			org_area = current_area;
			break;
		}
		return movedegree;
	}

	int isDetectedFaceMovement_direct_of_X() {
		if (org_x + moveThreshold < current_x)
			return RIGHT;
		if (org_x - moveThreshold > current_x)
			return LEFT;
		return STAY;
	}

	int isDetectedFaceMovement_direct_of_Y() {
		if (org_y + moveThreshold < current_y)
			return DOWN;
		if (org_y - moveThreshold > current_y)
			return UP;
		return STAY;
	}


	int isDetectedFaceMovement_direct_of_Z() {
		if (org_area + areaThreshold < current_area) 
			return GO;	
		if (org_area - areaThreshold > current_area) 
			return BACK;
		return STAY;
	}

}
