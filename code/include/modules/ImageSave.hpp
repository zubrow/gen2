#ifndef _IMAGE_SAVE_HPP_
#define _IMAGE_SAVE_HPP_

#include <archi/Receiver.hpp>
#include <data/Image.hpp>
class ImageSave : public Receiver<ColorImage>{
	private:
		std::string m_fileName;
	public:
		ImageSave(std::string fileName):m_fileName(fileName){}
		void run(){
			ColorImage img = Receiver<ColorImage>::get("input");
			cv::imwrite(m_fileName, img);

		}
};

#endif