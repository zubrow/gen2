#ifndef _PROVIDER_HPP_
#define _PROVIDER_HPP_

#include <archi/Module.hpp>

template<typename T>
class Provider : public virtual Module{
	private:
		std::map<std::string, T> m_values;
		
	protected:
		void set(std::string name, T value){

		std::cout<<"set "<<name<<std::endl;
			m_values[name] = value;
		}

	public:
		T get(std::string name){
			return m_values[name];
		}
};


#endif