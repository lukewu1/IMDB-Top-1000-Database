#include<iostream>
#include <vector>
#include "DirectorSkipList.hpp"
using namespace std;

// Constructor for DirectorSkipList with default capacity and levels
DirectorSkipList::DirectorSkipList() {
    capacity = DEFAULT_CAPACITY;
    levels = DEFAULT_LEVELS;
    level = 0;
    size = 0;
    head = new DirectorSLNode("noname", DEFAULT_LEVELS);
}

// Constructor for DirectorSkipList with given capacity and levels
DirectorSkipList::DirectorSkipList(int _cap, int _levels) {
    capacity = _cap;
    levels = _levels;
    level = 0;
    size = 0;
    head = new DirectorSLNode("noname", DEFAULT_LEVELS);
}

// Destructor for DirectorSkipList that deletes all nodes in the skip list (but not the MovieNodes, which are shared with other data structures)
DirectorSkipList::~DirectorSkipList() {
    DirectorSLNode* temp = head;
    DirectorSLNode* prev = nullptr;
    while(temp != nullptr){
        prev = temp;
        temp = temp->next[0];
        delete prev;
        prev = nullptr;
    }
}

// Inserts a movie node into the skip list with the specified director
void DirectorSkipList::insert(string director, MovieNode* _movie) {
    DirectorSLNode* curr = head;
    
    vector<DirectorSLNode*> prev(DEFAULT_LEVELS + 1, nullptr);

    for(int i = level; i >= 0; i--){
        while((curr->next[i] != nullptr) && (curr->next[i]->director.compare(director) < 0)){
            curr = curr->next[i];
        }
        prev[i] = curr;
    }
    curr = curr->next[0];

    if((curr == nullptr) || (curr->director.compare(director) !=0)){
        //cout << "Director to be added is: " << director << endl;
        int n_levels = 1;
        while((n_levels < DEFAULT_LEVELS) && (rand()%2 == 0)){
            n_levels++;
        }

        if(n_levels > level){
            for(int i = level + 1; i <= n_levels; i++){
                prev[i] = head;
            }
            level = n_levels;
        }

        DirectorSLNode* newNode = new DirectorSLNode(director, n_levels);
        newNode->movies.push_back(_movie);

        for(int i = 0; i <= n_levels; i++){
            if(prev[i] != nullptr){
                newNode->next[i] = prev[i]->next[i];
                prev[i]->next[i] = newNode;
            }
        }
    }
    else if(curr->director == director){
        curr->movies.push_back(_movie);
        curr->count++;
    }
}

// Searches for a node in the skip list with the specified director
DirectorSLNode *DirectorSkipList::search(string director) {
    DirectorSLNode* curr = head;

    for(int i = level; i >= 0; i--){
        while((curr->next[i] != nullptr) && (curr->next[i]->director < director)){
            curr = curr->next[i];
        }
    }

    curr = curr->next[0];

    if(curr->director == director) return curr;
    else{
        return nullptr;
    }
}

// Pretty-prints the skip list
void DirectorSkipList::prettyPrint() {
    DirectorSLNode* node = nullptr;
    for(int i = 0; i <= level; i++){
        node = head->next[i];
        cout << "Level " << i << ": ";
        while(node!=nullptr){
            cout << node->director << "(" << node->count << ") " << " ";
            node = node->next[i];
        }
        cout << endl;
    }
}
