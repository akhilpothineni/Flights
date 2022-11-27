#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm> 
#include <string>
#include "Airports.h"
#include <queue>
#include <utility>
#include "Calculate.h"
#include <list>
#include <climits>
#include <functional>
#include <unordered_map>

class Routes {
    public:
        //constructors
        Routes();
        //input: starting airport, destination airport, file name for airport data
        Routes(std::string sourceAirportsIDX, std::string destinationAirportsIDX, std::string airportFile); 

        //parses csv file to create edges vector
        //input: route file csv to parse, airport file to compare
        //output: vector of edge pointers
        std::vector<Routes*> parseRoutes(std::string routeFile, std::string airportFile);  

        //returns number of valid edges
        //output: size of vector of edges
        int countValidRoutes(); 

        //gets the source airport's index
        //input: index of the route in the vector of edges
        //output: IATA code of starting airport
        std::string getSourceRouteIDX(int routeIDX);

        //gets the destination airport's index
        //input: index of the route in the vector of edges
        //output: IATA code of destination airport
        std::string getDestinationRouteIDX(int routeIDX);

        //gets all adjacent airports with a route
        //input: IATA code of starting airport
        //output: vector of IATA codes with all connecting airports
        std::vector<std::string> getNeighbors(std::string startingAirport);

        //gets all adjacent airports with a route and their edge weights
        //input: IATA code of starting airport
        //output: vector of pairs of IATA codes with all connecting airports and their edge weights
        std::vector<std::pair<long double, std::string> > getWeightedNeighbors(std::string);

        //Traverses all nodes in graph using BFS
        //input: starting airport pointer
        //output: vector of all visited airports in order
        std::vector<std::string> BFSTraversal(Airports* start); 

        //Performs Dijkstra's algo to find shortest path
        //input: IATA codes of start and end
        //output: vector of IATA codes which is the shortest path
        std::vector<std::string> Dijkstra(std::string start, std::string end);

        //Ranks all airports by their importance using PageRank
        //Output vector of pairs IATA codes and their importance(probability being visited)
        std::vector<std::pair<double, std::string> > PageRank();

       
        //gets the edge weight of the path from the source to destination
        //Input: IATA code of start and end airport
        //Output: edge weight as a long double
        long double getPathLength(std::string start, std::string end);

        Airports airports;
        Calculate calc; 
        std::string sourceAirportsIDX_, destinationAirportsIDX_, airportFile_;



    private:
        std::vector<Routes*> routes;
        typedef std::pair<long double, std::string> PA;
};