#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_

#include <string>
#include "LinkedList.hpp"
#include "Entry.hpp"
#include "HistoryRecord.hpp"
#include "MyStack.hpp"


class Playlist {
private:
	LinkedList<Entry> entries;	
	MyStack< HistoryRecord > history; 
	/* Generate a random integer such that i ≤ j < n */
	int getRandomNumber(int i, int n) const;

	bool isthere(const std::string &_title) const;
 
public:	
	Playlist();
	
	void load(std::string fileName);

	void insertEntry(const Entry &e); 
	
	void deleteEntry(const std::string &_title);

	void moveLeft(const std::string &title); 

	void moveRight(const std::string &title);

	void reverse(); 

	void undo(); 
	
	void print();

	void printHistory();
};



#endif

