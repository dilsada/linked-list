#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Playlist.hpp"
#include "Entry.hpp"

using namespace std;


Playlist::Playlist()
{
    srand(15);
}

int Playlist::getRandomNumber(int i, int n) const
{
    int range=n-i;
    int random = rand() % range + i;
    return random;
}

void Playlist::print()
{
    cout << "[PLAYLIST SIZE=" << entries.getSize() <<"]";
    entries.print();
}
void Playlist::printHistory()
{
    cout<<"[HISTORY]";
    history.print();
}


void Playlist::insertEntry(const Entry &e){
	
	if(entries.isEmpty()){
		entries.insertNode(NULL, e);
	}
	else{
		Node<Entry>* tmp = entries.getTail();
		entries.insertNode(tmp,e);
	}

	HistoryRecord insertion(INSERT,e);
	history.push(insertion);

}

bool Playlist::isthere(const std::string &_title) const{
	Node<Entry>* tmp = entries.getHead();
	if(tmp == NULL)
		return false;
	else{
		while(tmp != NULL){

			if(tmp->getData().getTitle() == _title)				
				return true;
			else
				tmp = tmp->getNext();
		}
		return false;
	}
}


void Playlist::deleteEntry(const std::string &_title){
	Node<Entry>* tmp = entries.getHead();

	if(isthere(_title)){
		
		if(tmp->getData().getTitle() == _title){
			Entry e(_title,tmp->getData().getGenre(),tmp->getData().getYear());
			HistoryRecord deletion(DELETE,e);
			history.push(deletion);
			
			
			entries.deleteNode(NULL);
			return;
		}

		else{
			Node<Entry>* prev = tmp;
			tmp = tmp->getNext();
			while(tmp != NULL){
				if(tmp->getData().getTitle() == _title){
					
					Entry e(_title,tmp->getData().getGenre(),tmp->getData().getYear());
					HistoryRecord deletion(DELETE,e);
					history.push(deletion);
					
					entries.deleteNode(prev);
					return;
				}
				else{
					tmp = tmp->getNext();
					prev = prev->getNext();
				}
			}
		} 
	}

}


void Playlist::load(std::string fileName){
	ifstream file;
	string line;

	file.open(fileName.c_str());

	while(file.good()){

		getline(file,line);

		size_t first = line.find(";");
		string _title = line.substr(0,first);
		size_t second = line.rfind(";");
		string _genre = line.substr(first+1,second-first-1);
		string _year = line.substr(second+1);

		Entry e(_title,_genre,_year);
		insertEntry(e);

	}

	file.close();

}



void Playlist::moveLeft(const std::string &title){
	if(isthere(title)){
		Node<Entry>* a = entries.getHead();
		
		if(a->getData().getTitle() == title)
			return;

		else if(a->getNext()->getData().getTitle() == title){
			Node<Entry>* tmp = a->getNext();
			a->setNext(tmp->getNext());
			tmp->setNext(a);
			entries.setHead(tmp);
			return;
		}
		else{
			
			Node<Entry>* b = a->getNext();
			Node<Entry>* tmp = b->getNext();

			while(tmp->getData().getTitle() != title){
				tmp = tmp->getNext();
				b = b->getNext();
				a = a->getNext();
			}

			a->setNext(tmp);
			b->setNext(tmp->getNext());
			tmp->setNext(b);
		}

	}

}

void Playlist::moveRight(const std::string &title){
	if(isthere(title)){
		Node<Entry>* tmp = entries.getHead();

		if(tmp->getData().getTitle() == title){
			Node<Entry>* a = tmp->getNext();
			tmp->setNext(a->getNext());
			a->setNext(tmp);
			entries.setHead(a);
		}

		else{
			Node<Entry>* prev = tmp;
			tmp = tmp->getNext();

			while(tmp->getData().getTitle() != title){
				tmp = tmp->getNext();
				prev = prev->getNext();
			}

			if(tmp->getNext() == NULL)
				return;
			else{
				Node<Entry>* a = tmp->getNext();
				tmp->setNext(a->getNext());
				a->setNext(tmp);
				prev->setNext(a);

			}
		}
	}
}


void Playlist::reverse(){
	if (entries.getHead()== NULL)
		return;

	Node<Entry>* prev = NULL;
	Node<Entry>* curr = entries.getHead();
	Node<Entry>* next = NULL;

	while(curr != NULL){
		next = curr->getNext();
		curr->setNext(prev);
		prev = curr;
		curr = next;
	}
	entries.setHead(prev);

	HistoryRecord revers(REVERSE);
	history.push(revers);
}

void Playlist::undo(){
	if (history.Top()->getData().getOperation() == INSERT){

		deleteEntry(history.Top()->getData().getEntry().getTitle());
		history.pop();
	}

	else if(history.Top()->getData().getOperation() == DELETE){
		insertEntry(history.Top()->getData().getEntry().getTitle());
		history.pop();
	}
	else if(history.Top()->getData().getOperation() == REVERSE){
		reverse();
		history.pop();
	}
	else
		return;
}