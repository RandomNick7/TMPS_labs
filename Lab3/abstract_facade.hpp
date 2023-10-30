#ifndef ABSTRACT_FACADE
#define ABSTRACT_FACADE

#include "composite.hpp"
#include "proxy.hpp"

class Facade{
protected:
	Folder* curr_location;
	TempFile* temp;
public:
	virtual void add_new_folder(std::string name) = 0;
	virtual void add_new_file(std::string name) = 0;
	virtual void show_stats() = 0;
	virtual void edit_file(int new_size) = 0;
	virtual void go_to_item(std::string input) = 0;
	virtual Facade* change_perms() = 0;
};

#endif
