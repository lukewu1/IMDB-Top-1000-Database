#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include "MovieHashTable.hpp"
#include "DirectorSkipList.hpp"

using namespace std;

// Function prototypes
MovieNode* parseMovieLine(string line);
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList);
void display_menu();


// Main function
int main(int argc, char* argv[]) {
    // TODO
    int tablesize = stoi(argv[2]);
    int listsize = stoi(argv[3]);
    MovieHashTable obj(tablesize);
    DirectorSkipList obj2(listsize, 10);
    int input = 0;
    readMovieCSV(argv[1], obj, obj2);
    cout << "Number of collisions: " << obj.getCollisions() << endl;
    while(input != 5){
        display_menu();
        cin >> input;
        if(input == 1){
            string movie = "";
            cout << "Enter movie name: ";
            cin.ignore();
            getline(cin, movie);
            MovieNode* temp = obj.search(movie);
            if(temp == nullptr) cout << "Enter a valid movie name." << endl;
            else{
                cout << "The Director of " << movie << " is " << temp->director << endl;
            }
        }
        else if(input == 2){
            string directorname = "";
            string directorlast = "";
            cout << "Enter director's name: ";
            cin.ignore();
            getline(cin, directorname);
            cout << "Director name: " << directorname << endl;
            DirectorSLNode* temp = obj2.search(directorname);
            if(!temp){
                 cout << "Enter a valid director name." << endl;
            }
            else{
                cout << directorname << " directed " << temp->count << " movies" << endl;
            }
        }
        else if(input == 3){
            string movie = "";
            cout << "Enter movie name: ";
            cin.ignore();
            getline(cin, movie);
            MovieNode *temp = obj.search(movie);
            if(temp == nullptr) cout << "Enter a valid movie name." << endl;
            else{
                cout << temp->title << " was directed by: " << temp->director << " and grossed " << temp->revenue << " Million Dollars." << endl;
                cout << "Summary: " << temp->description << endl;
            }
        }
        else if(input == 4){
            string directorname = "";
            cout << "Enter a director name: ";
            cin.ignore();
            getline(cin, directorname);
            DirectorSLNode* temp = obj2.search(directorname);
            if(!temp){
                cout << "Enter a valid director name." << endl;
             }
             else{
                cout << directorname << " directed the following movies: " << endl;
                for(int i = 0; i < temp->movies.size(); i++){
                    cout << "(" << i << ")" << " " << temp->movies[i]->title << endl;
                }
             }
        }
        else if(input == 5){
            cout << "Quitting... Goodbye!" << endl;
            return 0;
        }
        else{
            cout << "Please enter a valid option" << endl;
            return 0;
        }
    }
    return 0;
}

// Function to parse a CSV line into a MovieNode object
MovieNode* parseMovieLine(string line) {
    stringstream ss(line);
    vector<string> fields;
    string field;

    // Loop through the characters in the line
    bool in_quotes = false;
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == '\"') {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            // add field to vector and reset for next field
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
            // handle double quotes inside a quoted field
            if (in_quotes && c == '\"' && i < line.length() - 1 && line[i+1] == '\"') {
                field += '\"'; // add the second double quote and skip it
                ++i;
            }
        }
    }
    fields.push_back(field);

    if (fields.size() != 12) {
        cerr << "Error: Invalid movie line format" << line << endl;
        return nullptr;
    }

    int rank = stoi(fields[0]);
    string title = fields[1];
    string genre = fields[2];
    string description = fields[3];
    string director = fields[4];
    string actors = fields[5];
    int year = stoi(fields[6]);
    int runtime = stoi(fields[7]);
    float rating = stof(fields[8]);
    int votes = stoi(fields[9]);
    float revenue = stof(fields[10]);
    int metascore = stoi(fields[11]);

    // Create a new MovieNode object with the parsed fields
    MovieNode* movie = new MovieNode(rank, title, genre, description, director, actors, year, runtime, rating, votes, revenue, metascore);
    return movie;
}

// Function to read a CSV file into a vector of MovieNode objects
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList) {
    // TODO 
    ifstream input;
    input.open(filename);
    if(input.is_open()){
        string line;
        while(!input.eof()){
            getline(input, line);
            if(line.length()>115){
                MovieNode* temp = parseMovieLine(line);
                movieTable.insert(temp->title, temp);
                directorList.insert(temp->director, temp);
            }
        }
    }
}

// Function to display the menu options
void display_menu() {
    cout << "Please select an option:" << endl;
    cout << "1. Find the director of a movie" << endl;
    cout << "2. Find the number of movies by a director" << endl;
    cout << "3. Find the description of a movie" << endl;
    cout << "4. List the movies by a director" << endl;
    cout << "5. Quit" << endl;
}
