/**
 ** SixDegrees.h
 **
 ** Project Two: Six Degrees of Collaboration
 **
 ** Purpose:
 **   Has an instance of CollabGraph object. Has functions that help to
 **   populate and navigate the collabgraph class
 **
 ** Created by:
 **   Walter Wagude
 **   5 DEC 2021
 **/
 
#ifndef __SIX_DEGREES__
#define __SIX_DEGREES__
 
#include <iostream>
#include "Artist.h"
#include "CollabGraph.h"
 
class SixDegrees {
     
    public:
        // constructor for the SixDegree class
        SixDegrees();
        // destructor
        ~SixDegrees();
        // function to populate the CollabGraph
        void populate_collabGraph(std::istream &input);
        // the command loop
        void command_loop(std::istream &input, std::ostream &output);
        
    private:
        CollabGraph collab_graph;
        
        // functions to implement the commands
        void bfs(Artist Start, Artist Destination, std::ostream &output);
        void dfs(Artist Start, Artist Destination, std::ostream &output);
        void Not(Artist Start, Artist Destination, 
                 std::vector<Artist> exclude, std::ostream &output);
        void print(std::ostream &output);
        
        // helper function for the traversals
        bool proceed(Artist Start, Artist Destination, std::ostream &output);
        bool proceed2(std::vector<Artist> exclude, std::ostream &output);
        void print_collab(Artist Start, Artist Destination,
                          std::ostream &output);
        void run_traversals(std::istream &input, 
                            std::string command, std::ostream &output);
        void not_helper(std::ostream &output, std::istream &input);
        void dfs_helper(Artist Start);
        void mark_artists(std::vector<Artist> exclude);
};
 
#endif