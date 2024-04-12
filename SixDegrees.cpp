/**
 ** SixDegrees.cpp
 **
 ** Project Two: Six Degrees of Collaboration
 **
 ** Purpose:
 **   Populates the CollabGraph and executes a sequence of commands, and
 **   outputs the results.
 **
 ** Created by:
 **   Walter Wagude
 **   5 DEC 2021
 **/

#include <stack>
#include <queue>
#include <fstream>
#include <vector>
#include <iostream>

#include "Artist.h"
#include "CollabGraph.h"
#include "SixDegrees.h"

using namespace std;

/*
* SixDegrees
* Parameters: none
* return: nothing
* purpose: default constructor for the SixDegrees class
*/
SixDegrees::SixDegrees(){
    
}

/*
* ~SixDegrees
* Parameters: none
* return: nothing
* purpose: destruct the SixDegree class
*/
SixDegrees::~SixDegrees(){
    
}

/*
* populate_collabGraph
* Parameters: input stream
* return: nothing
* purpose: populates the CollabGraph using the inputed artists
*/
void SixDegrees::populate_collabGraph(std::istream &input){
    // a vector to store the artists from the file
    vector<Artist> artists;
    // a strings to store information about the artists.
    string artistName = "";
    string artistSong = "";
    
    //read from file
    while (getline(input, artistName)){
        // create an instance of a artist object
        Artist create_artist(artistName);
        // add the artists' songs
        while (getline(input, artistSong)){
            if (artistSong != "*"){
                create_artist.add_song(artistSong);
            } else {
                // add artist to the vector
                artists.push_back(create_artist);
                break;
            }
    
        }

    }
    collab_graph.populate_graph(artists);
}

/*
* command_loop
* Parameters: input file, and an output stream
* return: nothing
* purpose: Executes a sequence of commands and outputs the results
*/
void SixDegrees::command_loop(istream &input, ostream &output){
    
    bool done = false;
    string command;
    
    while(done == false){
        getline(input, command);
        if (command == ""){
            
        } else {
            if(command == "print"){
                print(output);
            } else if (command == "quit"){
                return;
            } else if (command == "bfs"){
                run_traversals(input, "bfs", output);
            } else if (command == "dfs"){
                run_traversals(input, "dfs", output);
            } else if (command == "not"){
                run_traversals(input, "not", output);
            } else {
                cout << command << " is not a command."
                                   " Please try again." << endl;
            }
        }
        if (input.eof())
            done = true;
    }
}

/*
* bfs
* Parameters: two artists, the starting and destination artists, and an output
*             stream
* return: nothing
* purpose: prints the shortest path from the starting artist to the 
* destination artist found with a breadth first search
* Notes: Uses print_collab helper function to print the paths
*/
void SixDegrees::bfs(Artist Start, Artist Destination, ostream &output){
    
    collab_graph.clear_metadata();
    bool Continue = proceed(Start, Destination, output);
    
    if (Continue == false)
        return;
        
    queue<Artist> queue;
    collab_graph.mark_vertex(Start);
    queue.push(Start);
    
    while (not queue.empty()){
        Artist to_explore = queue.front();
        queue.pop();
        // get neighbors of the Artist and store them  in queue2
        vector<Artist> neighbors;
        neighbors = collab_graph.get_vertex_neighbors(to_explore);
        
        while (not neighbors.empty()){
            Artist curr = neighbors.back();
            neighbors.pop_back();
            if (collab_graph.is_marked(curr) != true){
                collab_graph.mark_vertex(curr);
                collab_graph.set_predecessor(curr, to_explore);
                queue.push(curr);
            }
        }
    }
    print_collab(Start, Destination, output);
}

/*
* proceed
* Parameters: two artists, the starting and destination artists, and an output
*             stream
* return: a boolean value
* purpose: a helper function for the traversals
*/
bool SixDegrees::proceed(Artist Start, Artist Destination, 
                         std::ostream &output){
    
    bool check = true;
    
    if (collab_graph.is_vertex(Start) == false){
        output << Start << " was not found in the dataset :(" << endl;
        check = false;    
    }
    
    if (collab_graph.is_vertex(Destination) == false){
        output << Destination << " was not found in the dataset :(" << endl;
        check = false;        
    }
    
    return check;
    
}

/*
* proceed2
* Parameters: vector of artists to be checked, and output stream
* return: a boolean value
* purpose: a helper function for the Not traversal function - checks if the 
*          artists to be excluded are in the dataset
*/
bool SixDegrees::proceed2(std::vector<Artist> exclude, std::ostream &output){
    
    bool check = true;
    
    while (not exclude.empty()){
        Artist curr = exclude.back();
        exclude.pop_back();

        if (collab_graph.is_vertex(curr) == false){
            output << curr << " was not found in the dataset :(" << endl;
            check = false;    
        }
        
    }
    
    return check;    
}

/*
* run_traversals
* Parameters: strings each representing the traversals, input stream, 
*             and an output stream
* return: none
* purpose: a helper function for the traversals
*/
void SixDegrees::run_traversals(istream &input, 
                                string command, ostream &output){
    string cmd1, cmd2;
    
    if (command == "bfs" or command == "dfs"){
        getline(input, cmd1);
        getline(input, cmd2);
        
        Artist Start(cmd1);
        Artist Destination(cmd2);
        
        if (command == "bfs"){
            bfs(Start, Destination, output);
        } else {
            dfs(Start, Destination, output);
        }
        
    } else if (command == "not") {
        not_helper(output, input);
    }    
}

/*
* not_helper
* Parameters: an output and input streams
* return: none
* purpose: a helper function for the Not function
*/
void SixDegrees::not_helper(ostream &output, istream &input){
    
    string cmd1, cmd2;
    
    getline(input, cmd1);
    getline(input, cmd2);
                                
    Artist Start(cmd1);
    Artist Destination(cmd2);
                                
    string exc_artist = "";
    vector<Artist> artists;
                                
    while (exc_artist != "*"){
        getline(input, exc_artist);
        if (exc_artist != "*"){
            Artist exclude(exc_artist);
            artists.push_back(exclude);
        }
    }
                                
    Not(Start, Destination, artists, output);                            
}

/*
* print_collab
* Parameters: two artists, the starting and destination artists, and an output
*             stream
* return: none
* purpose: a helper function for tprinting the collaborations
*/
void SixDegrees::print_collab(Artist Start, Artist Destination, 
                              ostream &output){
    
    stack<Artist> reportPath;
    
    reportPath = collab_graph.report_path(Start, Destination);
    
    if (reportPath.size() < 2){
        output << "A path does not exist between " << "\"" << Start << 
                "\"" << " and " << "\"" << Destination << "\"." << endl;
    }
    
    while (not reportPath.empty()){
        Artist first = reportPath.top();
        reportPath.pop();
        Artist second = reportPath.top();
        string song = collab_graph.get_edge(first, second);
        output << "\"" << first << "\"" << 
        " collaborated with " << "\"" << second << 
        "\" in " << "\"" << song << "\"" << endl;
        
        if (reportPath.size() == 1){
            output << "***" << endl;
            break;
        }
    }    
}

/*
* dfs
* Parameters: two artists, the starting and destination artists, and an output
*             stream
* return: nothing
* purpose: prints the shortest path from the starting artist to the 
* destination artist found with a depth first search
*/
void SixDegrees::dfs(Artist Start, Artist Destination, ostream &output){
    
    collab_graph.clear_metadata();
    
    bool Continue = proceed(Start, Destination, output);
    if (Continue == false){
        return;
    }
    
    dfs_helper(Start);
    
    print_collab(Start, Destination, output);
}

/*
* dfs_helper
* Parameters: an artist - the starting artist
* return: nothing
* purpose: dfs helper function that uses recursion to traverse the graph
*/
void SixDegrees::dfs_helper(Artist Start){
    
    collab_graph.mark_vertex(Start);
    
    vector<Artist> neighbors;
    neighbors = collab_graph.get_vertex_neighbors(Start);
    
    while (not neighbors.empty()){
        Artist curr = neighbors.back();
        neighbors.pop_back();

        if (collab_graph.is_marked(curr) != true){
            collab_graph.mark_vertex(curr);
            collab_graph.set_predecessor(curr, Start);
            dfs_helper(curr);
        }
        
    }
}

/*
* Not
* Parameters: two artists, the starting and destination artists,
*             and a list of artists to exclude
* return: nothing
* purpose: prints the shortest path from the starting artist to the 
* destination artist found with a breadth first search excluding all artists
* from the list of artists to exclude
*/
void SixDegrees::Not(Artist Start, Artist Destination, 
                           std::vector<Artist> exclude, std::ostream &output){
    collab_graph.clear_metadata();                           
    bool Continue = proceed(Start, Destination, output);
    bool Continue2 = proceed2(exclude, output);
    if (Continue == false or Continue2 == false)
        return;
    
    queue<Artist> queue;    
    mark_artists(exclude);
    collab_graph.mark_vertex(Start);
    queue.push(Start);
    
    while (not queue.empty()){
        Artist to_explore = queue.front();
        queue.pop();
        // get neighbors of the Artist and store them  in queue2
        vector<Artist> neighbors;
        neighbors = collab_graph.get_vertex_neighbors(to_explore);
        while (not neighbors.empty()){
            Artist curr = neighbors.back();
            neighbors.pop_back();
            if (collab_graph.is_marked(curr) != true){
                collab_graph.mark_vertex(curr);
                collab_graph.set_predecessor(curr, to_explore);
                queue.push(curr);
            }    
        }
    }
    print_collab(Start, Destination, output);                               
}

/*
* mark_artists
* Parameters: output file
* return: nothing
* purpose: marks artists to be excluded
*/
void SixDegrees::mark_artists(std::vector<Artist> exclude){
    
    while (not exclude.empty()){
        Artist curr = exclude.back();
        exclude.pop_back();

        if (collab_graph.is_marked(curr) != true){
            collab_graph.mark_vertex(curr);
        }
        
    }
}

/*
* print
* Parameters: output file
* return: nothing
* purpose: calls the print_graph function of CollabGraph to print the graph
*/
void SixDegrees::print(ostream &output){
    collab_graph.print_graph(output);
}