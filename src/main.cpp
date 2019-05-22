#include <iostream>
#include <vector>
#include <map>
#include "park.h"

using namespace std;

int main(int argc, char const *argv[])
{
    
    Park p;

    cout << p.isExist();

    std::vector<map<string, int>> v;

    map<string, int> m;

    m["Bycycle"] = 5;
    m["Cars"] = 2;

    v.push_back(m);

    m["Carsss"] = 99;
    v.push_back(m);

    //p.ini(v);

    //cout << p.checkType("Cadrs");

    cout << p.getPlots(1).size();

    return 0;
}