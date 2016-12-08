#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_
#include <opencv2/imgproc/imgproc.hpp>


class GrayImage : public cv::Mat{
public:
	GrayImage():cv::Mat(){}

	GrayImage(const cv::Mat& mat){
		if(mat.channels() != 1){
			cv::cvtColor(mat, *this, CV_BGR2GRAY);
		}else{
			mat.copyTo(*this);
		}

	}

};


class ColorImage : public cv::Mat{
public:
	
	ColorImage():cv::Mat(){}
	ColorImage(const cv::Mat& mat){
		if(mat.channels() != 3){
			cv::cvtColor(mat, *this, CV_GRAY2BGR);
		}else{
			mat.copyTo(*this);
		}

	}
};


#endif