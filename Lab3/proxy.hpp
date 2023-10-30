#ifndef PROXY_HPP
#define PROXY_HPP

#include "composite.hpp"

class TempFile: public Item{
	File* real_file;
	int temp_size = 0;
public:
	TempFile(File* reference){
		this->real_file = reference;
	}

	void change_size(int new_size){
		temp_size = real_file->get_size() - new_size;
	}

	void submit_changes(){
		real_file->change_size(temp_size);
	}

	void show_stats(){
		real_file->show_stats();
	}

	bool is_folder(){
		return false;
	}
};

#endif
