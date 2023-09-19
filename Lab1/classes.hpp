#include <iostream>
#include <fstream>
#include <cmath>
#include "interfaces.hpp"

//Printing classes
class ConsolePrinter: public IValPrinter{
public:
	void printVal(float val){
		std::cout << val << std::endl;
	}

	void printVal(float val[], int size){
		for(int i=0; i<size; i++){
			std::cout << val[i] << std::endl;
		}
	}
};

class FilePrinter: public IValPrinter{
private:
	std::ofstream out_file;
public:
	FilePrinter(std::string location){
		out_file.open(location);
	}

	~FilePrinter(){
		out_file.close();
	}

	void printVal(float val){
		out_file << val << std::endl;
	}

	void printVal(float val[], int size){
		for(int i=0; i<size; i++){
			out_file << val[i] << std::endl;
		}
	}
};

//=====================================//

//2D stuff
class Square: public IShape_2D{
private:
	float a = 0;
public:
	void setSide(float a){
		this->a = a;
	}
	void printSide(IValPrinter* out){
		out->printVal(a);
	}
	void calcPerimiter(IValPrinter* out){
		out->printVal(4*a);
	}
	void calcArea(IValPrinter* out){
		out->printVal(a*a);
	}
};

//-------------------------------------//

class Circle: public IShape_2D{
private:
	float radius = 0;
	float pi = 3.141592;
public:
	void setRadius(float r){
		this->radius = r;
	}
	void printRadius(IValPrinter* out){
		out->printVal(radius);
	}
	void calcPerimiter(IValPrinter* out){
		out->printVal(2*pi*radius);
	}
	void calcArea(IValPrinter* out){
		out->printVal(pi*radius*radius);
	}
};

//-------------------------------------//

class EquilatTriang: public ITriangle{
private:
	float a = 0;
public:
	void setSides(float a){
		this->a = a;
	}
	void printSides(IValPrinter* out){
		float values[] = {a,a,a};
		out->printVal(values, 3);
	}
	void calcPerimiter(IValPrinter* out){
		out->printVal(a*3);
	}
	void calcArea(IValPrinter* out){
		out->printVal(a*a*std::sqrt(3)/4);
	}
};

class IsoscelesTriang: public ITriangle{
private:
	float a = 0, b = 0;
public:
	void setSides(float a, float b){
		this->a = a;
		this->b = b;
	}
	void printSides(IValPrinter* out){
		float values[] = {a,a,b};
		out->printVal(values, 3);
	}
	void calcPerimiter(IValPrinter* out){
		out->printVal(a*2+b);
	}
	void calcArea(IValPrinter* out){
		out->printVal(sqrt(a*a-b*b/4)*b/2);
	}
};

class ScaleneTriang: public ITriangle{
private:
	float a = 0, b = 0, c = 0;
public:
	void setSides(float a, float b, float c){
		this->a = a;
		this->b = b;
		this->c = c;
	}
	void printSides(IValPrinter* out){
		float values[] = {a,b,c};
		out->printVal(values, 3);
	}
	void calcPerimiter(IValPrinter* out){
		out->printVal(a+b+c);
	}
	void calcArea(IValPrinter* out){
		float s = (a+b+c)/2;
		out->printVal(sqrt(s*(s-a)*(s-b)*(s-c)));
	}
};

//=====================================//

//3D Stuff

class Sphere: public IVolume_3D{
private:
	float radius = 0;
	float pi = 3.141592;
public:
	void setRadius(float r){
		this->radius = r;
	}
	void printRadius(IValPrinter* out){
		out->printVal(radius);
	}
	void calcArea(IValPrinter* out){
		out->printVal(4*pi*radius*radius);
	}
	void calcVolume(IValPrinter* out){
		out->printVal(4*pi*radius*radius*radius/3);
	}
};

//-------------------------------------//

class Cube: public IVolume_3D{
private:
	float a = 0;
public:
	void setSide(float a){
		this->a = a;
	}
	void printSide(IValPrinter* out){
		out->printVal(a);
	}
	void calcArea(IValPrinter* out){
		out->printVal(6*a*a);
	}
	void calcVolume(IValPrinter* out){
		out->printVal(a*a*a);
	}
};
