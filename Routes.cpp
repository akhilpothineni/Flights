#include "Routes.h"

Routes::Routes(){ //default constructor
    sourceAirportsIDX_ = "DEFAULT"; 
    destinationAirportsIDX_ = "DEFAULT";
    airportFile_ = "data/airports.dat";
}

Routes::Routes(std::string sourceAirportsIDX, std::string destinationAirportsIDX, std::string airportFile){
    sourceAirportsIDX_ = sourceAirportsIDX;
    destinationAirportsIDX_ = destinationAirportsIDX;
    airportFile_ = airportFile;
}  

std::vector<Routes*> Routes::parseRoutes(std::string routesFile, std::string airportsFile){
    std::ifstream file;
    file.open(routesFile);   
    std::string line, temp, sourceAirport, destinationAirport;    
    // std::cout << "\033[1;37mPrinting IATA\033[0m" << std::endl;
    //goes through csv
    while(std::getline(file, line)){
        std::stringstream ss (line);

        std::getline(ss, temp, ','); //airline (skips some value)

        std::getline(ss, temp, ','); //airline ID

        std::getline(ss, sourceAirport, ','); //source airport

        std::getline(ss, temp, ','); //source airport ID


        std::getline(ss, destinationAirport, ','); //destination airport

        //rest doesn't matter

        if(sourceAirport != "" && sourceAirport.size() == 3 && destinationAirport != "" && destinationAirport.size() == 3){
            // std::cout << "\033[1;34m"<< sourceAirport << "\033[0m" << std::endl;
            routes.push_back(new Routes(sourceAirport, destinationAirport, airportsFile));
        }
    }
    file.close();
    return routes; //return vector of edges
}

int Routes::countValidRoutes(){
    return routes.size(); //return number of edges
}


std::string Routes::getSourceRouteIDX(int i){
    return routes.at(i)->sourceAirportsIDX_; //get the starting airport
}

std::string Routes::getDestinationRouteIDX(int i){
    return routes.at(i)->destinationAirportsIDX_; //get the destination airport
}

std::vector<std::string> Routes::getNeighbors(std::string startingAirport){
    std::vector<std::string> destinations; //function returns the airports that can be visisted from a target
    for(size_t i = 0; i < routes.size(); i++){
        if(routes.at(i)->sourceAirportsIDX_ == startingAirport && (routes.at(i)->destinationAirportsIDX_) != 
            "IGM" && (routes.at(i)->destinationAirportsIDX_) != "SVC" && (routes.at(i)->destinationAirportsIDX_) != "ZEL" && (routes.at(i)->destinationAirportsIDX_) != "EAR" && (routes.at(i)->destinationAirportsIDX_) != "CGA" && (routes.at(i)->destinationAirportsIDX_) != "HYL" && (routes.at(i)->destinationAirportsIDX_) != "KCC"
            && (routes.at(i)->destinationAirportsIDX_) != "KPB" && (routes.at(i)->destinationAirportsIDX_) != "KTB" && (routes.at(i)->destinationAirportsIDX_) != "KWF" && (routes.at(i)->destinationAirportsIDX_) != "RYG" && (routes.at(i)->destinationAirportsIDX_) != "MRA"){
            destinations.push_back(routes.at(i)->destinationAirportsIDX_);
        }
    }
    return destinations; 
}

std::vector<std::pair<long double, std::string> > Routes::getWeightedNeighbors(std::string startingAirport){
    std::vector<Airports*> a = airports.parseAirports(airportFile_);
    int startIdx = airports.getAirportIDX(startingAirport);

    std::vector<std::string> dest = getNeighbors(startingAirport);
    std::vector<std::pair<long double, std::string> > destinationsWeights(dest.size());

    int count = 0;
    for(auto i : dest){
        destinationsWeights.at(count).second = i;
        int destIdx = airports.getAirportIDX(i);
        std::cout << "\033[1;37m" << "Neighbors of "<< "\033[0m" << "\033[1;36m" << startingAirport << "\033[0m"
            << "\033[1;37m" << ": " << "\033[0m"<< "\033[1;36m" << i << "\033[0m" << std::endl;
        long double dist = getPathLength(startingAirport, i); //gets the edge weight of every edge
        destinationsWeights.at(count).first = dist;
        count++;
    }

    auto p = std::unique(destinationsWeights.begin(), destinationsWeights.end()); //makes sure there are no copied routes
    destinationsWeights.resize(std::distance(destinationsWeights.begin(), p));

    // for(auto i : destinationsWeights){
    //     std::cout << i.first << " "<< i.second << std::endl;
    // }

    return destinationsWeights;
}

std::vector<std::string> Routes::BFSTraversal(Airports* startAirport){
    int count = 0; //counter for number of airports visited
    std::vector<std::string> visisted; 
    std::queue<std::string> q;

    q.push(startAirport->getIATA()); //gets inital airports pushed onto queue and marks as visited
    visisted.push_back(startAirport->getIATA());

    while(!q.empty()){
        std::string current = q.front(); //pushes next airport onto queue
        q.pop();
        count++;
        std::cout << "\033[1;34m" << current << "\033[0m" << std::endl;

        std::vector<std::string> dest = getNeighbors(current); //gets all the adjacent airports
        // std::cout << dest.size() <<std::endl;

        for(std::string s : dest){
            // std::cout << "ITERATING OVER DEST" <<std::endl;
            if(!(std::find(visisted.begin(), visisted.end(), s) != visisted.end())){ //checks if adjacent airport is not in visited
                // std::cout << "ADDING ONE TO VISITED" <<std::endl;
                q.push(s); // pushes adjacent airport to queue
                visisted.push_back(s);
            }
        }
    }

    //printout 
    std::cout << "\033[1;37m"<< "There are " << "\033[0m" <<
        "\033[1;36m" << count << "\033[0m" << 
        "\033[1;37m"<< " airports connected to this airport" <<
        "\033[0m" <<std::endl;


    return visisted;
}

std::vector<std::string> Routes::Dijkstra(std::string start, std::string destination){
    std::vector<Airports*> a = airports.parseAirports(airportFile_);
    std::vector<std::string> ret;
    long double finalDistance = 0.0;

    std::unordered_map<std::string, std::string> prev; //init prev airport visited
    std::unordered_map<std::string, bool>  visited; //init visited airport
    std::unordered_map<std::string, long double> distances; //init distance values for edge weights

    //assigns starting values to init things
    for(auto i : a){
        distances.insert({i->getIATA(), INT_MAX});
        visited.insert({i->getIATA(), false});
        prev.insert({i->getIATA(), "NULL"});
    }

    //creates priority queue
    std::priority_queue<PA, std::vector<PA>, std::greater<PA>> Q;
    distances.at(start) = 0.0;

    //pushes start to queue
    Q.push(std::make_pair(distances.at(start), start));

    std::cout << "\033[1;32m" << "Performing Dijkstra's" << "\033[0m" << std::endl;
    std::cout << "\033[1;31m" << "please be patient..." << "\033[0m" << std::endl;

    while(Q.top().second != destination){
        auto currNode = Q.top(); //saves top airports
        Q.pop();

        for(auto i : getWeightedNeighbors(currNode.second)){ //get adjacent airports from current 
            if(visited.at(i.second) == true){
                continue; //if visted vertex skip it
            }
            //if distance to get to vertex is less than current distance update the distance and add to prev
            if(i.first + distances.at(currNode.second) < distances.at(i.second)){
                distances.at(i.second) = i.first + distances.at(currNode.second);
                Q.push(std::make_pair(distances.at(i.second), i.second)); //push the neighbor to queue
                prev.at(i.second) = currNode.second;
            }
        }
        //set current vertex to visited
        visited.at(currNode.second) = true;
    }

    //gets pathing by looping through previous
    finalDistance = distances.at(destination);
    ret.push_back(destination);
    std::string s = destination;

    while(s != start){
        ret.push_back(prev.at(s));
        s = prev.at(s);
    }
    std::reverse(ret.begin(), ret.end());

    std::cout << "\033[1;35m" << "Shortest Path: " << "\033[0m" << std::endl;

    //print out path
    for(unsigned i = 0; i < ret.size(); i++){
        std::cout << "\033[1;34m" << ret.at(i) << "\033[0m"; 
        if(i != ret.size() - 1){
            std::cout << "\033[1;32m" << " -> " << "\033[0m";
        }
    }
    //print out for distance traveled
    std::cout << "\033[1;33m" << " Distance: " << "\033[0m" << "\033[1;34m" << distances.at(destination) 
        << "\033[0m" << "\033[1;33m" << " km" << "\033[0m" << std::endl;
    return ret;
}      


long double Routes::getPathLength(std::string s, std::string d){
    std::vector<Airports*> a = airports.parseAirports(airportFile_);
    int sIDX = airports.getAirportIDX(s);
    int dIDX = airports.getAirportIDX(d);
    if(sIDX == -1){
        return INT_MAX;
    }
    else if(dIDX == -1){
        return INT_MAX;
    }
    long double ret = calc.calcFlightDistance(airports.getLatitude(sIDX), airports.getLongitude(sIDX),  airports.getLatitude(dIDX), airports.getLongitude(dIDX));
    // std::cout << ret << std::endl;
    return ret;
}

std::vector<std::pair<double, std::string>> Routes::PageRank(){
    std::vector<Airports*> a = airports.parseAirports(airportFile_);
    double size = a.size();
    std::vector<std::pair<double, std::string>> airportsRanked(size);
    int idx = 0;
    unsigned numRanked = 0;
    std::string pastAiport;
    std::cout << "\033[1;37m"<< "Running PageRank" << "\033[0m" << std::endl;
    std::cout << "\033[1;31m" << "please be patient..." << "\033[0m" << std::endl;

    //for every airport vertex
    for(Airports* currAir : a){
        double count = 0;    
        airportsRanked[idx].second = currAir->getIATA(); //get airport code
        //for every route
        for(size_t i = 0; i < routes.size(); i++){
            if(routes.at(i)->destinationAirportsIDX_ == currAir->getIATA()){
                count++; //if destination of the route is the current vertex add to count
                if(currAir->getIATA() != pastAiport){
                    pastAiport = currAir->getIATA();;
                    numRanked++;
                }
            }
        }
        airportsRanked[idx].first = count / countValidRoutes(); //get rank of the airport
        idx++;
    }
    //sort based on rank
    std::sort(airportsRanked.begin(), airportsRanked.end(), std::greater<PA>());
    std::cout << "\033[1;34m"<< "PageRank Complete" << "\033[0m" << std::endl;

    //printout the top 5 airports
    int idk = 1;
    if(numRanked < 5){
        for(unsigned i = 0; i < numRanked; i++){
            std::cout << "\033[1;33m"<< idk << ": " << "\033[0m"<< "\033[1;32m" << airportsRanked.at(i).second << ", " << 
                airports.getName(airports.getAirportIDX(airportsRanked.at(i).second)) << "\033[0m" << "\033[1;34m"
                ", Probabilty of Being Visited: " << airportsRanked.at(i).first << "\033[0m" << std::endl;
            idk++;
        }
    }
    else{
        for(unsigned i = 0; i < 5; i++){
            std::cout << "\033[1;33m"<< idk << ": " << "\033[0m"<< "\033[1;32m" << airportsRanked.at(i).second << ", " << 
                airports.getName(airports.getAirportIDX(airportsRanked.at(i).second)) << "\033[0m" << "\033[1;34m"
                ", Probabilty of Being Visited: " << airportsRanked.at(i).first << "\033[0m" << std::endl;
            idk++;
        }
    }
    return airportsRanked;
}