
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <iostream>
#include <memory>
#include <map>
#include <vector>



#include <modules/Camera.hpp>
#include <modules/ImageDisplay.hpp>
#include <modules/ImageLoader.hpp>
#include <archi/Pipeline.hpp>




// class Random2DPointsGenerator : public Receiver<cv::Rect>, public Provider<std::vector<cv::Point> >{
// 	int m_nb;
// 	public:
// 		Random2DPointsGenerator(int nb):m_nb(nb){		}
// 		void run(){

// 		//std::cout<<"random points"<<std::endl;
// 			std::vector<cv::Point> points;
			
// 			cv::Rect r = Receiver<cv::Rect>::get("domain");

// 			std::random_device rd;
// 		    std::mt19937 gen(rd());
//     		std::uniform_int_distribution<> xdis(r.x, r.x+r.width);
// 			std::uniform_int_distribution<> ydis(r.y, r.y+r.height);
// 			std::generate_n(std::back_inserter(points), m_nb, [&xdis, &ydis, &gen]()	{
// 				return cv::Point(xdis(gen), ydis(gen));
// 			});

// 			Provider<std::vector<cv::Point> >::set("output", points);

// 		}
// };





// class GridRandom2DPointsGenerator : public Receiver<cv::Rect>, public Provider<std::vector<cv::Point> >{
// 	int m_step;
	
// 	public:
// 		GridRandom2DPointsGenerator(int step):m_step(step){		}
// 		void run(){

// 		//std::cout<<"grid random points"<<std::endl;
// 			std::vector<cv::Point> points;
			
// 			cv::Rect r = Receiver<cv::Rect>::get("domain");

// 			std::random_device rd;
// 		    std::mt19937 gen(rd());
//     		std::uniform_int_distribution<> dis(-m_step, m_step);
//     		bool reverse;
// 			for(int j = m_step; j < r.height-m_step; j+=m_step){
// 				if(!reverse){
// 					for(int i = m_step; i < r.width-m_step; i+=m_step){
// 						points.push_back(cv::Point(i+dis(gen), j+dis(gen)));
// 					}
// 				}else{
// 					for(int i = r.width-m_step; i > m_step; i-=m_step){
// 						points.push_back(cv::Point(i+dis(gen), j+dis(gen)));
// 					}	
// 				}
// 				reverse = !reverse;
// 			}
// 			Provider<std::vector<cv::Point> >::set("output", points);

// 		}
// };












// template<typename T>
// class ConsoleLog : public Receiver<T>{
// public:
// 	void run(){
// 		std::cout<<Receiver<T>::get("input")<<std::endl;

// 	}

// };

// class CircleDrawing : public Receiver<cv::Mat>, public Receiver<std::vector<cv::Point> >, public Provider<cv::Mat>{
// private: 
// 	int m_radius;
// public:


// 	CircleDrawing(int radius):m_radius(radius){}
// 	void run(){
// 		//std::cout<<"cricles drawing"<<std::endl;
// 		cv::Mat img = Receiver<cv::Mat>::get("image");
// 		std::vector<cv::Point> points = Receiver<std::vector<cv::Point> >::get("centers");
// 		cv::Mat res = img.clone();
// 		res.setTo(0);
// 		for(auto it = points.begin(); it != points.end(); ++it){
// 			cv::Vec3b v = img.at<cv::Vec3b>(*it);
			
// 			cv::circle(res, *it, m_radius, cv::Scalar(v[0], v[1], v[2]),-1);
// 		}

// 		Provider<cv::Mat>::set("output", res);
// 	}

// 	bool setProvider(std::string name, std::shared_ptr<Module> provider, std::string outputName)
// 	{
// 		if(Receiver<cv::Mat>::trySetProvider(name, provider, outputName))return true;
// 		if(Receiver<std::vector<cv::Point> >::trySetProvider(name, provider, outputName))return true;
// 		return false;
// 	}
// };




// class PolyDrawing : public Receiver<cv::Mat>, public Receiver<std::vector<cv::Point> >, public Provider<cv::Mat>{
// public:


// 	void run(){
// 		std::cout<<"poly drawing"<<std::endl;
// 		cv::Mat img = Receiver<cv::Mat>::get("image");
// 		std::vector<cv::Point> points = Receiver<std::vector<cv::Point> >::get("points");
// 		cv::Mat res = img.clone();
// 		res.setTo(0);
// 		auto next = points.begin();
// 		++next;
// 		for(auto it = points.begin(); next != points.end(); ++it, ++next){
// 			cv::Vec3b v = img.at<cv::Vec3b>(*it);
			
// 			cv::line(res, *it, *next, cv::Scalar(v[0], v[1], v[2]));
// 		}

// 		Provider<cv::Mat>::set("output", res);
// 	}

// 	bool setProvider(std::string name, std::shared_ptr<Module> provider, std::string outputName)
// 	{
// 		if(Receiver<cv::Mat>::trySetProvider(name, provider, outputName))return true;
// 		if(Receiver<std::vector<cv::Point> >::trySetProvider(name, provider, outputName))return true;
// 		return false;
// 	}
// };



int main(int argc, char** argv){
	Pipeline pipeline;
	//pipeline.addModule("camera", std::shared_ptr<Module>(new Camera(0)));
	if(argc>1)
	pipeline.addModule("camera", std::shared_ptr<Module>(new ImageLoader(argv[1])));
	else
	pipeline.addModule("camera", std::shared_ptr<Module>(new ImageLoader("lena.jpg")));
	
	pipeline.addModule("display", std::shared_ptr<Module>(new ImageDisplay("img")));
	pipeline.link("camera", "output", "display", "input");
	while(1){
		pipeline.run();
		if(cv::waitKey(10)>0)break;
	}
	return 0;





}