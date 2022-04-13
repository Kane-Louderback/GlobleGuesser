#include <iostream>
#include <vector>
using namespace std;

class Country{
    public:
        string lat, lon;
        string name;
};


// gets lat of desired country
int getLat(Country a);

// gets lon of desired country
int getLon(Country a);

// get distance bewtween two countries
double distance(Country a, Country b);
