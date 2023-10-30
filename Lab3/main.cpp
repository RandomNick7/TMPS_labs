#include "composite.hpp"
#include "proxy.hpp"
#include "facade.hpp"
#include "decorator.hpp"

int main(){
	//Create an admin and place it in a user wrapper to restrict access
	Facade* user = new UserUI(new AdminUI());

	user->show_stats();
	//Expected: User warned for lacking permissions
	user->add_new_folder("Home");

	user = user->change_perms();
	//Expected: User succesfully creates new folders
	user->add_new_folder("Home");
	user->add_new_folder("Media");
	user->add_new_folder("Documents");
	user->show_stats();

	/*Expected: User succesfully creates the following structure:
	root/ [6300]
	├─ Media/ [3750]
	│  ├─ Images/ [750]
	│  │  ├─ cat1.png [400]
	│  │  └─ cat2.jpg [350]
	│  ├─ Videos/ [3000]
	│  │  └─ cool_vid.mp4 [3000]
	└─ Documents/ [2550]
	   ├─ PDFs/ [1350]
	   │  ├─ report2023.pdf [550]
	   │  └─ ref_sheet.pdf [800]
	   └─ report_template.docx [1200]

	Square brackets show item_size of each file/folder
	*/
	user->go_to_item("Media");
	user->add_new_folder("Images");
	user->add_new_folder("Videos");

	user->go_to_item("Images");
	// Add Files in Images and "edit" them to give them a size
	user->add_new_file("cat1.png");
	user->go_to_item("cat1.png");
	user->edit_file(400);

	user->add_new_file("cat2.png");
	user->go_to_item("cat2.png");
	user->edit_file(350);

	// Exit current folder
	user->go_to_item("..");

	// Add a file in Videos
	user->go_to_item("Videos");
	user->add_new_file("cool_vid.mp4");
	user->edit_file(3000);
	user->go_to_item("..");

	// Exit Media, go to Documents and add data there too
	user->go_to_item("..");
	user->go_to_item("Documents");
	user->add_new_folder("PDFs");
	user->add_new_file("report_template.docx");
	user->edit_file(1200);
	user->go_to_item("PDFs");
	user->add_new_file("report2023.pdf");
	user->edit_file(550);
	user->add_new_file("ref_sheet.pdf");
	user->edit_file(800);

	// Return to Root and check total size, must be 6300
	user->go_to_item("..");
	user->go_to_item("..");
	user->show_stats();

	user = user->change_perms();
	return 0;
}
