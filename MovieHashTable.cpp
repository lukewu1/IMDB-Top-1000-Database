#include<iostream>
#include <vector>
#include "MovieHashTable.hpp"
using namespace std;

// Constructor for MovieHashTable with default size THIS FUNCTION IS DONE ----
MovieHashTable::MovieHashTable() {
    table_size = DEFAULT_HTABLE_CAPACITY;
    table = new MovieNode *[table_size];
    n_collisions = 0;
    for(int i = 0; i < table_size; i++){
        table[i] = nullptr;
    }
}

// Constructor for MovieHashTable with given size THIS FUNCTION IS DONE ----
MovieHashTable::MovieHashTable(int s) {
    table_size = s;
    table = new MovieNode *[table_size];
    n_collisions = 0;
    for(int i = 0; i < table_size; i++){
        table[i] = nullptr;
    }
}

// Destructor for MovieHashTable that deletes all nodes in the hash table THIS FUNCTION IS DONE ----
MovieHashTable::~MovieHashTable() {
    MovieNode *curr = nullptr;
    MovieNode *prev = nullptr;
    for(int i = 0; i < table_size; i++){
        curr = table[i];
        prev = nullptr;
        while(curr != nullptr){
            prev = curr;
            curr = curr->next;
            delete prev;
            prev = nullptr;
        }
    }
    delete[] table;
}

// Hash function for MovieHashTable that returns an index in the hash table for a given movie title.
// Students must use their identikey to come up with a creative hash function that minimizes collisions
// for the given IMDB-Movie database to ensure efficient insertion and retrieval of movie nodes.
int MovieHashTable::hash(string title) { //THIS FUNCTION IS DONE
    int index = 0;
    int tablesize = 0;
    string identikey = "luwu8831";

    for(int i = 0; i < title.size(); i++){
        index = index + title[i];
    }

    for(int i = 0; i < identikey.size(); i++){
        tablesize = tablesize + identikey[i];
    }
    return index%tablesize;
}

// Inserts a movie node into the hash table with the specified title
void MovieHashTable::insert(string title, MovieNode* movie) {
    MovieNode *temp = search(title);
    if(temp != nullptr){
        //cout << "Title already exists" << endl;
        temp->next = movie;
        setCollisions();
        return;
    }
    else{
        MovieNode *newNode = movie;
        MovieNode *head = table[hash(title)];
        newNode->next = head;
        table[hash(title)] = newNode;
    }
}

// Searches for a node in the hash table with the specified title
MovieNode* MovieHashTable::search(string title) { //THIS FUNCTION IS DONE
    int index = hash(title);
    if(table[index] == nullptr) return nullptr;

    MovieNode *temp = table[index];

    while(temp!=nullptr){
        if(temp->title == title) return temp;
        temp = temp->next;
    }
    return nullptr;
}

// Returns the number of collisions that have occurred during insertion into the hash table
int MovieHashTable::getCollisions() {
    return n_collisions;
}

// Increments the number of collisions that have occurred during insertion into the hash table
void MovieHashTable::setCollisions() {
    n_collisions = n_collisions + 1;
}

void MovieHashTable::printHashTable() { //I'm using this just to check if everything is correct(used with small file)
    for (int i = 0; i < table_size; i++) {
      if (table[i] != 0) {
	    cout << "[" << i << "] ";
	    MovieNode* curr = table[i];
	    while (curr != 0) {
	    cout << "-> Title: " << curr->title;	  
	    curr = curr->next;
	    }
	    cout << endl;
      }
      else cout << "[" << i << "] -> Empty" << endl;
    }
}