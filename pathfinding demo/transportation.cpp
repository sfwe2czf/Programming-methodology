#include "transportation.h"

void Transportation::Print()
{
	cout << "d:" << this->distance << ", " 
		 << "v:" << this->speed;
}

double FreeTrans::Work()
{
	return work * distance;
}
void FreeTrans::Print()
{
	Transportation::Print();
	cout << ", w:" << this->Work();
}

void Walking::Print()
{
	cout << "Walking=";
	FreeTrans::Print();
}

/////////////////////////////////////////////////
//////// TODO : Write more class methods ////////
/////////////////////////////////////////////////
void Bicycle::Print()
{
	cout << "Bicycle=";
	FreeTrans::Print();
}

int PaidTrans::Cost()
{
	return ceil(cost * distance);
}
void PaidTrans::Print()
{
	Transportation::Print();
	cout << ", c:" << this->Cost();
}

void Bus::Print()
{
	cout << "Bus=";
	PaidTrans::Print();
}

void Taxi::Print()
{
	cout << "Taxi=";
	PaidTrans::Print();
}

void Subway::Print()
{
	cout << "Subway=";
	PaidTrans::Print();
}