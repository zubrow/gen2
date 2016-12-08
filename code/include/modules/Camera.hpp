#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_	
#include <archi/Provider.hpp>
#include <data/Image.hpp>	


class Camera : public Provider<ColorImage>{
	private: 
		cv::VideoCapture cap;
	public:
		Camera(int i):Module(){
			cap.open(i);
		}

		void run(){
			cv::Mat img;
			cap>>img;
			Provider<ColorImage>::set("output", img);
		}
};


#endif