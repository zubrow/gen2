#ifndef _RECEIVER_HPP_
#define _RECEIVER_HPP_

#include <archi/Module.hpp>

class AbstractReceiver : public virtual Module{
	public:
		virtual ~AbstractReceiver(){}
		virtual bool setProvider(std::string name, std::shared_ptr<Module> provider, std::string outputName)=0;

};





template<typename T>
class Receiver : public virtual  AbstractReceiver{
private:
	std::map<std::string, std::pair<std::shared_ptr<Provider<T> >, std::string> > m_providers;
public:
	virtual void setProvider(std::string name, std::shared_ptr<Provider<T> > provider, std::string outputName){
		m_providers[name] = std::make_pair(provider, outputName);
	}
	
	virtual bool setProvider(std::string name, std::shared_ptr<Module> provider, std::string outputName)
	{
		return trySetProvider(name, provider, outputName);
	}




protected:
	T get(std::string name){
		std::cout<<"get "<<name<<std::endl;
		return m_providers[name].first->get(m_providers[name].second);
	}

 bool trySetProvider(std::string name, std::shared_ptr<Module> provider, std::string outputName)
	{
		std::shared_ptr<Provider<T> > casted = std::dynamic_pointer_cast<Provider<T> >(provider);
		if (casted)
		{
			setProvider(name, casted, outputName);
			return true;
		}
		return false;
	}
};


#endif