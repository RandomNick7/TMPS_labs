# SOLID Principles
## Author: Otgon Dorin

----------
## Objectives:
&ensp; &ensp; __1. Study and understand the SOLID Principles.__

&ensp; &ensp; __2. Choose a domain, define its main classes/models/entities and choose the appropriate instantiation mechanisms.__

&ensp; &ensp;3. Create a sample project that respects SOLID Principles.

## Implementation:
- S - Single Responsibility Principle:
All classes implemented serve a single purpose within the system.

```
//Only responsible for objects defined as "spheres"
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

//Only responsible for objects defined as "cubes"
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
```

Despite having simmilar methods, it's best to keep them separate if we wish to respect this principle and the following:

- O - Open/Closed Principle:
Functionality must be possible to add without having to modify existing code. This is to avoid having to change the same segment of code over and over and risking removing essential functionality.

```
//Parent class, does not care about child structure
class IShape_2D: public IPolytope{
	public:
		virtual void calcPerimiter(IValPrinter* out) = 0;
};

//Children classes with independent implementation
class ITriangle: public IShape_2D{
public:
	virtual void printSides(IValPrinter* out) = 0;
};

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
```

Most often, a violation of the Open/Closed principle involves including code or conditionals that caters to specific scenarios or possible inputs. The code above follows the O principle as implementing a new shape would require no modifications in the existing classes.


- L - Liskov Substitution Principle
A subclass must be substitutable with its parent class without unintended consequences.

```
class IValPrinter{
	public:
		//printVal has 2 versions depending on arguments: 1 for a single number and 1 for arrays of numbers
		//This is done to avoid repeated calls to the first type or making arrays of size 1 for the second type
		virtual void printVal(float val) = 0;
		virtual void printVal(float val[], int size) = 0;
};

//Both printing classes are fully capable of substituting IValPrinter wherever it's used
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
```

- I - Interface Segregation Principle
Classes should not be forced to implement unneeded interfaces. They should only depend on interfaces they actually need.

```
//Both 2D and 3D things qualify as polytopes
class IPolytope{
	public:
		virtual void calcArea(IValPrinter* out) = 0;
};

//The perimeter is a concept relevant only for 2D shapes
class IShape_2D: public IPolytope{
	public:
		virtual void calcPerimiter(IValPrinter* out) = 0;
};

//The volume is a concept relevant only for 3D objects
class IVolume_3D: public IPolytope{
	public:
		virtual void calcVolume(IValPrinter* out) = 0;
};
```

- D - Dependency Inversion Principle
Concrete classes should depend on abstractions, not the other way around.

```
class IValPrinter{
	public:
		//printVal has 2 versions depending on arguments: 1 for a single number and 1 for arrays of numbers
		//This is done to avoid repeated calls to the first type or making arrays of size 1 for the second type
		virtual void printVal(float val) = 0;
		virtual void printVal(float val[], int size) = 0;
};

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

//The shapes only depend on the abstract class ValPrinter, whether ConsolePrinter or FilePrinter are used do not matter, both work just as well
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
```

The code within the `main.cpp` file is only to check if all the classes' methods work correctly.

## Conclusion
During this laboratory work, a simple, yet successful implementation of the SOLID principles has been created. The functionality within the code can be easily extended to suit needed purposes, the process being facilitated by the clean structure of the class hierarchy created. This serves as proof of the usefulness and practicality of the SOLID principles, and why is each defined as such.
