#ifndef EDITOR_CLASS
#define EDITOR_CLASS

#include <iostream>
#include "memento.hpp"

class File{
private:
	std::string text;
public:
	File(){
		this->text = "";
	}

	void setText(std::string text){
		this->text = text;
	}

	void showText(){
		std::cout << this->text << std::endl;
	}
};

class Editor{
private:
	std::string text;
	int cursorX;
	int cursorY;
	File* file;

public:
	Editor(File* file){
		this->file = file;
		text = "";
		cursorX = 0;
		cursorY = 0;
	}

	void setText(std::string text){
		this->text = text;
		saveMemento();
	}

	void setCursor(int x, int y){
		this->cursorX = x;
		this->cursorY = y;
	}


	void saveText(){
		this->file->setText(text);
	}

	Memento* saveMemento(){
		return new Memento(text, cursorX, cursorY);
	}

	void loadMemento(Memento snapshot){
		setText(snapshot.restore_text());
		setCursor(snapshot.restoreX(), snapshot.restoreY());
	}
};

#endif
