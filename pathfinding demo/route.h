// route.h
#ifndef ROUTE_H
#define ROUTE_H

#include "transportation.h"
#include <vector>

class Route
{
public:
	Route();

public:
	void AddTrans(Transportation* t);
	void SetID(int id) { this->id = id; };
	int GetID() { return this->id; }
	void Print();
	
	double Dist();
	int Cost();
	double Work();
	double Time();


private:
	vector<Transportation*> routeData;
	int id;
	int cnt;
};

#endif