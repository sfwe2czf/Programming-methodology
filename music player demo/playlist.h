
#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include <vector>
#include <Windows.h>
#include "song.h"

using namespace std;


//PlayList ±¸Çö
class PlayList
{
public:
	// TODO
	PlayList();
	~PlayList();

	void AddSong();
	void DeleteSong();
	void ShowAll() const;
	void Play();
	void ShowStatus() const;
	void Search() const;
	void ReadList();
	void WriteList() const;

private:
	int numofSong;
	int play_index;
	vector<Song> v;
};

#endif