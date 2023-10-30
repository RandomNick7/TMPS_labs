#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include <cstddef>
#include <iostream>
#include <vector>

class Item{
protected:
	std::string item_name = "";
	Item* parent;
public:
	int item_size = 0;
	virtual void show_stats() = 0;
	virtual bool is_folder() = 0;
	int get_size(){
		return item_size;
	}

	std::string get_name(){
		return item_name;
	}

	void update_size(int size){
		this->item_size += size;
		if(parent != NULL){
			this->parent->update_size(size);
		}
	}

	Item* exit(){
		return parent;
	}
};


class Folder: public Item{
	int file_count = 0;
	std::vector<Item*> contents;
public:
	Folder(std::string name, Folder* parent){
		this->item_name = name;
		this->parent = parent;
	}

	void add_item(Item* new_item){
		file_count++;
		contents.push_back(new_item);
		update_size(new_item->item_size);
	}

	Item* open_item(std::string name){
		for(int i=0; i<contents.size(); i++){
			if(contents[i]->get_name() == name){
				return contents[i];
			}
		}
		return NULL;
	}

	void show_stats(){
		std::cout << "Folder name: " << item_name << std::endl;
		std::cout << "Folder size: " << item_size << std::endl;
		std::cout << "Item count: " << file_count << std::endl;
	};

	void show_items(){
		if(file_count > 0){
			std::cout << "Items:" << std::endl;
			for(int i=0; i<contents.size(); i++){
				std::cout << i+1 << ". " << contents[i]->get_name() << std::endl;
			}
		}
	}

	Item* get_parent(){
		return parent;
	}

	bool is_folder(){
		return true;
	}
};

class File: public Item{
public:
	File(std::string name, Folder* parent){
		this->item_name = name;
		this->parent = parent;
	}

	void change_size(int new_size){
		parent->update_size(this->item_size - new_size);
		this->item_size = new_size;
	}

	void show_stats(){
		std::cout << "Folder name:" << item_name << std::endl;
		std::cout << "Folder size:" << item_size << std::endl;
	}

	bool is_folder(){
		return false;
	}
};

#endif
