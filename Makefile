#
# Makefile for Six Degrees
#
# Project 2 (fall 2020)
#
# Walter Wagude
#  date: 12/11/2021
# 

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11 
INCLUDES = $(shell echo *.h)

SixDegrees: main.o SixDegrees.o CollabGraph.o Artist.o
	${CXX} -o $@ $^

%.o: %.cpp ${INCLUDES}
	${CXX} ${CXXFLAGS} -c $<

# This rule provides my submission
provide:
	provide comp15 proj2phase2 	CollabGraph.cpp CollabGraph.h\
				   main.cpp Makefile\
				   README SixDegrees.cpp SixDegrees.h\
				   Test.txt Testcommand_loop.txt\
				   TestingCollabGraph.cpp Testpopulate_collabgraph.txt\
				   artists.txt
# This rule provides my submission 
phase1:
	provide comp15 proj2phase1 CollabGraph.cpp CollabGraph.h\
	               main.cpp Makefile\
	               README SixDegrees.cpp SixDegrees.h\
				   Testcommand_loop.txt\
				   TestingCollabGraph.cpp Testpopulate_collabgraph.txt\
				   unit_tests.h artists.txt
			

clean:
	rm -rf SixDegrees *.o *.dSYM
