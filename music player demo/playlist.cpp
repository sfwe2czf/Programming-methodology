//playlist.cpp

#include <iostream>
#include <cstring>
#include <iostream>
#include <string>
#include <Windows.h>
#include <ctime>
#include "playlist.h"
#include <fstream>
#include <random>
#include <algorithm>
#include <iterator>

using namespace std;

// TODO
void eraseLines(int count);
void LCD(int min, int sec);
void shape(int num);

PlayList::PlayList()
{
	numofSong = 0;
	play_index = 1;
}

PlayList::~PlayList()
{

}

void PlayList::AddSong() {
	cout << "==Enter song to add==" << endl;

	Song s;
	cin >> s;

	numofSong += 1;
	v.push_back(s);
	
	system("CLS");
	cout << "Added" << endl;
	return;
}

void PlayList::DeleteSong() {
	cout << "==Enter song to delete==" << endl;

	Song s;
	cin >> s;

	for (int i = 0; i < numofSong; i++) {
		if (v[i] == s) {
			if (i < play_index) {
				play_index -= 1;
			}
			else if (i == play_index && i == v.size() - 1) {
				play_index = 1;
			}

			v.erase(v.begin() + i);

			numofSong -= 1;
			system("CLS");
			cout << "deleted" << endl;

			return;
		}
	}

	system("CLS");
	cout << "Error: No such song" << endl;
	return;
}

void PlayList::ReadList() {
	cout << "input file name: " << endl;

	string s;
	cin >> s;

	//read file
	fstream f;
	f.open(s, ios::in);

	if (!f.is_open()) {
		system("CLS");
		cout << "error: no such file name" << endl;
		cout << "return to menu";
		return;
	}


	string d;

	string t;
	string a;
	int p;

	int i = 1;
	while (getline(f, d)) {
		if (i % 4 == 1) {
			numofSong += 1;
			t = d;
			Song k;
			v.push_back(k);
			
		}
		if (i % 4 == 2) {
			a = d;
		}
		if (i % 4 == 3) {
			p = stoi(d);
			v.back().Sets(t, a, p);
		}

		i++;
	}
	
	f.close();
	system("CLS");
	cout << "read" << endl;
	return;
}

void PlayList::WriteList() const {
	cout << "input file name: " << endl;

	string s;
	cin >> s;

	//read file
	fstream f;
	f.open(s, ios::out);

	for (int i = 0; i < numofSong; i++) {
		f << v[i].title << endl;
		f << v[i].artist << endl;
		f << v[i].playtime << endl;
		f << "@" << endl;
	}
	f.close();
	system("CLS");
	cout << "writed" << endl;
	return;
}

void PlayList::ShowAll() const{
	system("CLS");
	cout << "Showing all songs" << endl;
	cout << "---------------------------" << endl;

	for (int i = 0; i < numofSong; i++) {
		cout << i + 1 << ". " << v[i] << endl;
	}

	cout << "---------------------------" << endl;
	cout << "Press q to return" << endl;
	while (1) {
		string q;
		cin >> q;
		if (q == "q" || q == "Q") {
			system("CLS");
			break;
		}
	}
	return;
};

void PlayList::ShowStatus() const {
	system("CLS");

	int totaltime = 0;
	for (int i = 0; i < numofSong; i++) {
		totaltime += v[i].playtime;
	}
	int min = totaltime / 60;
	int sec = totaltime % 60;

	cout << "Showing status" << endl;
	cout << "---------------------------" << endl;
	cout << "Number of songs in the list: " << numofSong << endl;
	cout << "Current Song index         : " << play_index << endl;
	cout << "Total playtime             : " << min << " minutes " << sec << " seconds" << endl;
	cout << "---------------------------" << endl;
	cout << "Press q to return" << endl;
	while (1) {
		string q;
		cin >> q;
		if (q == "q" || q == "Q") {
			system("CLS");
			break;
		}
	}
	return;
};

void PlayList::Play(){
	system("CLS");
	cout << "------------" << endl;
	cout << "Playing setup" << endl;
	cout << "------------" << endl;
	cout << "Enter play mode: " << endl;
	string type;
	int number;
	cin >> type;
	cout << "Enter number of songs play" << endl;
	cin >> number;
	system("CLS");

	if (numofSong == 0) {
		cout << "----------" << endl;
		cout << "Now playing" << endl;
		cout << "----------" << endl;
		cout << "Total number of songs      : " << number << endl;
		cout << "Total playtime             : " << 0 << " minutes " << 0 << " seconds" << endl;
		cout << "Play mode                  : Normal" << endl;
		cout << "-----------------------" << endl;
		cout << "Press q to return" << endl;
		while (1) {
			string q;
			cin >> q;
			if (q == "q" || q == "Q") {
				system("CLS");
				break;
			}
		}
		return;
	}



	if (type == "N"||type=="n") {
		int totalplaytime = 0;
		for (int i = 0; i < number; i++) {
			int j = i;
			j += play_index-1;
			j %= numofSong;
			totalplaytime += v[j].playtime;
		}
		int min = totalplaytime/60;
		int sec = totalplaytime%60;

		for (int k = 0; k < number; k++) {
			int j = k;
			int i = k;
			i += play_index-1;
			i %= numofSong;

			system("CLS");
			cout << "----------" << endl;
			cout << "Now playing" << endl;
			cout << "----------" << endl;
			cout << "Total number of songs      : " << number << endl;
			cout << "Total playtime             : " << min << " minutes " << sec << " seconds" << endl;
			cout << "Play mode                  : Normal" << endl;
			cout << "Current playing            : " << j + 1 << " / " << number << endl << endl;

			cout << i + 1 << ". " << v[i] << endl << endl;

			const int nTick = GetTickCount();
			int nTime;
			int counter = 0;
			while (true) {
				nTime = (GetTickCount() - nTick) / 1000;
				int mins = nTime / 60;
				int secs = nTime % 60;

				if (nTime == v[i].playtime + 1) {
					cout << "\r--------------";
					cout << endl;
					break;
				}
				if ((GetTickCount() - nTick) % 1000 == 0) {
					if (counter != 0) {
						eraseLines(5);
					}
					counter += 1;
					LCD(mins, secs);
				
				}

			}	
		}
		play_index = (play_index + number) % numofSong;
		if (play_index == 0)
			play_index = numofSong;
	}
	else if (type == "S" || type =="s") {
		if (number > numofSong) {
			number = numofSong;
		}

		vector<int> x;
		for (int i = 0; i < numofSong; i++) {
			x.push_back(i);
		}

		random_device rd;
		mt19937 g(rd());

		shuffle(x.begin(), x.end(), g);

		int totalplaytime = 0;
		for (int i = 0; i < number; i++) {
			int j = x[i];
			totalplaytime += v[j].playtime;
		}
		int min = totalplaytime / 60;
		int sec = totalplaytime % 60;

		for (int k = 0; k < number; k++) {
			int j = k;
			int i = x[k];

			
				system("CLS");
				cout << "----------" << endl;
				cout << "Now playing" << endl;
				cout << "----------" << endl;
				cout << "Total number of songs      : " << number << endl;
				cout << "Total playtime             : " << min << " minutes " << sec << " seconds" << endl;
				cout << "Play mode                  : Shuffle" << endl;
				cout << "Current playing            : " << j + 1 << " / " << number << endl << endl;

				cout << i + 1 << ". " << v[i] << endl << endl;

				const int nTick = GetTickCount();
				int nTime;
				int counter = 0;
				while (true) {
					nTime = (GetTickCount() - nTick) / 1000;
					int mins = nTime / 60;
					int secs = nTime % 60;

					if (nTime == v[i].playtime + 1) {
						cout << "\r--------------";
						cout << endl;
						break;
					}
					if ((GetTickCount() - nTick) % 1000 == 0) {
						if (counter != 0) {
							eraseLines(5);
						}
						counter += 1;
						LCD(mins, secs);

					}

				}
			
			

		}
		play_index = (x[number - 1]+2)%numofSong;
		if (play_index == 0)
			play_index = numofSong;


	}
	eraseLines(6);
	cout << "-----------------------" << endl;
	cout << "Press q to return" << endl;
	while (1) {
		string q;
		cin >> q;
		if (q == "q" || q == "Q") {
			system("CLS");
			break;
		}
	}
	return;
};

void PlayList::Search() const{
	system("CLS");
	cout << "Now search for what?" << endl;
	cout << "A-artist" << endl;
	cout << "T-title" << endl;
	cout << "else-return to menu" << endl;
	string s;
	cin >> s;
	if (s == "t" || s == "T") {
		string k;
		cout << "Enter keywords : ";
		cin >> k;
		system("CLS");
		cout << "result for title : " << k << " found (alphabetical order) :" << endl << endl;

		std::for_each(k.begin(), k.end(), [](char& c) {
			c = ::toupper(c);
			});

		vector<Song> ans;

		for (int i = 0; i < numofSong; i++) {
			string t = v[i].title;
			std::for_each(t.begin(), t.end(), [](char& c) {
				c = ::toupper(c);
				});
			if (t.find(k) != -1) {
				ans.push_back(v[i]);
			}
		}

		if (ans.size() == 0) {
			cout << "---------------------------" << endl;
			cout << "Press q to return" << endl;
			string q;
			cin >> q;
			if (q == "q" || q == "Q")
				system("CLS");
			return;
		}

		Song temp;

		for (int i = 0; i < ans.size()-1; ++i) {
			for (int j = 0; j < ans.size() - 1 - i; ++j) {
				string a = ans[j].title;
				std::for_each(a.begin(), a.end(), [](char& c) {
					c = ::toupper(c);
					});
				string b = ans[j + 1].title;
				std::for_each(b.begin(), b.end(), [](char& c) {
					c = ::toupper(c);
					});
				if (a>b) {
					temp = ans[j];
					ans[j] = ans[j+1];
					ans[j+1] = temp;
				}
				else if (a == b) {
					string a = ans[j].artist;
					std::for_each(a.begin(), a.end(), [](char& c) {
						c = ::toupper(c);
						});
					string b = ans[j + 1].artist;
					std::for_each(b.begin(), b.end(), [](char& c) {
						c = ::toupper(c);
						});
					if (a > b) {
						temp = ans[j];
						ans[j] = ans[j + 1];
						ans[j + 1] = temp;
					}
				}
			}
		}

		for (int i = 0; i < ans.size(); i++) {
			cout << i + 1 << ". " << ans[i] << endl;
		}

		cout << "---------------------------" << endl;
		cout << "Press q to return" << endl;
		string q;
		cin >> q;
		if (q == "q" || q == "Q")
			system("CLS");
		return;
	}
	else if (s == "A" || s == "a") {
		string k;
		cout << "Enter keywords : ";
		cin >> k;
		system("CLS");
		cout << "result for artist : " << k << " found (alphabetical order) :" << endl << endl;
		
		std::for_each(k.begin(), k.end(), [](char& c) {
			c = ::toupper(c);
			});

		vector<Song> ans;

		for (int i = 0; i < numofSong; i++) {
			string t = v[i].artist;
			std::for_each(t.begin(), t.end(), [](char& c) {
				c = ::toupper(c);
				});

			if (t.find(k) != -1) {
				ans.push_back(v[i]);
			}
		}

		if (ans.size() == 0) {
			cout << "---------------------------" << endl;
			cout << "Press q to return" << endl;
			string q;
			cin >> q;
			if (q == "q" || q == "Q")
				system("CLS");
			return;
		}

		Song temp;

		for (int i = 0; i < ans.size() - 1; ++i) {
			for (int j = 0; j < ans.size() - 1 - i; ++j) {
				string a = ans[j].artist;
				std::for_each(a.begin(), a.end(), [](char& c) {
					c = ::toupper(c);
					});
				string b = ans[j + 1].artist;
				std::for_each(b.begin(), b.end(), [](char& c) {
					c = ::toupper(c);
					});
				if (a > b) {
					temp = ans[j];
					ans[j] = ans[j + 1];
					ans[j + 1] = temp;
				}
				else if (a == b) {
					string a = ans[j].title;
					std::for_each(a.begin(), a.end(), [](char& c) {
						c = ::toupper(c);
						});
					string b = ans[j + 1].title;
					std::for_each(b.begin(), b.end(), [](char& c) {
						c = ::toupper(c);
						});
					if (a > b) {
						temp = ans[j];
						ans[j] = ans[j + 1];
						ans[j + 1] = temp;
					}
				}
			}
		}

		for (int i = 0; i < ans.size(); i++) {
			cout << i + 1 << ". " << ans[i] << endl;
		}

		cout << "---------------------------" << endl;
		cout << "Press q to return" << endl;
		while (1) {
			string q;
			cin >> q;
			if (q == "q" || q == "Q") {
				system("CLS");
				break;
			}
		}
		return;
	}
	else {
		system("CLS");
		return;
	}

	return;
};

void LCD(int min, int sec) {
	int num1 = min / 10;
	int num2 = min % 10;
	int num3 = sec / 10;
	int num4 = sec % 10;
	
	shape(num1);
	cout << "\x1b[4A";
	shape(num2);
	cout << "\x1b[4A";
	cout << "\x1b[1B";// set cursor properly
	cout << " * ";
	cout << "\x1b[2B";
	cout << "\x1b[3D";// set cursor properly
	cout << " * ";
	cout << "\x1b[3A";// set cursor properly
	
	shape(num3);
	cout << "\x1b[4A";
	shape(num4);

	// set cursor properly
	return;
}

void eraseLines(int count) {
	if (count > 0) {
		std::cout << "\x1b[2K"; // Delete current line
		// i=1 because we included the first line
		for (int i = 1; i < count; i++) {
			std::cout
				<< "\x1b[1A" // Move cursor up one
				<< "\x1b[2K"; // Delete the entire line
		}
		std::cout << "\r"; // Resume the cursor at beginning of line
	}
}

void shape(int num) {
	if (num == 0) {
		cout << "----";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "|  |";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "|  |";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "|  |";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "----";
	}
	if (num == 1) {
		cout << "    ";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "   |";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "   |";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "   |";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "    ";
	}
	if (num == 2) {
		cout << "----";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "   |";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "----";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "|   ";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "----";
	}
	if (num == 3) {
		cout << "----";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "   |";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "----";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "   |";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "----";
	}
	if (num == 4) {
		cout << "|  |";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "|  |";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "---|";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "   |";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "   |";
	}
	if (num == 5) {
		cout << "----";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "|   ";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "----";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "   |";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "----";
	}
	if (num == 6) {
		cout << "----";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "|   ";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "----";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "|  |";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "----";
	}
	if (num == 7) {
		cout << "----";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "|  |";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "|  |";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "   |";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "   |";
	}
	if (num == 8) {
		cout << "----";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "|  |";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "|--|";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "|  |";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "----";
	}
	if (num == 9) {
		cout << "----";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "|  |";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "|--|";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "   |";
		cout << "\x1b[1B";
		cout << "\x1b[4D";
		cout << "   |";
	}
	
	return;
}