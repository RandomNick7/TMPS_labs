#include "factories.hpp"
#include "obj_pool.hpp"
#include "singleton.hpp"

// Initializing instancePtr from the Singleton
Statistics* Statistics::instancePtr = NULL;

//Driver code
int main(){
	//Initialize the Singleton
	Statistics* stats = Statistics::getInstance();

	//Initialize a factory capable of producing anything needed and a Vehicle variable that can accomodate for anything
	VehicleFactory* universal_factory;
	Vehicle* transport;


	universal_factory = new GroundTypeFactory();

	// Ground + Light Vehicle = Truck
	transport = universal_factory->createLight();
	transport->deliver("Berlin");
	stats->completeDelivery(8);

	// Ground + Heavy Vehicle = Train
	transport = universal_factory->createHeavy();
	transport->deliver("Paris");
	stats->completeDelivery(43);


	universal_factory = new WaterTypeFactory();

	// Water + Light Vehicle = Barge
	transport = universal_factory->createLight();
	transport->deliver("London");
	stats->completeDelivery(13);

	// Water + Heavy Vehicle = Freighter
	transport = universal_factory->createHeavy();
	transport->deliver("Washington");
	stats->completeDelivery(275);


	universal_factory = new FlyingTypeFactory();

	// Air + Light Vehicle = UAV a.k.a. Drone
	transport = universal_factory->createLight();
	transport->deliver("Baltimore");
	stats->completeDelivery(3);

	// Air + Heavy Vehicle = Plane
	transport = universal_factory->createHeavy();
	transport->deliver("Los Angeles");
	stats->completeDelivery(16);

	std::cout << std::endl;

	// Testing out that the Singleton is actually a single instance...
	std::cout << "Total profit: " << stats->getProfits() << std::endl;
	std::cout << "Total deliveries: " << stats->getDeliveries() << std::endl;
	Statistics* new_stats = Statistics::getInstance();

	std::cout << std::endl;

	// Creating and testing a Pool...
	CourierPool* pool = new CourierPool();
	Courier* c1 = pool -> getCourier();
	Courier* c2 = pool -> getCourier();
	Courier* c3 = pool -> getCourier();

	// Perform a bunch of deliveries to change the "deliveries" attribute in the couriers
	c1 -> deliver("Santa Clarita");
	new_stats->completeDelivery(2);
	c1 -> deliver("Bakersfield");
	new_stats->completeDelivery(5);
	c2 -> deliver("Santa Barbara");
	new_stats->completeDelivery(3);
	c3 -> deliver("Long Beach");
	new_stats->completeDelivery(1);

	std::cout << "Courier delivery counts: " << c1->getDeliveries() << ' ' << c2->getDeliveries() << ' ' << c3->getDeliveries() << std::endl;

	// Return the couriers to the pool, their values should be reset
	pool -> returnCourier(c1);
	pool -> returnCourier(c2);

	// c1 and c2 should show values of 0 deliveries now
	c1 = pool -> getCourier();
	c2 = pool -> getCourier();
	std::cout << "Courier delivery counts: " << c1->getDeliveries() << ' ' << c2->getDeliveries() << ' ' << c3->getDeliveries() << std::endl;

	std::cout << std::endl;

	//Singleton should show sum of ALL profits and delivery counts, regardless of re-instantiation earlier in the code
	std::cout << "Total profit: " << stats->getProfits() << std::endl;
	std::cout << "Total deliveries: " << stats->getDeliveries() << std::endl;
	return 0;
}
