#ifndef FACTORIES_HPP
#define FACTORIES_HPP

#include <iostream>

// Abstract base entity whose defined functions represent what other classes can work with concering the final concrete objects
class Vehicle{
public:
	virtual void deliver(std::string destination) = 0;
};

// Abstract Factory - defines how all other factories are meant to behave
class VehicleFactory{
public:
	virtual Vehicle* createHeavy() = 0;
	virtual Vehicle* createLight() = 0;
};

//2 Concrete things & 1 Concrete Factory per related classes below

//==== Land units ====//

class Train: public Vehicle{
public:
	void deliver(std::string destination){
		std::cout << "Sending freight to " << destination << std::endl;
	}
};

class Truck: public Vehicle{
public:
	void deliver(std::string destination){
		std::cout << "Delivering packages to " << destination << std::endl;
	}
	void reset(){};
};

class GroundTypeFactory: public VehicleFactory{
public:
	Vehicle* createHeavy(){
		return new Train;
	}
	Vehicle* createLight(){
		return new Truck;
	}
};

//==== Sea units ====//

class Freighter: public Vehicle{
public:
	void deliver(std::string destination){
		std::cout << "Shipping cargo to " << destination << std::endl;
	}
};

class Barge: public Vehicle{
public:
	void deliver(std::string destination){
		std::cout << "Sailing with merchandise to " << destination << std::endl;
	}
};

class WaterTypeFactory: public VehicleFactory{
public:
	Vehicle* createHeavy(){
		return new Freighter;
	}
	Vehicle* createLight(){
		return new Barge;
	}
};

//==== Aerial units ====//

class Plane: public Vehicle{
public:
	void deliver(std::string destination){
		std::cout << "Flying with goods to " << destination << std::endl;
	}
};

class UAV: public Vehicle{
public:
	void deliver(std::string destination){
		std::cout << "Dropping package at " << destination << std::endl;
	}
};

class FlyingTypeFactory: public VehicleFactory{
public:
	Vehicle* createHeavy(){
		return new Plane;
	}
	Vehicle* createLight(){
		return new UAV;
	}
};

#endif
