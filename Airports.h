#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm> 
#include <string>

class Airports{
    public:
        //constructors
        Airports();
        //input: the index of the airport, the name of the airport, the IATA code, latitude, longitude
        Airports(int airportsIDX, std::string name, std::string IATA, long double latitude, long double longitude); 

        //returns number of valid vertexes
        //output: int of the number of vertexes in our graph       
        int countValidAirports();

        //parses csv file to create vertexes vector
        //input: airport file csv to parse
        //output: vector of airport pointers
        std::vector<Airports*> parseAirports(std::string airportsFile);

        //gets latitude of current airport
        //output: latitude of current airport
        long double getLatitude();


        //gets longitude of current airport
        //output: longitude of current airport
        long double getLongitude();

        std::string getName();
        std::string getIATA();
        int getAirportIDX(std::string);

        int getAirportIDX();

        //gets latitude of specific airport
        //input: index of airport
        //output: latitude at specific airport index
        long double getLatitude(int IDX);

        //gets longitude of specific airport
        //input: index of airport
        //output: longitude at specific airport index
        long double getLongitude(int IDX);

        //gets name of specific airport
        //input: index of airport
        //output: name at specific airport index
        std::string getName(int IDX);

        //gets airport pointer of specific airport
        //input: index of airport
        //output: airport pointer at specific airport index
        Airports* getAirport(int IDX);

        //gets IATA code of specific airport
        //input: index of airport
        //output: IATA code at specific airport index
        std::string getIATA(int IDX);

        //vector of vertexes
        std::vector<Airports*> airports;

        

    private:
        //removes quotes from CSV file around IATA code 
        //input: IATA code with quotes
        //output: IATA code without quotes
        std::string removeQuotes(std::string IATA);

        int numAirports;
        std::string name_, IATA_;
        int airportsIDX_;
        long double latitude_, longitude_;
};