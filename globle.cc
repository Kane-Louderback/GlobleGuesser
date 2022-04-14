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
bool find(vector<Country> &vec, Country a);
void printVec(vector<Country> a);
void printVecDis(vector<Stat> a);
void sortVecDis(vector<Stat> &a);
int findClosest(vector<Country> a, Country focal, int intput);

int main(){
    ifstream infile;
    infile.open("country_list.txt");
    vector<Country> vec;
    
    if(!infile){
        cout << "File Failure" << endl;
    }
  
    // put everything in vector from file
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
    double sum = 0;
    int index = 237;
    string input = "";
    cout << "Welcome! The calulated best starting guess is Somoa, enter that now. Enter the distance after each guess. To quit the program, type q then enter. Good luck!" << '\n';
    cout << "Distance: ";
    cin >> input;
    while(input != "q"){
    int prevIndex = index;
    int intput = stoi(input);
    int prevIntput = intput;
    vector<Stat> distances;

    //fill the distances vector, distance from the current country index
    for(int i = 0; i < vec.size(); i++){
       int dist = distance(vec[index].lat, vec[index].lon, vec[i].lat, vec[i].lon);
       Stat tmp;
       tmp.name = vec[i].name;
       tmp.distances = dist;
       distances.push_back(tmp);
       
    }
    // now need to find the closest answer to the intput
    cout << endl << endl;
    //printVec(vec);
    int track = 1000000;
    for(int k = 0; k < distances.size(); k++){
        
        int test = abs(distances[k].distances - intput);
        if(test < track){
            track = test;
            index = k;
        }
    }
    
    cout << "The next best guess is... " << vec[index].name << endl;
    int vecsize = vec.size() - 1;
    // could cause issues, if problem occurs later this could be it
    vec[index].lat = 0;
    vec[index].lon = 0;
    string input1;
    cout << "Distance: ";
    cin >> input1;

    cout << input << " <---> " << input1 << endl;
    if( input == input1){
        cout << "PrevIndex " << prevIndex << endl;
        index = prevIndex;
        cout << "Index " << index << endl;
        printVec(vec);
        cout << "HOST COUNTRY =" << vec[index].name << endl;
        vec[index].lat = 0;
        vec[index].lon = 0;
    }
    input = input1;
    }

    infile.close();
}
long double toRadians(const long double degree)
{

    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}
long double distance(long double lat1, long double long1,
                     long double lat2, long double long2)
{
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);
     
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;
 
    long double ans = pow(sin(dlat / 2), 2) +
                          cos(lat1) * cos(lat2) *
                          pow(sin(dlong / 2), 2);
 
    ans = 2 * asin(sqrt(ans));
    long double R = 6371;

    ans = ans * R;
 
    return ans;
}
bool find(vector<Country> &vec, Country a){
    bool found = false;
    for(int i = 0; i < vec.size(); i++){
        string name1 = vec[i].name;
        string name2 = a.name;
        cout << " test -> "<< name1 << name2 << endl;
        if(name1 == name2){
            found = true;
        }

    }
    //cout << "FOUND = " << found << endl;
    return found;
}
void printVec(vector<Country> a){
    for(int i = 0; i < a.size(); i++){
        cout << a[i].name << " " << a[i].lat << " " << a[i].lon << endl;
    }

}
void printVecDis(vector<Stat> a){
    for(int i = 0; i < a.size(); i++){
        cout << a[i].name << " " << a[i].distances << endl;
    }

}
void sortVecDis(vector<Stat> &a){
    for(int i = 0; i < a.size(); i++){
        for (int j = 0; j < a.size() - i - 1; j++)
            if (a[j].distances > a[j + 1].distances)
                swap(a[j], a[j + 1]); 
    }

}
int findClosest(vector<Country> a, Country focal, int intput){
    int closest = 1000000;
    int index = 0;
    vector<Stat> vec;
    Stat newt;
    for(int i = 0; i < a.size(); i++){
        int dist = abs(intput - distance(a[i].lat, a[i].lon, focal.lat, focal.lon));
        //cout << intput << " - " << dist << endl;
        newt.name = a[i].name;
        newt.distances = dist;
        vec.push_back(newt);
    }
    
    sortVecDis(vec);
    //printVecDis(vec);
    
    return index;
}