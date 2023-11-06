# Behavioral Design Patterns
## Author: Otgon Dorin

----------
## Objectives:
&ensp; &ensp; __1. Study the existing Behavioral Design Patterns.__

&ensp; &ensp; __2. Choose 3 structural patterns and plan out the classes and entities which shall be used.__

&ensp; &ensp; __3. Create a small project that implements all 3 chosen patterns.__

## Implementation:
In this laboratory work, the theme was a simple text editor, being able to change some file's contents and load previous snapshots.`main.cpp` contains a functional script showing how the patterns implemented work together. Some classes such as a simple "File" class and an "Editor" class to perform the modifications have been implemented for demonstration purposes. 

```cpp
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
```

The code for each behavioral pattern is available in the header file with the corresponding name. The first behavioral design pattern chosen was the Memento, allowing snapshots to be created at any time. A stack containing all these snapshots has been implemented as well, to allow more than 1 to be used at any time.

```cpp
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
```

The next behavioral pattern programmed was the Strategy, which allows one to change the behavior of a class at runtimeas one sees fit. The Context will be able to save the text from the editor either to a file or to a memento, or to load a previous snapshot and can easily change between these actions:

```cpp
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
```

Finally, a Command pattern has been implemented to manage these save/load actions. Its use is to simplify the implementations of future classes that would use these implementations instead of having them redefined every time:

```cpp
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
```

The code within the `main.cpp` file is to check if all the classes' methods work correctly. Only methods from the File, Editor and Command classes are directly called. Running the code should print a series of results in the terminal.

## Conclusion
During this laboratory work, 3 implementations have been successfully programmed, these being the Memento, Strategy and Command. The code is a simple example of a working implementation involving several behavioral patterns meshed together to create a stripped-down text editor.
