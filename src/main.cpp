#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include "park.h"

#include "../lib/ovo.h"

using namespace std;

int main(int argc, char const *argv[])
{/*
    Plot p("eeeee", 3, "222");

    ovo::data d;

    d["eeeee"] = p.getStrContent();

    cout << d.showAll();*/

   
    Park p;

    cout << p.isExist();

    std::vector<map<string, int>> v;

    map<string, int> m;

    m["Bycycle"] = 599;
    m["Cars"] = 2;

    v.push_back(m);

    m["Carsss"] = 99;
    v.push_back(m);

    p.ini(v);

    //cout << p.checkType("Cadrs");

    p.join();
    int t = time(NULL);
    cout << p.getPlotsID().size();
    cout << "  " << time(NULL) - t;
    return 0;
}