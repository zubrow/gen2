#ifndef _PIXEL_HPP_
#define _PIXEL_HPP_
#include <data/Point.hpp>
#include <data/Pigment.hpp>


template<typename PIGMENT>
class Pixel{
private:
	PIGMENT m_pigment;
	Point m_point;

public:
	Pixel(Point point, PIGMENT pigment):
		m_pigment(pigment),
		m_point(point){

		} 
	PIGMENT pigment()const{
		return m_pigment;
	}
	Point point()const{
		return m_point;
	}
};


typedef Pixel<ColorPigment> ColorPixel;
typedef Pixel<GrayPigment> GrayPixel;



#endif