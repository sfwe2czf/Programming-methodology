// manager.h

#ifndef MANAGER_H
#define MANAGER_H

#include "route.h"
#include <string>
using namespace std;

class Manager
{
public:
	Manager();

public:
	void Print();

	void Start();
	void ReadManual();
	void ReadFile();
	void AddRoute(Route* r);

	void PrintRoute(int rid);				// Print a route you have selected
	int FindBestRoute(int mode);			// Find the best route of the selected constraint and return the route id
	int* FindRoutes(int mode, double pivot);	// Find routes that are better than pivot value in each mode
	void Sort(int mode);					// Sort the routes based on the selected constraint, print a sequence of route ids in best to worst order

private:
	vector<Route*> routeList;
	int cntID; 
};

#endif