#include "stdafx.h"
#include "Node.cpp"
#include <stack>
#include <fstream>

class PlayLList {
public:
	int count;
	Node * head;
	Node * current;
	Node * prev;
	Node * tail;

	PlayLList() {
		count = 0;
		head = nullptr;
		current = nullptr;
		prev = nullptr;
		tail = nullptr;
	}

	~PlayLList() {
		stack<Node *> s;
		Node * temp = head;
		while (temp) {
			s.push(temp);
			temp = temp->next;
		}
		while (s.size() > 0) {
			Node * top = s.top();
			s.pop();
			delete top;
		}
	}

	void printPlayList() {
		Node * temp = head;
		while (temp) {
			cout << temp->artist << " BY " << temp->songName << endl;
			temp = temp->next;
		}
	}

	// Implicitly skips to next song
	bool deleteCurrentSong() {
		if (count == 0) {
			cout << "Playlist is empty :(" << endl;
			return false;
		}
		if (current == head) {
			prev = tail;
			Node * temp = head;
			head = head->next;
			current = head;
			delete temp;
		}
		else if (current == tail) {
			Node * temp = tail;
			tail = prev;
			tail->next = nullptr;
			current = head;
			delete temp;
		}
		else {
			Node * temp = current;
			prev->next = current->next;
			current = prev->next;
			delete temp;
		}
		count--;

		// returns playlists ability to continue serving songs
		return count > 0;
	}

	string currentSong() {
		if (current) {
			return current->songName + " - " + current->artist;
		}
		return "Playlist is empty :(";
	}

	void handleRequest(const string& s) {
		if (s == "q") {
			return;
		}
		if (s == "p") {
			cout << "done playing" << endl;
			nextSong(1);
		}
		else if (s == "s") {
			int n;
			cout << "How many songs would you like to skip? ";
			cin >> n;
			nextSong(n);
		}
		else if (s == "d") {
			deleteCurrentSong();
		}
		else {
			cout << "We couldn't interpret your request! Try again" << endl;
		}
	}

	void savePlaylist(string fileName) {
		ofstream outfile(fileName);
		Node * temp = head;
		while (temp) {
			outfile << temp->artist << "," << temp->songName << endl;
			temp = temp->next;
		}
		outfile.close();
	}

	void nextSong(int n) {
		if (current) {
			while (n) {
				prev = current;
				current = current->next;
				if (!current) {
					current = head;
				}
				n--;
			}
		}
	}

	void addSong(Node * songNode) {
		if (head == nullptr) {
			head = songNode;
			tail = songNode;
			current = songNode;
		}
		else {
			tail->next = songNode;
			tail = tail->next;
		}
		count++;
	}
};