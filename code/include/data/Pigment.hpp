#ifndef _PIGMENT_HPP_
#define _PIGMENT_HPP_

#include <opencv2/core/core.hpp>

class Pigment{
public:
	virtual operator cv::Vec3b()const =0;
	virtual operator uchar()const =0;
	virtual operator cv::Scalar()const =0;
};



class GrayPigment : public Pigment{
private:
	uchar value;
public:
	GrayPigment(uchar v):value(v){}
	virtual operator cv::Vec3b()const{
		return cv::Vec3b(value, value, value);
	}
	virtual operator uchar()const{
		return value;
	}
	virtual operator cv::Scalar()const{
		return cv::Scalar(value, value, value);
	}
};


class ColorPigment : public Pigment, public cv::Vec3b{

public:
	ColorPigment(uchar b, uchar g, uchar r):cv::Vec3b(b,g,r){}
	ColorPigment(uchar v):cv::Vec3b(v,v,v){}
	ColorPigment(cv::Vec3b vec):cv::Vec3b(vec){}
	virtual operator cv::Vec3b()const{
		return *this;
	}
	virtual operator uchar()const{
		return (*this)[0];
	}
	virtual operator cv::Scalar()const{
		return cv::Scalar((*this)[0], (*this)[1], (*this)[2]);
	}
};

#endif