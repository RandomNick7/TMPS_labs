# Creational Design Patterns
## Author: Otgon Dorin

----------
## Objectives:
&ensp; &ensp; __1. Study the existing Creational Design Patterns.__

&ensp; &ensp; __2. Choose 4 creational patterns and plan out the classes and entities which shall be used.__

&ensp; &ensp; __3. Create a small project that implements all 4 chosen patterns.__

## Implementation:
The first creational design pattern chosen was the Abstract Factory, which also utilizes the Factory pattern in its implementation. The purpose of it is to create families of related objects via Factories without having to specify their concrete classes. A client simply uses a concrete implementation of the Abstract Factory and uses its interface to create specific objects. Inside the code, there is an abstract VehicleFactory with 3 concrete implementations depending on the medium: "Ground", "Water" or "Air". All factories can create either a "Light" vehicle or a "Heavy" one, representing the aforementioned families. The code for the Abstract Factory is available in `factories.hpp`, here is a snippet including one of the Factories and its related classes:

```
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
```

Another implemented Design Pattern is the Singleton - A class which only allows itself to be instantiated only once. Useful when only 1 object is ever needed, requiring easy access. Although being one of the most well-known design patterns, its existence violates S of SOLID, as it is responsible for enforcing its uniqueness while also performing whatever other functionalities it may have. A simple "Statistics" class was implemented following this design pattern, as there is no point in having more than 1 global statistic. The code is also available in `singleton.hpp`:
```
// A Simpleton to monitor basic values. More than 1 Object of this class is not needed anyway
class Statistics{
private:
	int profits, deliveries;
	static Statistics* instancePtr;

	// Hidden default constructor
	Statistics(){}

public:
	//Remove copy Constructor & assignation operation
	Statistics(const Statistics& obj) = delete;
	void operator = (Statistics const&) = delete;

	// If there's no instance, make one. Otherwise, just return the pointer to the existing instance
	static Statistics* getInstance(){
		if (instancePtr == NULL){
			instancePtr = new Statistics();
			instancePtr->profits = 0;
			instancePtr->deliveries = 0;
		}
		return instancePtr;
	}

	void completeDelivery(int cash_delta){
		profits += cash_delta;
		deliveries++;
	}

	int getProfits(){
		return profits;
	}

	int getDeliveries(){
		return deliveries;
	}
};
```

The fourth design pattern implemented is the Object Pool pattern, used often for keeping track of numerous instances of a particular class or for classes where class instantiation and object destruction are too computationally costly. It allows one to reuse old objects without wasting extra time with re-instantiation every time. It can be implemented within other design patterns, including the previous Abstract Factory. A simple example is provided in `obj_pool.hpp`:

```
// An Object Pool managing all Couriers (example class), assuming it'd be the most commonly used type
// This is usually used when instantiating/destroying happens very often or is very costly

class CourierPool{
private:
	std::list<Courier*> couriers;
public:
	Courier* getCourier(){
		// If there are no available Couriers, just make a new one:
		if(couriers.empty()){
			return new Courier();
		}else{
		// Otherwise just return one from the pool
			Courier* c = couriers.front();
			couriers.pop_front();
			return c;
		}
	}

	//If a Courier's been used, reset it and put it back in the pool
	void returnCourier(Courier* c){
		c->reset();
		couriers.push_back(c);
	}
};
```

The code within the `main.cpp` file is only to check if all the classes' methods work correctly. Running the code should print a series of results in the terminal, which can be manually checked for validity.

## Conclusion
During this laboratory work, 4 implementations have been successfully programmed, these being the Abstract Factory and the related (Concrete) Factory, the Singleton and the Object Pool. The code serves as an example of a simple yet extensible implementation of some of the most well-known and well-used creational design patterns.
