#ifndef COMMAND
#define COMMAND

#include "strategy.hpp"

class Command{
protected:
	MementoStack* history;
	Context* context;
	Editor* editor;
public:
	virtual void execute() = 0;
};

class SaveCommand: public Command{
private:
	bool to_file;
public:
	SaveCommand(MementoStack* history, Context* context, Editor* editor, bool to_file){
		this->history = history;
		this->context = context;
		this->editor = editor;
		this->to_file = to_file;
	}

	void execute(){
		if(to_file){
			this->context->setStrat(new SaveFile(editor));
		}else{
			this->context->setStrat(new SaveSnapshot(editor, history));
		}
		this->context->execStrat();
	}
};

class LoadCommand: public Command{
public:
	LoadCommand(MementoStack* history, Context* context, Editor* editor){
		this->history = history;
		this->context = context;
		this->editor = editor;
	}

	void execute(){
		this->context->setStrat(new LoadSnapshot(editor, history));
		this->context->execStrat();
	}
};

#endif
