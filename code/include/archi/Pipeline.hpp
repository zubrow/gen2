#ifndef _PIPELINE_HPP_
#define _PIPELINE_HPP_

#include <memory>
#include <algorithm>
#include <string>


#include<archi/Module.hpp>


class Pipeline{
private:

	std::map<std::string , std::shared_ptr<Module> > m_modules;
	std::vector<std::shared_ptr<Module> >  m_order;

public:
	void run(){
		std::for_each(m_order.begin(), m_order.end(), [](std::shared_ptr<Module> module){ module->run();});
	}
	void addModule(std::string name, std::shared_ptr<Module> module){
		m_modules[name] = module;
		m_order.push_back(module);
	}

	void link(std::string providerName, 
			std::string providerOutputName, 
			std::string receiverName, 
			std::string receiverInputName){

		auto moduleFound = m_modules.find( providerName );

        if ( moduleFound == m_modules.end() )
           {
             std::cout << "Provider : " << providerName << " not found !";
                return;
            }

            std::shared_ptr<Module>& provider = moduleFound->second;
            moduleFound = m_modules.find( receiverName );

            if ( moduleFound == m_modules.end() )
            {
                std::cout << "Listener : " << receiverName << " not found !";
                return;
            }

            std::shared_ptr<Module>& potentialReceiver = moduleFound->second;
            //TODO : checker si le provider en est bien un
            std::shared_ptr<AbstractReceiver> receiver = std::dynamic_pointer_cast<AbstractReceiver> ( potentialReceiver );
             if ( !receiver)
            {
                std::cout << "receiver "<<receiverName<<"."<<receiverInputName<<" non valide pour "<<providerName<<"."<< providerOutputName<<std::endl;
            }
            //TODO : checker que les modules sont du bon type
            if ( receiver->setProvider(receiverInputName, provider, providerOutputName))
            {
                std::cout << " -> success !";
            }
            else
            {
                std::cout << " -> fail !";
            }
	}


};


#endif