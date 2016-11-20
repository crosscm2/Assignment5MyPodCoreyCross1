#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

class Node {
public:
	string artist;
	string songName;

	Node * next;

	Node(string artist, string name) {
		(*this).artist = artist;
		(*this).songName = name;
		next = nullptr;
	}
};