#include "cv_camera.h"
using namespace camera;

int main()
{
	

	camera::init_CameraFunc();

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

		// finish check
		if (camera::turnOff()) {
			break;
		}
		
	}
	return 0;
}