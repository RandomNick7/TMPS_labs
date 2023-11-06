#include "command.hpp"
#include "strategy.hpp"
#include "editor_class.hpp"
#include "memento.hpp"

int main(){
    File* some_txt = new File();
    Editor* editor = new Editor(some_txt);
    Context* context = new Context();
    MementoStack* history = new MementoStack();

    editor->setText("This is some text to be put in a file!");


    //Save the text to file
    Command* command = new SaveCommand(history, context, editor, true);
    command->execute();

    //Expected: Above string to be echoed
    some_txt->showText();

    editor->setText("This is a modified text, different from the original");
    command = new SaveCommand(history, context, editor, false);
    command->execute();

    //Expected: Original string to be echoed
    some_txt->showText();

    //history contains a Memento with that last modification
    //Let's try loading it and saving it to the file

    editor->setText("This is a text that should not be printed, if all works well");
    command = new LoadCommand(history, context, editor);
    command->execute();

    command = new SaveCommand(history, context, editor, true);
    command->execute();

    //Expected - Echo of 2nd string
    some_txt->showText();
    return 0;
}
