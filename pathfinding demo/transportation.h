// transportation.h

#ifndef TRANS_H
#define TRANS_H

#include <iostream>

using namespace std;

// Transportation node
class Transportation
{
public:
	Transportation() { this->distance = 0; this->speed = 0; }
	Transportation(double dist, double speed) { this->distance = dist; this->speed = speed; }

public:
	virtual void Print();									// Prints node data 
	virtual double Time() { return distance / speed; }		// Computes Time of transportation
	virtual double Dist() { return distance; }
	virtual double Work() { return 0; }						// Computes Work of transportation
	virtual int Cost() { return 0; }						// Computes Cost of transportation

protected:
	double distance;			// Distance of the transportation
	double speed;				// Speed of the transportation
};

// Free Transportation method node which use more strength, less money, more time.
class FreeTrans : public Transportation
{
public:
	FreeTrans() : Transportation() { this->work = 0; }
	FreeTrans(double dist, double speed, double work) 
	: Transportation(dist, speed)
	{ this->work = work; }

public:
	virtual void Print();		// Prints data
	double Work();				// Computes the total work 

protected:
	double work;				// work per distance
};

// Transportation node for Walking
class Walking : public FreeTrans
{
public:
	Walking() : FreeTrans() {};
	Walking(double dist, double speed, double work)
	: FreeTrans(dist, speed, work) {}

public:
	void Print();
};

///////////////////////////////////////////
//////// TODO : Write more classes ////////
///////////////////////////////////////////
// Transportation node for Bicycle
class Bicycle :public FreeTrans {
public:
	Bicycle() :FreeTrans() {};
	Bicycle(double dist, double speed, double work)
	: FreeTrans(dist, speed, work) {}

public:
	void Print();
};


// Paid Transportation method node which use more money, less time, no work.
class PaidTrans : public Transportation
{
public:
	PaidTrans() : Transportation() { this->cost = 0; }
	PaidTrans(double dist, double speed, int cost)
		: Transportation(dist, speed)
	{
		this->cost = cost;
	}

public:
	virtual void Print();		// Prints data
	int Cost();				// Computes the total cost(Money)

protected:
	double cost;				// work per distance
};

// Transport node for Bus
class Bus :public PaidTrans {
public:
	Bus() :PaidTrans() {};
	Bus(double dist, double speed, int cost)
		: PaidTrans(dist, speed, cost) {}

public:
	void Print();
};

// Transport node for Taxi
class Taxi :public PaidTrans {
public:
	Taxi() :PaidTrans() {};
	Taxi(double dist, double speed, int cost)
		: PaidTrans(dist, speed, cost) {}

public:
	void Print();
};

// Transport node for Bus
class Subway :public PaidTrans {
public:
	Subway() :PaidTrans() {};
	Subway(double dist, double speed, int cost)
		: PaidTrans(dist, speed, cost) {}

public:
	void Print();
};



#endif