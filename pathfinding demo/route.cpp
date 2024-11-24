#include "route.h"

Route::Route()
{
	cnt = 0; // the number of transportation
	id = 0;
}

void Route::AddTrans(Transportation* trans)
{
	cnt++;
	this->routeData.push_back(trans);
}

void Route::Print()
{
	cout << "<Route " << id << ">" << endl;
	for (int i = 0; i < cnt; i++)
	{
		cout << '(';
		routeData[i]->Print();
		cout << ')' << endl;
	}
}

double Route::Dist()
{
	double dist = 0;
	for (int i = 0; i < cnt; i++)
	{
		dist += routeData[i]->Dist();
	}
	return dist;
}

int Route::Cost()
{
	int cost = 0;
	for (int i = 0; i < cnt; i++)
	{
		cost += routeData[i]->Cost();
	}
	return cost;
}

double Route::Work()
{
	double work = 0;
	for (int i = 0; i < cnt; i++)
	{
		work += routeData[i]->Work();
	}
	return work;
}

double Route::Time()
{
	double time = 0;
	for (int i = 0; i < cnt; i++)
	{
		time += routeData[i]->Time();
	}
	return time;
}