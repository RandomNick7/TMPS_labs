#ifndef OBJ_POOL_HPP
#define OBJ_POOL_HPP

#include <iostream>
#include <list>
// An Object Pool managing all Couriers (example class), assuming it'd be the most commonly used type
// This is usually used when instantiating/destroying happens very often or is very costly

class Courier{
private:
	int deliveries = 0;
public:
	void deliver(std::string destination){
		deliveries++;
		std::cout << "Carrying package to " << destination << std::endl;
	}

	int getDeliveries(){
		return deliveries;
	}

	void reset(){
		deliveries = 0;
	}
};

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

#endif
