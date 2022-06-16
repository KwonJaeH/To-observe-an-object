//#include "cv_camera.h"
#include "gl_object.h"
//using namespace camera;
using namespace object;

int main()
{
	

	//camera::init_Func();

	//if (camera::openCheck()) {
	//	return -1;
	//}

	//while (true)
	//{
	//	// read frame
	//	camera::readFrame();

	//	// extract face and draw ellipse
	//	camera::extract_face_and_eye();

	//	// show current frame
	//	camera::showImage();

	//	// finish check
	//	if (camera::turnOff()) {
	//		break;
	//	}
	//	
	//}

	object::init_Func();

	while (object::windowIsOpened()) {
		object::animationLoop();
	}

	object::done();
	return 0;
}