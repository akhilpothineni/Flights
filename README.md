# akhilp3-alexdl2-jmeka2 Final Project
Contributers: Alex L, Akhil P, Jayanth M

## Overview
Our project looks at data from the OpenFlights airports and routes dataset (https://openflights.org/data.html). 

From this dataset we determine the shortest path between two given airports, and rank each airport based on its importance. We also are able to perform BFS to traverse through every connected airport.

**Presentation Video:** https://youtu.be/E-S9wmvquL8

**Documentation:** All documentation and the written report exist in ```./Documents```. 

All testing and running of the code can be done using the provided make file. In order to input airports of your choice first use ```module load llvm/6.0.1``` on EWS and then use ```make``` & ```./run```  to run the code. In order to run the test cases use ```make test```, then run using ```./test```. This will automatically run tests using catch.

## Inputing Data
Data is read in from multiple .dat files. These exists in ```/data```. The data from these files is processed in two locations: ```airports.cpp/h``` and ```routes.cpp/h```. 

Data is corrected and then stored in two vectors. One representing the vertcies (airports) and another representing edges (routes).

## BFS Traversal
BFS Traversal is implemented in ```routes.cpp/h```.

Test cases for BFS's exist in ```tests/test.cpp``` and are run by using ```./test```. The test cases use a smaller data set to make it easily checked manually. BFS is checked by making sure the traversal at the end goes in the correct order. BFS's test case file is  ```/data/testBFS.dat```

## Dijkstra's Algorithm
Dijkstra's Algorithm is implemented in ```routes.cpp/h```. 

Test cases for Dijkstra's exist in ```tests/test.cpp``` and are run by using ```./test```. The test cases also use a smaller data set so they can be easily checked manually. Listed on the test files for Dijkstra's are the respective weights of the routes to make sure the algorithm is finding the shortest path. Dijkstra's test case files are  ```/data/testDijRoutesComplex.dat``` & ```/data/testDijRoutesSimple.dat```.

## PageRank
PageRank's Algorithm is implemented in ```routes.cpp/h```. 

Test cases for pagerank exist in ```tests/test.cpp``` and are run by using ```./test```. These test cases also use a smaller data set so they can be easily checked manually. The PageRank tests