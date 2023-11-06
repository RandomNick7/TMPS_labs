#ifndef STRATEGY
#define STRATEGY

#include "editor_class.hpp"

class Strategy{
protected:
	Editor* editor;
public:
	virtual void execute() = 0;
};

class SaveFile: public Strategy{
public:
	SaveFile(Editor* editor){
		this->editor = editor;
	}
	void execute(){
		this->editor->saveText();
	}
};

class SaveSnapshot: public Strategy{
private:
	MementoStack* history;
public:
	SaveSnapshot(Editor* editor, MementoStack* history){
		this->editor = editor;
		this->history = history;
	}
	void execute(){
		history->push(this->editor->saveMemento());
	}
};

class LoadSnapshot: public Strategy{
private:
	MementoStack* history;
public:
	LoadSnapshot(Editor* editor, MementoStack* history){
		this->editor = editor;
		this->history = history;
	}

	void execute(){
		Memento last = history->pop();
		this->editor->loadMemento(last);
	}
};

class Context{
private:
public:
	Strategy* strat;
	void setStrat(Strategy* strategy){
		this->strat = strategy;
	}

	void execStrat(){
		strat->execute();
	}
};

#endif
