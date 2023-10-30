#ifndef DECORATOR_HPP
#define DECORATOR_HPP

#include "composite.hpp"
#include "proxy.hpp"
#include "abstract_facade.hpp"

// Only 1 Decorator type is used, further inheritance is unnecessary
// Anything the default user is allowed to do is delegated to the real Facade
class UserUI: public Facade{
    Facade* base;
public:
	UserUI(Facade* facade){
        this->base = facade;
	}

	void add_new_folder(std::string name){
        std::cout << "You need elevated permissions to add new folders!" << std::endl;
	}

	void add_new_file(std::string name){
        std::cout << "You need elevated permissions to add new files!" << std::endl;
	}

	void show_stats(){
        base->show_stats();
	}

	void edit_file(int new_size){
        std::cout << "You need elevated permissions edit files!" << std::endl;
	}

	void go_to_item(std::string input){
		base->go_to_item(input);
	}

	Facade* change_perms(){
        return base;
    }
};

#endif
