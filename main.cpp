#include "cv_camera.h"
#include "gl_object.h"
using namespace camera;
using namespace object;

int main()
{
	

	camera::init_Func();

	if (camera::openCheck()) {
		return -1;
	}

	while (true)
	{
		// read frame
		camera::readFrame();

		// extract face and draw ellipse
		camera::extract_face_and_eye();

		// show current frame
		camera::showImage();
		camera::drawSettingWindow();
		cout << camera::current_x << " , " << camera::current_y << "\n";
		// finish check
		if (camera::SettingisFinished()) {
			camera::setCurrentFacePos();
			break;
		}
		
	}

	object::init_Func();

	while (object::windowIsOpened()) {
		
		camera::readFrame();
		camera::showImage();

		object::animationLoop();

		camera::extract_face_and_eye();
		
		int status;

		status = camera::isDetectedFaceMovement_direct_of_X();
		if (status) {
			float move_x = camera::returnMoveDegree(status);
			object::updateFace_Position(move_x, status);
			object::updateCamera_Position(status);
		}

		status = camera::isDetectedFaceMovement_direct_of_Y();
		if (status) {
			float move_y = camera::returnMoveDegree(status);
			object::updateFace_Position(move_y, status);
			object::updateCamera_Position(status);
		}
		

		if (camera::turnOff()) {
			break;
		}
	}

	object::done();
	return 0;
}