/*
 * main.cpp
 *
 * COMP 15 Project 2: Six Degrees of Collaboration
 * Purpose:
 *      A driver for the Six Degrees program - handles command line arguments
 *      and interacts with the rest of the implementation 
 * 
 * by Walter Wagude, 5 DEC 2021
 */
 
#include <fstream>
#include <iostream>
#include "Artist.h"
#include "CollabGraph.h"
#include "SixDegrees.h"

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
    
    // an instance of a SixDegrees object
    SixDegrees six_degrees;
    // populate the graph
    six_degrees.populate_collabGraph(input_file);
    
    if (argc == 2){
        // take commands from cin and run the command loop
        six_degrees.command_loop(cin, cout);
    } else if (argc == 3){
        ifstream commands(argv[2]);
        // take commands and run the command loop
        six_degrees.command_loop(commands, cout);
    } else if (argc == 4){
        // commands
        ifstream commands(argv[2]);
        // output file
        ofstream outputtxt(argv[3]);
        // take commands and run the command loop
        six_degrees.command_loop(commands, outputtxt);    
    }
    
    input_file.close();
    return 0;
}
