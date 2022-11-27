#include "Airports.h"

Airports::Airports(){ //default constructor
    numAirports = 0;
    airportsIDX_ = 0;
    name_ = "DEFAULT";
    IATA_ = "DEFAULT";
    latitude_ = 0.0;
    longitude_ = 0.0;
}

Airports::Airports(int airportsIDX, std::string name, std::string IATA, long double latitude, long double longitude){
    numAirports = countValidAirports();
    airportsIDX_ = airportsIDX;
    name_ = name;
    IATA_ = IATA;
    latitude_ = latitude;
    longitude_ = longitude;
}

int Airports::countValidAirports(){
    return airports.size(); //returns size of vertex vector
}

std::vector<Airports*> Airports::parseAirports(std::string airportsFile){
    std::ifstream file;
    file.open(airportsFile);
    std::string line, temp, sRow, sName, sIATA, sLatitude, sLongitude;    
    // std::cout << "\033[1;37mPrinting IATA\033[0m" << std::endl;

    while(std::getline(file, line)){
        std::stringstream ss (line);

        std::getline(ss, temp, ','); //row (skips some value)

        std::getline(ss, sName, ','); //name
        sName = removeQuotes(sName);

        std::getline(ss, temp, ','); //city (doesn't matter)
        std::getline(ss, temp, ','); //country (doesn't matter)

        std::getline(ss, sIATA, ','); //IATA
        sIATA = removeQuotes(sIATA);

        std::getline(ss, temp, ','); //ICAO
        std::getline(ss, sLatitude, ','); //latitude
        std::getline(ss, sLongitude, ','); //longitude

        //rest doesn't matter

        if(sIATA != "" && sIATA.size() == 3){
            // std::cout << "\033[1;34m"<< sIATA << "\033[0m" << std::endl;
            airports.push_back(new Airports(airports.size(), sName, sIATA, std::stold(sLatitude), std::stold(sLongitude)));  
            //have to index with the vector size because of issue with indexing. Should work now though.    
        }
    }
    return airports; //returns vector of vertexes
}

std::string Airports::removeQuotes(std::string str){
    if(str.size() >= 3){
        str = str.substr(1, str.length() - 2); //removes quotes on the IATA codes
        return str;
    }
    else{
        return "";
    }
}

int Airports::getAirportIDX(std::string userIATA){
    if(userIATA.size() != 3){
        return -1; //return -1 if the airport is invalid
    }
    for(auto i : airports){
        if(userIATA == i->getIATA()){
            return i->getAirportIDX(); //return index if not invalid
        }
    }
    return -1;
}

std::string Airports::getName(int airportIDX){
    return airports[airportIDX]->getName(); //return full name of airport
}

long double Airports::getLatitude(int airportIDX){
    return airports[airportIDX]->getLatitude(); //return longitude of airport at specific index
}

long double Airports::getLongitude(int airportIDX){
    return airports[airportIDX]->getLongitude(); //return latitude of airport at specific index
}

long double Airports::getLatitude(){
    return latitude_; //return latitude of current airport
}

long double Airports::getLongitude(){
    return longitude_; //return longitude of current airport
}

std::string Airports::getName(){
    return name_; //return current name of airport
}

std::string Airports::getIATA(){
    return IATA_; //return current IATA code
}

std::string Airports::getIATA(int i){
    return airports[i]->getIATA(); //return specific IATA code
}


int Airports::getAirportIDX(){
    return airportsIDX_; //return current airport index
}

Airports* Airports::getAirport(int i){
    return airports.at(i); //gets the airport pointer at a specifi index
}