#ifndef _RANDOM_2D_POINTS_GENERATOR_HPP_
#define _RANDOM_2D_POINTS_GENERATOR_HPP_
#include <data/Geoemetry.hpp>
#include <data/Point.hpp>
#include <archi/Provider.hpp>
#include <archi/Receiver.hpp>
#include <vector>

class Random2DPointsGenerator : public Receiver<Rectangle>, public Receiver<int>, public Provider<std::vector<Point> >{
	int m_nb;
	public:
		Random2DPointsGenerator(){		}
		void run(){
			std::vector<Point> points;
			
			Rectangle r = Receiver<Rectangle>::get("domain");
			int count = Receiver<int>::get("count");
			std::random_device rd;
		    std::mt19937 gen(rd());
    		std::uniform_int_distribution<> xdis(r.x, r.x+r.width);
			std::uniform_int_distribution<> ydis(r.y, r.y+r.height);
			std::generate_n(std::back_inserter(points), count, [&xdis, &ydis, &gen]()	{
				return cv::Point(xdis(gen), ydis(gen));
			});

			Provider<std::vector<Point> >::set("output", points);

		}
};


#endif