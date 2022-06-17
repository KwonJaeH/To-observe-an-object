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
		camera::extract_face();

		// show current frame
		camera::showImage();
		camera::drawSettingWindow();
		
		// finish check
		if (camera::SettingisFinished()) {
			camera::setOrgFacePos();
			break;
		}
		
	}

	object::init_Func();

	while (object::windowIsOpened()) {
		
		// read frame
		camera::readFrame();
		
		// show current frmae
		camera::showImage();

		// drawanimation
		object::animationLoop();

		// extract face
		camera::extract_face();
		
		int status;

		status = camera::isDetectedFaceMovement_direct_of_X();
		if (status) {
			float move_x = camera::returnMoveDegreeXYZ(status);
			object::updateFace_Position_for_XYZ(move_x, status);

		}

		status = camera::isDetectedFaceMovement_direct_of_Y();
		if (status) {
			float move_y = camera::returnMoveDegreeXYZ(status);
			object::updateFace_Position_for_XYZ(move_y, status);
	
		}
		
		status = camera::isDetectedFaceMovement_direct_of_Z();
		if (status) {
			float move_z = camera::returnMoveDegreeXYZ(status);
			object::updateFace_Position_for_XYZ(move_z, status);
		}


		if (camera::turnOff()) {
			break;
		}
	}

	object::done();
	return 0;
}