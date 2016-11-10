
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <iostream>
#include <memory>
#include <map>
#include <vector>

#include <data/Point.hpp>
#include <data/Pigment.hpp>
#include <data/Image.hpp>
#include <data/Pixel.hpp>

#include <archi/Provider.hpp>
#include <archi/Receiver.hpp>





class Camera : public Provider<cv::Mat>{
	private: 
		cv::VideoCapture cap;
	public:
		Camera(int i):Module(){
			cap.open(i);
		}

		void run(){
			cv::Mat img;
			cap>>img;
			Provider<cv::Mat>::set("output", img);
		}
};

class ImageLoader : public Provider<cv::Mat>{
	private: 
		std::string m_name;
	public:
		ImageLoader(std::string name):Module(), m_name(name){}

		void run(){
			cv::Mat img = cv::imread(m_name);
			Provider<cv::Mat>::set("output", img);
		}
};



class ImageDisplay : public Receiver<cv::Mat>{
	private:
		std::string m_windowName;
	public:
		ImageDisplay(std::string windowName):m_windowName(windowName){}
		void run(){
			cv::Mat img = Receiver<cv::Mat>::get("input");
			cv::imshow(m_windowName, img);

		}
};


class ImageSave : public Receiver<cv::Mat>{
	private:
		std::string m_fileName;
	public:
		ImageSave(std::string fileName):m_fileName(fileName){}
		void run(){
			cv::Mat img = Receiver<cv::Mat>::get("input");
			cv::imwrite(m_fileName, img);

		}
};

class ImageInfos : public Receiver<cv::Mat>, Provider<cv::Rect >{
	public:
		void run(){

		std::cout<<"image infos"<<std::endl;
			cv::Mat img = Receiver<cv::Mat>::get("input");
			cv::Rect r(0,0, img.cols, img.rows);
			Provider<cv::Rect>::set("domain", r);
		}

};

class Random2DPointsGenerator : public Receiver<cv::Rect>, public Provider<std::vector<cv::Point> >{
	int m_nb;
	public:
		Random2DPointsGenerator(int nb):m_nb(nb){		}
		void run(){

		//std::cout<<"random points"<<std::endl;
			std::vector<cv::Point> points;
			
			cv::Rect r = Receiver<cv::Rect>::get("domain");

			std::random_device rd;
		    std::mt19937 gen(rd());
    		std::uniform_int_distribution<> xdis(r.x, r.x+r.width);
			std::uniform_int_distribution<> ydis(r.y, r.y+r.height);
			std::generate_n(std::back_inserter(points), m_nb, [&xdis, &ydis, &gen]()	{
				return cv::Point(xdis(gen), ydis(gen));
			});

			Provider<std::vector<cv::Point> >::set("output", points);

		}
};





class GridRandom2DPointsGenerator : public Receiver<cv::Rect>, public Provider<std::vector<cv::Point> >{
	int m_step;
	
	public:
		GridRandom2DPointsGenerator(int step):m_step(step){		}
		void run(){

		//std::cout<<"grid random points"<<std::endl;
			std::vector<cv::Point> points;
			
			cv::Rect r = Receiver<cv::Rect>::get("domain");

			std::random_device rd;
		    std::mt19937 gen(rd());
    		std::uniform_int_distribution<> dis(-m_step, m_step);
    		bool reverse;
			for(int j = m_step; j < r.height-m_step; j+=m_step){
				if(!reverse){
					for(int i = m_step; i < r.width-m_step; i+=m_step){
						points.push_back(cv::Point(i+dis(gen), j+dis(gen)));
					}
				}else{
					for(int i = r.width-m_step; i > m_step; i-=m_step){
						points.push_back(cv::Point(i+dis(gen), j+dis(gen)));
					}	
				}
				reverse = !reverse;
			}
			Provider<std::vector<cv::Point> >::set("output", points);

		}
};












template<typename T>
class ConsoleLog : public Receiver<T>{
public:
	void run(){
		std::cout<<Receiver<T>::get("input")<<std::endl;

	}

};

class CircleDrawing : public Receiver<cv::Mat>, public Receiver<std::vector<cv::Point> >, public Provider<cv::Mat>{
private: 
	int m_radius;
public:


	CircleDrawing(int radius):m_radius(radius){}
	void run(){
		//std::cout<<"cricles drawing"<<std::endl;
		cv::Mat img = Receiver<cv::Mat>::get("image");
		std::vector<cv::Point> points = Receiver<std::vector<cv::Point> >::get("centers");
		cv::Mat res = img.clone();
		res.setTo(0);
		for(auto it = points.begin(); it != points.end(); ++it){
			cv::Vec3b v = img.at<cv::Vec3b>(*it);
			
			cv::circle(res, *it, m_radius, cv::Scalar(v[0], v[1], v[2]),-1);
		}

		Provider<cv::Mat>::set("output", res);
	}

	bool setProvider(std::string name, std::shared_ptr<Module> provider, std::string outputName)
	{
		if(Receiver<cv::Mat>::trySetProvider(name, provider, outputName))return true;
		if(Receiver<std::vector<cv::Point> >::trySetProvider(name, provider, outputName))return true;
		return false;
	}
};




class PolyDrawing : public Receiver<cv::Mat>, public Receiver<std::vector<cv::Point> >, public Provider<cv::Mat>{
public:


	void run(){
		std::cout<<"poly drawing"<<std::endl;
		cv::Mat img = Receiver<cv::Mat>::get("image");
		std::vector<cv::Point> points = Receiver<std::vector<cv::Point> >::get("points");
		cv::Mat res = img.clone();
		res.setTo(0);
		auto next = points.begin();
		++next;
		for(auto it = points.begin(); next != points.end(); ++it, ++next){
			cv::Vec3b v = img.at<cv::Vec3b>(*it);
			
			cv::line(res, *it, *next, cv::Scalar(v[0], v[1], v[2]));
		}

		Provider<cv::Mat>::set("output", res);
	}

	bool setProvider(std::string name, std::shared_ptr<Module> provider, std::string outputName)
	{
		if(Receiver<cv::Mat>::trySetProvider(name, provider, outputName))return true;
		if(Receiver<std::vector<cv::Point> >::trySetProvider(name, provider, outputName))return true;
		return false;
	}
};



int main(int argc, char** argv){
	Pipeline pipeline;
	pipeline.addModule("loader", std::shared_ptr<Module>(new Camera(0)));
	pipeline.addModule("imageinfos", std::shared_ptr<Module>(new ImageInfos()));
	pipeline.addModule("pointsgenerator", std::shared_ptr<Module>(new Random2DPointsGenerator(10000)));
	pipeline.addModule("gridgenerator", std::shared_ptr<Module>(new GridRandom2DPointsGenerator(5)));
	// pipeline.addModule("console", std::shared_ptr<Module>(new ConsoleLog<std::vector<cv::Point> >()));
	pipeline.addModule("circles", std::shared_ptr<Module>(new CircleDrawing(5)));
	pipeline.addModule("lines", std::shared_ptr<Module>(new PolyDrawing()));
	pipeline.addModule("displaycircles", std::shared_ptr<Module>(new ImageDisplay("circles")));
	pipeline.addModule("displaylines", std::shared_ptr<Module>(new ImageDisplay("lines")));
	//pipeline.addModule("savecircles", std::shared_ptr<Module>(new ImageSave("circles.jpg")));
	//pipeline.addModule("savelines", std::shared_ptr<Module>(new ImageSave("lines.jpg")));
	pipeline.link("loader", "output", "circles", "image");
	pipeline.link("loader", "output", "lines", "image");
	pipeline.link("loader", "output", "imageinfos", "input");
	pipeline.link("imageinfos", "domain", "pointsgenerator", "domain");
	pipeline.link("imageinfos", "domain", "gridgenerator", "domain");
	// pipeline.link("pointsgenerator", "output", "console", "input");
	pipeline.link("pointsgenerator", "output", "circles", "centers");
	pipeline.link("gridgenerator", "output", "lines", "points");
	pipeline.link("circles", "output", "displaycircles", "input");
	pipeline.link("lines", "output", "displaylines", "input");
	//pipeline.link("circles", "output", "savecircles", "input");
	//pipeline.link("lines", "output", "savelines", "input");
	while(1){
		pipeline.run();
		if(cv::waitKey(10)>0)break;
	}
	return 0;





}