#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <iostream>
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

#endif
