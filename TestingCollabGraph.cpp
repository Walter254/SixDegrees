/*
 * TestingSixDegrees.cpp
 *
 * COMP 15 Project 2: Six Degrees of Collaboration
 * Purpose:
 *      A testing file for the Six degrees program. This file has a main 
 *      with an instance of the CollabGraph object. The object is used to call
 *      the public member functions and the output is displayed on the
 *      command line
 * 
 * by Walter Wagude, 7 DEC 2021
 */
 
#include <fstream>
#include <iostream>
#include "Artist.h"
#include "CollabGraph.h"

using namespace std;

int main(int argc, char *argv[])
{
    // If the number of commands line arguments is not 1,2, or 3
    if (argc < 2 or argc > 4){
        cerr << "Usage: SixDegrees dataFile" << 
                 " [commandFile] [outputFile]" << endl;
        exit(EXIT_FAILURE);
    }
    
    string filename;
    filename = argv[1];
    
    // open file
    ifstream input_file;
    input_file.open(filename);
    
    // when a file cannot be opened
    if (not input_file.is_open()){
        cerr << filename << " cannot be opened." << endl;
        exit(EXIT_FAILURE);
    }
    
    CollabGraph collabgraph;
    // a vector to store the artists from the file
    vector<Artist> artists;
    
    string artistName = "";
    string artistSong = "";
    
    //read from file
    while (getline(input_file, artistName)){
        // create an instance of a artist object
        Artist create_artist(artistName);
        // add the artists' songs
        while (getline(input_file, artistSong)){
            if (artistSong != "*"){
                create_artist.add_song(artistSong);
            } else {
                // add artist to the vector
                artists.push_back(create_artist);
                break;
            }
    
        }
    
    }
    
    Artist test;
    Artist test_source;
    Artist test_destination;
    for (size_t i = 0; i < artists.size(); i++){
        //cout << artists[i] << endl;
        test = artists[0];
        test_source = artists[0];
        test_destination = artists[2];
        
        //cout << artists[i].in_song("Make You Feel My Love") << endl;
    }
    //cout << test << endl;
    // 
    collabgraph.populate_graph(artists);
    //collabgraph.print_graph(cout);
    vector<Artist> neighbors;
    neighbors = collabgraph.get_vertex_neighbors(test);
    cout << "The neighbors of " << test << " are: " << endl;
    
    for (size_t i = 0; i < neighbors.size(); i++){
        cout << neighbors[i] << endl;
    
        //cout << artists[i].in_song("Make You Feel My Love") << endl;
    }
    // collabgraph.mark_vertex(test_source);
    // collabgraph.mark_vertex(test_destination);
    // stack<Artist> path;
    // path = collabgraph.report_path(test_source, test_destination);
    // cout << "path from " << test_source << " to " << 
    // test_destination << endl;
    // while (!path.empty()){
    //     cout << "here " << path.top() << endl;
    //     path.pop();
    // }
    
     
    input_file.close();
    return 0;
}
