#ifndef _IMAGE_DISPLAY_HPP_
#define _IMAGE_DISPLAY_HPP_

#include <archi/Receiver.hpp>
#include <data/Image.hpp>	

class ImageDisplay : public Receiver<ColorImage>{
	private:
		std::string m_windowName;
	public:
		ImageDisplay(std::string windowName):m_windowName(windowName){}
		void run(){
			ColorImage img = Receiver<ColorImage>::get("input");
			cv::imshow(m_windowName, img);

		}
};


#endif