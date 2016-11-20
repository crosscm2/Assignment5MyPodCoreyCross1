// Assignment5MyPodCoreyCross1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PlayLList.cpp"
#include <vector>
#include <sstream>

vector<string> split(string s, char splitBy) {
	vector<string> artistANDsong;
	stringstream ss;
	ss.str(s);
	string item;
	while (getline(ss, item, splitBy)) {
		artistANDsong.push_back(item);
	}
	return artistANDsong;
}

int main() {
	// Get filename from user
	string fileName;
	cout << "Please enter the name of the file containing all your music: ";
	cin >> fileName;

	// Create PlayLList instance to store all tracks
	PlayLList * playlist = new PlayLList;


	// Open file to read in all songs, line by line. Store each song in the playlist instance
	ifstream infile(fileName);
	string line;
	while (getline(infile, line)) {
		if (line == "") {
			continue;
		}
		vector<string> components = split(line, ',');
		string artist = components[0];
		string song = components[1];
		Node * songNode = new Node(artist, song);
		playlist->addSong(songNode);
	}

	string request = "";
	while (playlist->count > 0 && request != "q") {
		cout << "\nNext song: " << playlist->currentSong() << endl;
		cout << "Enter (p) to play the song, (s) to skip the song, or (d) to delete the song. Enter (q) to quit: ";
		cin >> request;
		playlist->handleRequest(request);
	}
	cout << "\n\nThanks for listening!" << endl;

	// clean up memory once program has terminated
	playlist->savePlaylist(fileName);
	delete playlist;
}