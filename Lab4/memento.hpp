#ifndef MEMENTO
#define MEMENTO

#include <iostream>
#include <vector>

class Memento{
private:
	std::string text;
	int cursorX;
	int cursorY;
public:
	Memento(std::string text, int cursorX, int cursorY){
		this->text = text;
		this->cursorX = cursorX;
		this->cursorY = cursorY;
	}

	std::string restore_text(){
		return text;
	}

	int restoreX(){
		return cursorX;
	}

	int restoreY(){
		return cursorY;
	}
};

class MementoStack{
private:
	std::vector<Memento*> history;
public:
	void push(Memento* snapshot){
		history.push_back(snapshot);
	}

	Memento pop(){
		Memento last_snapshot = *(history.back());
		history.pop_back();
		return last_snapshot;
	}
};

#endif
