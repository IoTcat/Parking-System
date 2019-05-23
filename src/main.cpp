#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include "park.h"

#include "../lib/ovo.h"

using namespace std;

int main(int argc, char const *argv[])
{

    FeeTable t;
/*
    std::vector<string> v;

    v.push_back("Cars");
    v.push_back("rac");


    t.setTypes(v);
*/
    std::map<string, std::vector<int>> mm;

    std::vector<int> vv;

    vv.push_back(2);
    vv.push_back(3);

    mm["Cars"] = vv;

    t.set(mm);
    cout << t.showAll();

    //t.set(m);

    //cout << t.getFee("car", "0", "10000");

    //cout << t.showAll();


/*
    Plot p("eeeee", 3, "222");

    ovo::data d;

    d["eeeee"] = p.getStrContent();

    cout << d.showAll();
*/



   
    Park p;

    //cout << p.isExist();

    std::vector<map<string, int>> v;

    map<string, int> m;

    m["Bycycle"] = 599;
    m["Cars"] = 2;

    v.push_back(m);

    m["Carsss"] = 99;
    v.push_back(m);

    p.ini(v);
    //p.updateFeeTable(mm);

    //cout << p.checkType("Cadrs");
    


    p.join();


    p.checkIn("2333", "Cars");
    cout << p.checkOut("2333");
    //cout << p._feeTable.showAll();

    //cout << p._d.showAll();
    //
/*
    string kk = "";
    if(!p.newCar("110", "Cars", p.getPlotsID("Cars", false)[0], kk))cout << kk;

    int t = time(NULL);*/
    string s = "Cars";
    //cout << endl<<p.getPlotsID("Cars", false).size();

    for(auto i : p.getPlotsID(s)){
        cout << p.getPlot(i).showAll();
    }/*

    for(auto i : p.getCarsID(0)){
        cout << i;
    }
    cout << "  " << time(NULL) - t;
//p.delCar("110");
    cout << p.getPlotByCar("110").showAll();
*/
        for(auto i : p.getLogByDate("2019-05-23")){
            cout << i.showAll();
        }

    return 0;
}