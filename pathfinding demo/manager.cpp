// manager.cpp

#include "manager.h"
#include <iostream>
#include <fstream>
#include <vector>

Manager::Manager()
{
	cntID = 0;
}

void printTitle()
{
	cout << "\t\t ================== " << endl;
	cout << "\t\t|  Travel Manager  |" << endl;
	cout << "\t\t ================== " << endl;
}
void printStart()
{
	cout << "\tSelect input way (1: Manual, 2: File)" << endl;
	cout << ">> ";
}
void printManage()
{
	cout << "\tSelect input way (1: Manual, 2: File) or" << endl;
	cout << "\tSelect Managing method" << endl;
	cout << "\t(A: Print all routes, R: Print single route)" << endl;
	cout << "\t(F: Search best route, S: Sort routes)" << endl;
	cout << ">> ";
}
void Manager::Start()
{
	while (1)
	{
		printTitle();
		if (cntID > 0)
			printManage();
		else
			printStart();
		
		char mode;
		cin >> mode;
		fflush(stdin);

		system("CLS");
		switch (toupper(mode))
		{
		case '1':				// Data Manual input mode
			this->ReadManual();
			break;
		case '2':				// Data File input mode
			routeList.clear(); // new travel. claer the list of routes
			cntID = 0; // initialize id
			this->ReadFile();
			break;
		case 'A':				// Print ALL routes
			this->Print();
			break;

		case 'R':				// Show a specific route's information
			cout << "id of route to print: ";
			int rid;
			cin >> rid;
			this->PrintRoute(rid);
			cout << endl;
			break;
		case 'F':				// Find (Search) Route by constraint
			cout << "Select the constraint to find best one" << endl;
			cout << "0: Distance, 1: Time, 2: Work, 3: Cost" << endl;
			cout << "Mode:";
			int m;
			cin >> m;
			cout << "The best route is" << endl;
			int rid2;
			rid2 = this->FindBestRoute(m);
			this->PrintRoute(rid2);
			cout << endl;
			break;
		case 'S':				// Sort Routes by constraint
			cout << "Select the constraint to sort" << endl;
			cout << "0: Distance, 1: Time, 2: Work, 3: Cost" << endl;
			cout << "Mode:";
			int m2;
			cin >> m2;
			this->Sort(m2);
			cout << endl;
			break;

		case 'Q':				// Quit Program
			cout << "Bye!\n";
			return;
		default:	// Other inputs are not allowed
			cout << "Invalid mode number" << endl;
			continue;
		}
	}
	
}

void printManualInstructions()
{
	cout << "\t(MANUAL INPUT MODE)" << endl;
	cout << "\t0: Finish input mode" << endl;
	cout << "\t1: Walking, 2: Bicycle, 3: Bus, 4: Taxi, 5: Subway" << endl;
	cout << ">> ";
}
void Manager::ReadManual()
{
	printTitle();
	printManualInstructions();

	Route* r = new Route();				// New Route instance
	int t_cnt = 0;			// Number of movements
	while (1)
	{
		int type;
		cin >> type;

		// Stop constructing route by inserting 0
		if (type == 0)
		{
			cout << "Stopped reading route data" << endl;
			this->AddRoute(r);
			system("CLS");
			return;
		}
		
		cout << "Distance of Method " << type << endl;
		cout << ">> ";
		double dist;
		cin >> dist;

		cout << "Speed of Method " << type << endl;
		cout << ">> ";
		double speed;
		cin >> speed;

		////////////////////////////////////////////////
		/// TODO : Get more inputs depending on TYPE ///
		////////////////////////////////////////////////
		double work;
		int cost;

		switch (type)
		{
		case 1:
			cout << "Work of Walking" << endl;
			cout << ">> ";
			cin >> work;

			r->AddTrans(new Walking(dist, speed, work));
			break;

		case 2:
			cout << "Work of Bicycle" << endl;
			cout << ">> ";
			cin >> work;

			r->AddTrans(new Bicycle(dist, speed, work));
			break;
		case 3:
			cout << "Cost of Bus" << endl;
			cout << ">> ";
			cin >> cost;

			r->AddTrans(new Bus(dist, speed, cost));
			break;
		case 4:
			cout << "Cost of Taxi" << endl;
			cout << ">> ";
			cin >> cost;

			r->AddTrans(new Taxi(dist, speed, cost));
			break;
		case 5:
			cout << "Cost of Bus" << endl;
			cout << ">> ";
			cin >> cost;

			r->AddTrans(new Subway(dist, speed, cost));
			break;
		}
		cout << "New Transportation or 0 to finish" << endl;
		cout << ">> ";
	}
}

void printFileInstructions()
{
	cout << "\t(FILE INPUT)" << endl;
	cout << "\tInsert file name" << endl;
	cout << ">> "; 
}
void Manager::ReadFile()
{
	// COMMENT THIS PART WHEN IMPLEMENTATION IS DONE //
	/* 
	system("CLS");
	cout << "Implementation not done" << endl;
	return; 
	*/
	// COMMENT THIS PART WHEN IMPLEMENTATION IS DONE //
	
	printTitle();
	printFileInstructions();
	
	string fname;
	cin >> fname;
	fflush(stdin);

	int T = 0;						// Number of Routes
	int N = 0;						// Number of Transportations
	ifstream in(fname);
	in >> T;

	for (int i = 0; i < T; i++)
	{
		Route* r = new Route();
		in >> N;
		for (int j = 0; j < N; j++)
		{
			int type;
			double dist;
			double speed;
			in >> type >> dist >> speed;
			/////////////////////////
			/// TODO : Get inputs ///
			/////////////////////////
			double work;
			int cost;
			switch (type)
			{
			case 1:
				in >> work;
				r->AddTrans(new Walking(dist, speed, work));
				break;
			case 2:
				in >> work;
				r->AddTrans(new Bicycle(dist, speed, work));
				break;
			case 3:
				in >> cost;
				r->AddTrans(new Bus(dist, speed, cost));
				break;
			case 4:
				in >> cost;
				r->AddTrans(new Taxi(dist, speed, cost));
				break;
			case 5:
				in >> cost;
				r->AddTrans(new Subway(dist, speed, cost));
				break;
			}
		}
		this->AddRoute(r);
	}
}

void Manager::AddRoute(Route* r)
{
	this->cntID++;
	r->SetID(this->cntID);
	this->routeList.push_back(r);
}
void Manager::Print()
{
	for (int i = 0; i < cntID; i++)
	{
		this->routeList[i]->Print();
	}
}

/////////////////////////////////
//// Added Manager Functions ////
/////////////////////////////////
void Manager::PrintRoute(int rid)
{
	rid -= 1; // id starts with one, while index starts with zero
	routeList[rid]->Print();
	cout << "Distance:" << routeList[rid]->Dist() << ", Time:" << routeList[rid]->Time() << ", Work:" << routeList[rid]->Work() << ", Cost:" << routeList[rid]->Cost();
}
int Manager::FindBestRoute(int mode)
{
	int ans = 0; //answer

	switch (mode)
	{
	case(0):   // least distance
		for (int i = 0; i < routeList.size(); i++) {                     // through loop, find index which has least value
			if (routeList[ans]->Dist() > routeList[i]->Dist()) {
				ans = i;
			}
		}
		break;
	case(1):  // least time
		for (int i = 0; i < routeList.size(); i++) {
			if (routeList[ans]->Time() > routeList[i]->Time()) {
				ans = i;
			}
		}
		break;
	case(2): // least work
		for (int i = 0; i < routeList.size(); i++) {
			if (routeList[ans]->Work() > routeList[i]->Work()) {
				ans = i;
			}
		}
		break;
	case(3): // least cost
		for (int i = 0; i < routeList.size(); i++) {
			if (routeList[ans]->Cost() > routeList[i]->Cost()) {
				ans = i;
			}
		}
		break;
	default:
		break;
	}
	return ans + 1; // id starts with one, while index starts with zero
}

/*


int* Manager::FindRoutes(int mode, double pivot)
{
	int* result = new int[];
	return result;
}

I'm gonna use simple bubble sort, not quick sort. So, this code is unnecessary

*/

void Manager::Sort(int mode)
{
	vector<int> ans;    // answer sequence
	for (int i = 0; i < routeList.size(); i++) {
		ans.push_back(i);
	}


	switch (mode)
	{
	case(0):   // least distance
		for (int i = 0; i < ans.size(); i++) {
			for (int j = i + 1; j < ans.size(); j++) {    // bubble sort
				if (routeList[ans[j]]->Dist() < routeList[ans[i]]->Dist()) {    //swap when distance is smaller
					int temp = ans[i];
					ans[i] = ans[j];
					ans[j] = temp;
				}
			}
		}

		for (int i = 0; i < routeList.size(); i++) {
			cout << ans[i]+1 << "(d:" << routeList[ans[i]]->Dist() << ") ";  // print the result
		}
		break;
	case(1):  // least time
		for (int i = 0; i < ans.size(); i++) {
			for (int j = i + 1; j < ans.size(); j++) {    // bubble sort
				if (routeList[ans[j]]->Time() < routeList[ans[i]]->Time()) {    //swap when time is smaller
					int temp = ans[i];
					ans[i] = ans[j];
					ans[j] = temp;
				}
			}
		}
			
		for (int i = 0; i < routeList.size(); i++) {
			cout << ans[i]+1 << "(t:" << routeList[ans[i]]->Time() << ") ";  // print the result
		}
		break;
	case(2): // least work
		for (int i = 0; i < ans.size(); i++) {
			for (int j = i + 1; j < ans.size(); j++) {    // bubble sort
				if (routeList[ans[j]]->Work() < routeList[ans[i]]->Work()) {    //swap when work is smaller
					int temp = ans[i];
					ans[i] = ans[j];
					ans[j] = temp;
				}
			}
		}

		for (int i = 0; i < routeList.size(); i++) {
			cout << ans[i]+1 << "(w:" << routeList[ans[i]]->Work() << ") ";  // print the result
		}
		break;
	case(3): // least cost
		for (int i = 0; i < ans.size(); i++) {
			for (int j = i + 1; j < ans.size(); j++) {    // bubble sort
				if (routeList[ans[j]]->Cost() < routeList[ans[i]]->Cost()) {    //swap when cost is smaller
					int temp = ans[i];
					ans[i] = ans[j];
					ans[j] = temp;
				}
			}
		}
			
		for (int i = 0; i < routeList.size(); i++) {
			cout << ans[i]+1 << "(c:" << routeList[ans[i]]->Cost() << ") ";  // print the result
		}
		break;
	default:
		break;
		}
}