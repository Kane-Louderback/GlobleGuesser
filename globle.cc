#include "country.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
using namespace std;
long double toRadians(const long double degree);
long double distance(long double lat1, long double long1, long double lat2, long double long2);

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
        long double numlat = stod(lati);
        long double numlon = stod(longi);
        tmp.lat = numlat;
        tmp.lon = numlon;
        //cout << "->" << setprecision(10) << numlat << endl; 
        // gets country name
        getline(infile, names);
        tmp.name = names;
         
        vec.push_back(tmp);
        

    }

    Country a;
    double closest = 10000000;
    double sum = 0;
    double previous = closest;
    int index = 137;
    string input = "";
    cout << "Welcome! The calulated best starting guess is Montenegro, enter that now. Enter the distance after each guess. To quit the program, type q then enter. Good luck!" << '\n';
    while(input != "q"){
    cout << "Distance: ";
    cin >> input;
    int intput = stoi(input);
    for(int i = 0; i < vec.size(); i++){
       int dist =  abs(distance(vec[index].lat, vec[index].lon, vec[i].lat, vec[i].lon)) - intput;
       if(dist < closest){
           closest = abs(dist);
           index = i;
       }
    }
        cout << "MATH = " << closest << endl;
        cout << "Next best guess is ... " << vec[index].name << endl;
        
    }

    infile.close();
}
long double toRadians(const long double degree)
{
    // cmath library in C++
    // defines the constant
    // M_PI as the value of
    // pi accurate to 1e-30
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}
long double distance(long double lat1, long double long1,
                     long double lat2, long double long2)
{
    // Convert the latitudes
    // and longitudes
    // from degree to radians.
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);
     
    // Haversine Formula
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;
 
    long double ans = pow(sin(dlat / 2), 2) +
                          cos(lat1) * cos(lat2) *
                          pow(sin(dlong / 2), 2);
 
    ans = 2 * asin(sqrt(ans));
 
    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    long double R = 6371;
     
    // Calculate the result
    ans = ans * R;
 
    return ans;
}
