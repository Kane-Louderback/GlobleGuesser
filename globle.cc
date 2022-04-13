#include "country.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;


int main(){
    ifstream infile;
    infile.open("country_list.txt");
    vector<Country> vec;
   
    if(!infile){
        cout << "File Failure" << endl;
    }
  

    for(int i = 0; i < 244; i++){
        Country tmp;
        string names;
        string lati, longi;
        string dumb;
        // skips acronym
        infile >> dumb;
        // gets lat and lon
        infile >> lati >> longi;
        double numlat = stod(lati);
        double numlon = stod(longi);
        tmp.lat = numlat;
        tmp.lon = numlon;
        //cout << "->" << setprecision(10) << numlat << endl; 
        // gets country name
        getline(infile, names);
        tmp.name = names;
         
        vec.push_back(tmp);
        

    }

    Country a;

    for(int i = 0; i < vec.size(); i++){
        cout << vec[i].name << " " << setprecision(10) << vec[i].lat << " " << setprecision(10) << vec[i].lon << endl;
    }
  

    infile.close();
}