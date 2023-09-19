#include "classes.hpp"

int main(){
	ConsolePrinter* out = new ConsolePrinter();
	FilePrinter* f = new FilePrinter("./shapes.txt");

	std::cout << "Square test..." << std::endl;
	Square* sqr = new Square();
	sqr->setSide(5.5);
	sqr->calcArea(f);
	sqr->printSide(out);

	std::cout << "Triangle test..." << std::endl;
	ScaleneTriang* pyth_triang = new ScaleneTriang();
	pyth_triang->setSides(6,8,10);
	pyth_triang->calcArea(f);
	pyth_triang->calcArea(out);
	pyth_triang->printSides(out);

	std::cout << "Circle test..." << std::endl;
	Circle* c = new Circle();
	c->setRadius(2.818);
	c->calcPerimiter(f);
	c->calcArea(out);

	std::cout << "Sphere test..." << std::endl;
	Sphere* s = new Sphere();
	s->setRadius(3.682);
	s->printRadius(out);
	s->calcArea(out);
	s->calcVolume(f);

	std::cout << "Cube test..." << std::endl;
	Cube* cube = new Cube();
	cube->setSide(5.48);
	cube->calcArea(out);
	cube->calcVolume(f);

	std::cout << "Everything's done, check shapes.txt too" << std::endl;
	return 0;
}
