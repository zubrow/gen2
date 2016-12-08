#ifndef _IMAGE_LOADER_HPP_
#define _IMAGE_LOADER_HPP_

#include <archi/Provider.hpp>
#include <data/Image.hpp>

class ImageLoader : public Provider<ColorImage>{
	private: 
		std::string m_name;
	public:
		ImageLoader(std::string name):Module(), m_name(name){}

		void run(){
			cv::Mat img = cv::imread(m_name);
			Provider<ColorImage>::set("output", img);
		}
};




#endif