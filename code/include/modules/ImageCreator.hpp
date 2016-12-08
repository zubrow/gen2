#ifndef _IMAGE_LOADER_HPP_
#define _IMAGE_LOADER_HPP_

#include <archi/Provider.hpp>
#include <archi/Receiver.hpp>
#include <data/Image.hpp>

class ImageCreator : public Receiver<Rectangle>, public Provider<ColorImage>{

	public:
		ImageLoader():Module(){}

		void run(){
			cv::Mat img = cv::imread(m_name);
			Provider<ColorImage>::set("output", img);
		}
};




#endif