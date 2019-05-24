#include <ctime>
#include <iostream>
#include <map>
#include <vector>
#include "park.h"

#include "../lib/ovo.h"

using namespace std;

int main(int argc, char const *argv[]) {
    Park p;

    if (!p.isExist()) {
        ovo::math m;
        std::vector<std::map<string, int>> ParkIniInfo;
        std::map<string, int> t_map;
        for (int i = 0; i < 100; i++) {
            t_map["Car"] = m.rand(0, 600);
            t_map["Bicycle"] = m.rand(0, 600);
            t_map["Airplane"] = m.rand(0, 600);
            t_map["Ship"] = m.rand(0, 600);
            ParkIniInfo.push_back(t_map);
        }

        p.ini(ParkIniInfo);

        std::map<string, std::vector<int>> feeTable;
        std::vector<int> fee;

        for (int i = 0; i < 24; i++) {
            fee.push_back(m.rand(0, 60));
        }

        feeTable["Car"] = fee;

        for (int i = 0; i < 24; i++) {
            fee[i] = m.rand(0, 60);
        }

        feeTable["Bicycle"] = fee;

        for (int i = 0; i < 24; i++) {
            fee[i] = m.rand(0, 60);
        }

        feeTable["Airplane"] = fee;

        for (int i = 0; i < 24; i++) {
            fee[i] = m.rand(0, 60);
        }

        feeTable["Ship"] = fee;

        p.updateFeeTable(feeTable);
    }

    ovo::data d;
    d["date"] = "2019-05-24";

    cout << p.getLog(d)[0].showAll();
    // cout << p.getLog()

    while (1) {
        string input = "";

        while (cin >> input) {
            if (input == "getPlots") {
                for (auto i : p.getPlotsID()) {
                    cout << p.getPlot(i).showAll() << endl;
                }
            }

            if (input == "getPlotsNum") {
                cout << p.getPlotsID().size() << endl;
            }

            input = "";
        }
    }

    // FeeTable t;
    /*
        std::vector<string> v;

        v.push_back("Cars");
        v.push_back("rac");


        t.setTypes(v);
    *//*

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
*/

    /*
        Plot p("eeeee", 3, "222");

        ovo::data d;

        d["eeeee"] = p.getStrContent();

        cout << d.showAll();
    */

    /*
       

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
        //*/
    /*
        string kk = "";
        if(!p.newCar("110", "Cars", p.getPlotsID("Cars", false)[0], kk))cout <<
    kk;

        int t = time(NULL);
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

            for(auto i : p.getLogByDate("2019-05-23")){
                cout << i.showAll();
            }
    */

    return 0;
}