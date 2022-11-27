#include <iostream>
#include "Airports.h"
#include "Routes.h"

int main(){
    Airports airports;
    Routes routes;

    //Prompt the User and get Input
    std::cout << "\033[1;37m"<< "BFS type: " << "\033[0m" << "\033[1;33m" << "B" << "\033[0m" <<
        "\033[1;34m" << " | " << "\033[0m";
    std::cout << "\033[1;37m"<< "Dijkstra type: " << "\033[0m" << "\033[1;33m" << "D" << "\033[0m" <<
        "\033[1;34m" << " | " << "\033[0m";
    std::cout << "\033[1;37m"<< "PageRank type: " << "\033[0m" << "\033[1;33m" << "P" << "\033[0m" << std::endl;
    std::string testMaybe;
    std::cin >> testMaybe;

    //creates the vertex's of our graph from the airports Dataset
    airports.parseAirports("data/airports.dat");
    //creates the edge's of our graph from the routes Dataset
    routes.parseRoutes("data/routes.dat", "data/airports.dat");


    //Check what User Wants to Do
    if(testMaybe == "P"){
        routes.PageRank(); //run pagerank
    }
    else if(testMaybe == "D"){
        //get user input for shortest path
        std::cout << "\033[1;37m"<< "Where are you now? " << "\033[0m" <<
            "\033[1;36m" << "(Use a capital 3 letter IATA code)"<< "\033[0m" << std::endl;
        std::string start;
        std::cin >> start;
        int startIDX = airports.getAirportIDX(start);
        std::cout << "\033[1;37m"<< "Where do you want go? " << "\033[0m" <<
            "\033[1;36m" << "(Use a capital 3 letter IATA code)"<< "\033[0m" << std::endl;
        std::string destination;
        std::cin >> destination;
        
        //check if airport in is our airports dataset
        int destinationIDX = airports.getAirportIDX(start);
        if(startIDX != -1 && destinationIDX != -1){
            routes.Dijkstra(start, destination); //run shortest path
        }
        else{
            std::cout << "\033[1;31m" << "Please remember to use a 3 letter IATA and that it exists"<< "\033[0m" << std::endl;
        }
    }
    else if(testMaybe == "B"){
        //prompt for starting airport
        std::cout << "\033[1;37m"<< "Where are you now? " << "\033[0m" <<
        "\033[1;36m" << "(Use a capital 3 letter IATA code)"<< "\033[0m" << std::endl;
        std::string start;
        std::cin >> start;

        //gets starting airport index 
        int startAirportIDX = airports.getAirportIDX(start);
        if(startAirportIDX != -1){ //if index 
            std::cout << "\033[1;37m"<< "Performing BFS from " << "\033[0m" <<
                "\033[1;34m" << start << "\033[0m" << std::endl;

            std::cout << "\033[1;31m" << "please be patient..." << "\033[0m" << std::endl;

            routes.BFSTraversal(airports.getAirport(startAirportIDX)); //run BFS

        }else{
            std::cout << "\033[1;31m" << "Please remember to use a 3 letter IATA and that it exists"<< "\033[0m" << std::endl;
        }    
    }
    else{ //check if user inputted one of the options
        std::cout << "\033[1;31m" << "Please use one of the provided options"<< "\033[0m" << std::endl;
    }

    return 0;
}