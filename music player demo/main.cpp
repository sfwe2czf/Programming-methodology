#include <iostream>
#include "playlist.h"

using namespace std;

bool Menu(PlayList& play_list)
{
	bool good;

	do
	{
		good = true;

		cout << "\n\nPlayList Program!\n"
			<< "\tA - Add a song\n"
			<< "\tD - Delete a song\n"
			<< "\tP - Play a song\n"
			<< "\tS - Show all songs\n"
			<< "\tT - Show playlist status\n"
			<< "\tF - Search\n"
			<< "\tR - Read a playlist\n"
			<< "\tW - Save a playlist\n"
			<< "\tQ - Quit\n: ";

		char choice;
		cin >> choice;
		fflush(stdin);

		switch (toupper(choice))
		{
		case 'A':
			play_list.AddSong();
			break;

		case 'D':
			play_list.DeleteSong();
			break;

		case 'P':
			play_list.Play();
			break;

		case 'S':
			play_list.ShowAll();
			break;

		case 'T':
			play_list.ShowStatus();
			break;

		case 'F':
			play_list.Search();
			break;

		case 'R':
			play_list.ReadList();
			break;
		case 'W':
			play_list.WriteList();
			break;

		case 'Q':
			return false;

		default:
			good = false;
		}
	} while (!good);

	return true;
}

int main()
{
	PlayList play_list;
	while (Menu(play_list))
		;
	return 0;
}