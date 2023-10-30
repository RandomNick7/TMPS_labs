#ifndef FACADE_HPP
#define FACADE_HPP

#include "composite.hpp"
#include "proxy.hpp"
#include "abstract_facade.hpp"
#include "decorator.hpp"

class AdminUI: public Facade{
public:
	AdminUI(){
		curr_location = new Folder("root", NULL);
		temp = NULL;
	}

	void add_new_folder(std::string name){
		Folder* folder = new Folder(name, curr_location);
		curr_location->add_item(folder);
	}

	void add_new_file(std::string name){
		File* file = new File(name, curr_location);
		curr_location->add_item(file);
	}

	void show_stats(){
		std::cout << std::endl;
		curr_location->show_stats();
		curr_location->show_items();
		std::cout << std::endl;
	}

	//Latest added file will be the edit target
	void edit_file(int new_size){
		if(temp!=NULL){
			temp->change_size(new_size);
			temp->submit_changes();
		}else{
			std::cout << "No file set to edit!" << std::endl;
		}
	}


//Ugly casts inbound, at least it avoids more OOP spaghetti
//The casts are all done to expected types
//File and Folder always have a Folder as parent, so it introduces no issues
	void go_to_item(std::string input){
		if(input == ".." && curr_location->get_parent()!=NULL){
			curr_location = (Folder*)curr_location->exit();
		}else if(input == "."){
			//Do nothing.
		}else{
			Item* new_location = curr_location->open_item(input);
			if(new_location == NULL){
				std::cout << "Invalid location!" << std::endl;
			}else{
				if(new_location->is_folder()){
					curr_location = (Folder*)new_location;
				}else{
					//Make sure to clean your mess up!
					if(temp != NULL){
						delete temp;
					}
					temp = new TempFile((File*)new_location);
				}
			}
		}
	}

	Facade* change_perms(){
		return new UserUI(this);
	}
};

#endif
