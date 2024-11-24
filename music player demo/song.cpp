// song.cpp
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "song.h"
#include <cstring>
#include <string>

using namespace std;

// ignore any newlines in input
void IgnoreNewLines()
{
	while (cin.peek() == '\n')
		cin.ignore();
}

// default constructor
Song::Song()
{
	strcpy(title, "");
	strcpy(artist, "");
	playtime = 0;
}

Song::Song(const char* t, const char* a, int p)
{
	Set(t, a, p);
}

void Song::Sets(string t, string a, int p) {
	const char* t1 = t.c_str();
	const char* a1 = a.c_str();

	Set(t1, a1, p);
}

void Song::Set(const char* t, const char* a, int p)
{
	if (strlen(t) < MAX_CHARS)
		strcpy(title, t);

	if (strlen(a) < MAX_CHARS)
		strcpy(artist, a);

	if (p > 0)
		playtime = p;
}

// output operator
ostream& operator<<(ostream& os, const Song& song)
{
	// TODO
	int min = song.playtime / 60;
	int sec = song.playtime % 60;

	os << song.title << "/" << song.artist << "/" << min << " minutes " << sec << " seconds";
	return os;
}

// input operator
istream& operator>>(istream& is, Song& song)
{
	// Do not modify this part

	// ignore any newlines
	IgnoreNewLines();

	// read until the comma
	cin.getline(song.title, Song::MAX_CHARS, ',');
	
	// ignore the space in between
	if (cin.peek() == ' ')
		cin.ignore();

	// ignore any newlines
	IgnoreNewLines();

	// read until new line
	cin.getline(song.artist, Song::MAX_CHARS);

	// ignore the space in between
	if (cin.peek() == ' ')
		cin.ignore();

	// ignore any newlines
	IgnoreNewLines();

	// read until new line
	is >> song.playtime;

	return is;
}

// equality test operator
bool operator==(const Song& lhs, const Song& rhs)
{
	// TODO
	bool title = false;
	bool artist = false;
	bool time = false;

	if (_stricmp(lhs.title, rhs.title) == 0)
		title = true;
	

	if (_stricmp(lhs.artist, rhs.artist) == 0) 
		artist = true;
	

	if (lhs.playtime == rhs.playtime)
		time = true;

	return (title && artist && time);
}

