#ifndef _IMAGE_INFOS_HPP_
#define _IMAGE_INFOS_HPP_

#include <archi/Receiver.hpp>
#include <data/Image.hpp>
#include <data/Geometry.hpp>


class ImageInfos : public Receiver<ColorImage>, public Provider<Rectangle>, public Provider<Size>{
	public:
		void run(){

		std::cout<<"image infos"<<std::endl;
			ColorImage img = Receiver<ColorImage>::get("input");
			Rectangle r(0,0, img.cols, img.rows);
			Provider<Rectangle>::set("domain", r);
			Size s(img.cols, img.rows);
			Provider<Size>::set("size", s);
		}

};


#endif