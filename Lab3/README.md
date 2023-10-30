# Structural Design Patterns
## Author: Otgon Dorin

----------
## Objectives:
&ensp; &ensp; __1. Study the existing Structural Design Patterns.__

&ensp; &ensp; __2. Choose 4 structural patterns and plan out the classes and entities which shall be used.__

&ensp; &ensp; __3. Create a small project that implements all 4 chosen patterns.__

## Implementation:
The general idea of this project was to create something similar to a basic file explorer. The code for each structural pattern is available in the header file with the corresponding name. The first structural design pattern chosen was the Composite, as the file explorer would have to work with Folders, which can contain other Files & Folders, which themselves can contain other such items. The tree-like structure that can be created with such a file/folder system corresponds with the purpose of a Composite. Several methods allowing for manipulation of these individual Items have been added as well for demonstration purposes. Below are 3 classes: the abstract Item class and its 2 implementations: File and Folder.

```cpp
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
```

If a modification were to be done to a file, it's often best to not write to the file directly, as every modification would influence the file, but instead to a temporary version and modifying the original file once upon completion. This can be achieved using the Proxy structural design pattern, implemented in the TempFile class:

```cpp
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
```

So far, a lot of methods have been implemented with little to hold them together. Calling them individually is possible, but would quickly become a hassle. A Facade can be implemented to ease the use of the Composite Objects:

```cpp
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
```

The abstract version of the facade is there for the implementation a Decorator, which can be used to create a version of the Facade with limited access, intended for unpriviledged users. Any actions the users are allowed to do is delegated to the Facade implemented above:

```cpp
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
```

The code within the `main.cpp` file is to check if all the classes' methods work correctly. Running the code should print a series of results in the terminal. The comments within `main.cpp` describe the expected results, which are successfully reached.

## Conclusion
During this laboratory work, 4 implementations have been successfully programmed, these being the Composite, Proxy, Facade and Decorator. The code is a simple example of a working implementation involving several structural patterns meshed together to create a basic version of a file manager/explorer.
