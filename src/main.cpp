/*
 * @Author: IoTcat (https://iotcat.me) 
 * @Date: 2019-05-26 18:59:20 
 * @Last Modified by:   IoTcat 
 * @Last Modified time: 2019-05-26 18:59:20 
 */
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <vector>
#include "park.h"

#include "../lib/ovo.h"

using namespace std;

int g_time = 0;

void recordCostTime(auto f);
void autoIni(Park& p);
void manualIni(Park& p);
void displayInfo(auto f, auto get);
void displayLog(auto f);

int main(int argc, char const* argv[]) {
    Park* p = new Park();

    cout << "This program aims to test the API of Back-End System.\nOnly for "
            "TEST purpose!!!!"
         << endl;
    system("pause");

    if (!p->isExist()) {
        while (1) {
            system("cls");
            cout << "There is NO Former Data FOUND!! You can choose to:" << endl
                 << endl;
            cout << "1. Randomly generate Plot and Price Info." << endl;
            cout << "2. Set Plots and Price info Manually." << endl;
            cout << endl << "Your Selection is = ";

            string s;
            cin >> s;

            if (s == "1") {
                autoIni(*p);
                break;
            }

            if (s == "2") {
                manualIni(*p);
                break;
            }
        }
    }

    while (1) {
        system("cls");

        cout << "1. Show Park Info." << endl;
        cout << "2. Show FeeTable Info." << endl;
        cout << "3. Test for Get Plots Info." << endl;
        cout << "4. Test for Get Cars Info." << endl;
        cout << "5. Test for Check In and Check Out." << endl;
        cout << "6. Test for Change Plots Info." << endl;
        cout << "7. Test for Get History LOG." << endl;
        cout << "8. Delete All Data and Exit." << endl;
        cout << "9. Exit" << endl;

        cout << endl << "Please Select = ";

        string slct;
        cin >> slct;

        if (slct == "1") {
            system("cls");

            cout << p->showAll() << endl;
            system("pause");
        }

        if (slct == "2") {
            system("cls");

            cout << p->showFeeTableInfo() << endl;
            system("pause");
        }

        if (slct == "3") {
            system("cls");

            cout << "1. Get All Plots." << endl;
            cout << "2. Get Plots By if Occupied." << endl;
            cout << "3. Get Plots By Floor." << endl;
            cout << "4. Get Plots By Type." << endl;
            cout << "5. Get Plots By Floor and if Occupied." << endl;
            cout << "6. Get Plots By Type and if Occupied." << endl;
            cout << "7. Get Plots By Floor and Type." << endl;
            cout << "8. Get Plots By Floor, Type and if Occupied." << endl;
            cout << "9. Get Plots By Car LicenseNumber." << endl;
            cout << "10. Back to Menu." << endl;

            cout << endl << "Please Select = ";

            string s;
            cin >> s;

            if (s == "1") {
                displayInfo(
                    [&]() -> std::vector<string> { return p->getPlotsID(); },
                    [&](string s) -> Plot { return p->getPlot(s); });
            }

            if (s == "2") {
                displayInfo(
                    [&]() -> std::vector<string> {
                        cout << "Please input 0 or 1(Occupied) = ";
                        string ss;
                        cin >> ss;
                        bool fin = true;
                        if (ss == "0") fin = false;
                        g_time = time(NULL);
                        return p->getPlotsID(fin);
                    },
                    [&](string s) -> Plot { return p->getPlot(s); });
            }

            if (s == "3") {
                displayInfo(
                    [&]() -> std::vector<string> {
                        cout << "Please Input the Floor = ";
                        int ss;
                        cin >> ss;
                        g_time = time(NULL);
                        return p->getPlotsID(ss);
                    },
                    [&](string s) -> Plot { return p->getPlot(s); });
            }

            if (s == "4") {
                displayInfo(
                    [&]() -> std::vector<string> {
                        cout << "Please Input the type = ";
                        string ss;
                        cin >> ss;
                        g_time = time(NULL);
                        return p->getPlotsID(ss);
                    },
                    [&](string s) -> Plot { return p->getPlot(s); });
            }

            if (s == "5") {
                displayInfo(
                    [&]() -> std::vector<string> {
                        cout << "Please Input the Floor = ";
                        int tt;
                        cin >> tt;
                        cout << "\nPlease Input 0 or 1(Occupied) = ";
                        int ss;
                        cin >> ss;
                        bool fin = true;
                        if (ss == 0) fin = false;
                        g_time = time(NULL);
                        return p->getPlotsID(tt, fin);
                    },
                    [&](string s) -> Plot { return p->getPlot(s); });
            }

            if (s == "6") {
                displayInfo(
                    [&]() -> std::vector<string> {
                        cout << "Please Input the type = ";
                        string tt;
                        cin >> tt;
                        cout << "\nPlease Input 0 or 1(Occupied) = ";
                        int ss;
                        cin >> ss;
                        bool fin = true;
                        if (ss == 0) fin = false;
                        g_time = time(NULL);
                        return p->getPlotsID(tt, fin);
                    },
                    [&](string s) -> Plot { return p->getPlot(s); });
            }

            if (s == "7") {
                displayInfo(
                    [&]() -> std::vector<string> {
                        cout << "Please Input the Floor = ";
                        int tt;
                        cin >> tt;
                        cout << "Please Input the type = ";
                        string kk;
                        cin >> kk;
                        g_time = time(NULL);
                        return p->getPlotsID(tt, kk);
                    },
                    [&](string s) -> Plot { return p->getPlot(s); });
            }

            if (s == "8") {
                displayInfo(
                    [&]() -> std::vector<string> {
                        cout << "Please Input the Floor = ";
                        int tt;
                        cin >> tt;
                        cout << "Please Input the type = ";
                        string kk;
                        cin >> kk;
                        cout << "\nPlease Input 0 or 1(Occupied) = ";
                        int ss;
                        cin >> ss;
                        bool fin = true;
                        if (ss == 0) fin = false;
                        g_time = time(NULL);
                        return p->getPlotsID(tt, kk, fin);
                    },
                    [&](string s) -> Plot { return p->getPlot(s); });
            }

            if (s == "9") {
                displayInfo(
                    [&]() -> std::vector<string> {
                        cout << "Please Input the Car LicenseNumber = ";
                        string kk;
                        cin >> kk;
                        std::vector<string> v;
                        g_time = time(NULL);
                        if(p->getPlotByCar(kk).getID() != "undefined")
                            v.push_back(p->getPlotByCar(kk).getID());
                        return v;
                    },
                    [&](string s) -> Plot { return p->getPlot(s); });
            }
        }

        if (slct == "4") {
            system("cls");

            cout << "1. Get All Cars." << endl;
            cout << "2. Get Cars By Floor." << endl;
            cout << "3. Get Cars By Type." << endl;
            cout << "4. Get Cars By Floor and Type." << endl;
            cout << "5. Get Car By LicenseNumber." << endl;
            cout << "6. Get Car By PlotID." << endl;
            cout << "7. Back to Menu." << endl;

            cout << endl << "Please Select = ";

            string s;
            cin >> s;

            if (s == "1") {
                displayInfo(
                    [&]() -> std::vector<string> { return p->getCarsID(); },
                    [&](string s) -> Car { return p->getCar(s); });
            }

            if (s == "2") {
                displayInfo(
                    [&]() -> std::vector<string> {
                        cout << "Please Input the Floor = ";
                        int ss;
                        cin >> ss;
                        g_time = time(NULL);
                        return p->getCarsID(ss);
                    },
                    [&](string s) -> Car { return p->getCar(s); });
            }

            if (s == "3") {
                displayInfo(
                    [&]() -> std::vector<string> {
                        cout << "Please Input the type = ";
                        string ss;
                        cin >> ss;
                        g_time = time(NULL);
                        return p->getCarsID(ss);
                    },
                    [&](string s) -> Car { return p->getCar(s); });
            }

            if (s == "4") {
                displayInfo(
                    [&]() -> std::vector<string> {
                        cout << "Please Input the Floor = ";
                        int tt;
                        cin >> tt;
                        cout << "Please Input the type = ";
                        string kk;
                        cin >> kk;
                        g_time = time(NULL);
                        return p->getCarsID(tt, kk);
                    },
                    [&](string s) -> Car { return p->getCar(s); });
            }

            if (s == "5") {
                displayInfo(
                    [&]() -> std::vector<string> {
                        cout << "Please Input the Car LicenseNumber = ";
                        string kk;
                        cin >> kk;
                        std::vector<string> v;
                        g_time = time(NULL);
                        v.push_back(kk);
                        return v;
                    },
                    [&](string s) -> Car { return p->getCar(s); });
            }

            if (s == "6") {
                displayInfo(
                    [&]() -> std::vector<string> {
                        cout << "Please Input the Plot ID = ";
                        string kk;
                        cin >> kk;
                        std::vector<string> v;
                        g_time = time(NULL);
                        if(p->getPlot(kk).getCar() != "undefined" && p->getPlot(kk).getCar() != "null")   
                            v.push_back(p->getPlot(kk).getCar());
                        return v;
                    },
                    [&](string s) -> Car { return p->getCar(s); });
            }
        }

        if (slct == "5") {
            system("cls");

            cout << "1. Check In." << endl;
            cout << "2. Check In with Floor." << endl;
            cout << "3. Check In with Plot ID." << endl;
            cout << "4. Check Out." << endl;
            cout << "5. Back to Menu." << endl;

            cout << endl << "Please Select = ";

            string s;
            cin >> s;

            if (s == "1") {
                system("cls");

                cout << "Please Input the LicenseNumber = ";
                string t_CarID, t_Type, errMsg = "";
                cin >> t_CarID;

                cout << endl << "Please Input the Car type = ";
                cin >> t_Type;

                if (!p->checkIn(t_CarID, t_Type, errMsg)) {
                    cout << "Check In Failure!! :: " << errMsg;
                } else {
                    cout << "Check In Successfully!!";
                }

                cout << endl;
                system("pause");
            }

            if (s == "2") {
                system("cls");

                cout << "Please Input the LicenseNumber = ";
                string t_CarID, t_Type, errMsg = "";
                cin >> t_CarID;

                cout << endl << "Please Input the Car type = ";
                cin >> t_Type;

                int t_level;
                cout << endl << "Please Input the level = ";
                cin >> t_level;

                if (!p->checkIn(t_CarID, t_Type, t_level, errMsg)) {
                    cout << "Check In Failure!! :: " << errMsg;
                } else {
                    cout << "Check In Successfully!!";
                }

                cout << endl;
                system("pause");
            }

            if (s == "3") {
                system("cls");

                cout << "Please Input the LicenseNumber = ";
                string t_CarID, t_Type, t_PlotID, errMsg = "";
                cin >> t_CarID;

                cout << endl << "Please Input the Car type = ";
                cin >> t_Type;

                cout << endl << "Please Input the Plot ID = ";
                cin >> t_PlotID;

                if (!p->checkInByPlotID(t_CarID, t_Type, t_PlotID, errMsg)) {
                    cout << "Check In Failure!! :: " << errMsg;
                } else {
                    cout << "Check In Successfully!!";
                }

                cout << endl;
                system("pause");
            }

            if (s == "4") {
                system("cls");

                cout << "Please Input the LicenseNumber = ";
                string t_CarID, errMsg = "";
                cin >> t_CarID;

                int fee = p->checkOut(t_CarID, errMsg);

                if (fee == -1) {
                    cout << "Check Out Failure!! :: " << errMsg;
                } else {
                    cout << "Your Fee is $" << fee << "." << endl;
                    cout << "Check Out Successfully!!";
                }

                cout << endl;
                system("pause");
            }
        }

        if (slct == "6") {
            system("cls");

            cout << "1. Update Type." << endl;
            cout << "2. Update Floor." << endl;
            cout << "3. Back to Menu." << endl;

            cout << endl << "Please Select = ";

            string s;
            cin >> s;

            if (s == "1") {
                system("cls");

                cout << "Please Input the Plot ID = ";
                string t_PlotID;
                cin >> t_PlotID;

                cout << "Please Input the new Type = ";
                string t_Type;
                cin >> t_Type;

                Plot pp = p->getPlot(t_PlotID);
                cout << pp.showAll();

                if (!p->updatePlot(pp, t_Type)) {
                    cout << endl << "Update Failure!!!" << endl;
                } else {
                    cout << endl << "Update Successfully!!" << endl;
                }

                system("pause");
            }
            if (s == "2") {
                system("cls");

                cout << "Please Input the Plot ID = ";
                string t_PlotID;
                cin >> t_PlotID;

                cout << "Please Input the new Floor = ";
                int t_floor;
                cin >> t_floor;

                Plot pp = p->getPlot(t_PlotID);

                if (!p->updatePlot(pp, t_floor)) {
                    cout << endl << "Update Failure!!!" << endl;
                } else {
                    cout << endl << "Update Successfully!!" << endl;
                }

                system("pause");
            }
        }

        if (slct == "7") {
            system("cls");

            cout << "1. Get All Log." << endl;
            cout << "2. Get Log By Date." << endl;
            cout << "3. Get Log By Car LicenseNumber." << endl;
            cout << "4. Get Log By Type." << endl;
            cout << "5. Get Log By Floor." << endl;
            cout << "6. Get Log By Fee." << endl;
            cout << "7. Get Log By Type and Date." << endl;
            cout << "8. Get Log By Floor and Date." << endl;
            cout << "9. Back to Menu." << endl;

            cout << endl << "Please Select = ";

            string s;
            cin >> s;

            if (s == "1") {
                displayLog(
                    [&]() -> std::vector<ovo::data> { return p->getLog(); });
            }

            if (s == "2") {
                displayLog([&]() -> std::vector<ovo::data> {
                    cout << "Please Input the Date (format 2019-05-26) = ";
                    string t_date;
                    cin >> t_date;

                    return p->getLogByDate(t_date);
                });
            }

            if (s == "3") {
                displayLog([&]() -> std::vector<ovo::data> {
                    cout << "Please Input the Car LicenseNumber = ";
                    string t_CarID;
                    cin >> t_CarID;

                    return p->getLogByCarID(t_CarID);
                });
            }

            if (s == "4") {
                displayLog([&]() -> std::vector<ovo::data> {
                    cout << "Please Input the Type = ";
                    string t_Type;
                    cin >> t_Type;

                    return p->getLogByType(t_Type);
                });
            }

            if (s == "5") {
                displayLog([&]() -> std::vector<ovo::data> {
                    cout << "Please Input the Floor = ";
                    int t_floor;
                    cin >> t_floor;

                    return p->getLogByLevel(t_floor);
                });
            }

            if (s == "6") {
                displayLog([&]() -> std::vector<ovo::data> {
                    cout << "Please Input the Fee = ";
                    int t_fee;
                    cin >> t_fee;

                    return p->getLogByFee(t_fee);
                });
            }

            if (s == "7") {
                displayLog([&]() -> std::vector<ovo::data> {
                    cout << "Please Input the Type = ";
                    string t_Type;
                    cin >> t_Type;

                    cout << "Please Input the Date (format 2019-05-26) = ";
                    string t_date;
                    cin >> t_date;

                    return p->getLogByType(t_Type, t_date);
                });
            }

            if (s == "8") {
                displayLog([&]() -> std::vector<ovo::data> {
                    cout << "Please Input the Floor = ";
                    int t_floor;
                    cin >> t_floor;

                    cout << "Please Input the Date (format 2019-05-26) = ";
                    string t_date;
                    cin >> t_date;

                    return p->getLogByLevel(t_floor, t_date);
                });
            }
        }
        if (slct == "8") {
            delete p;
            system("del data\\* /Q");
            return 0;
        }

        if (slct == "9") {
            return 0;
        }
    }
    return 0;
}
void recordCostTime(auto f) {
    unsigned int t = time(NULL);
    f();
    if (g_time > t) t = g_time;
    cout << " - Cost " << time(NULL) - t << " Seconds!!" << endl;
}

void autoIni(Park& p) {
    ovo::math m;
    std::vector<std::map<string, int>> ParkIniInfo;
    std::map<string, int> t_map;

    recordCostTime([&] {
        for (int i = 0; i < 100; i++) {
            t_map["Car"] = m.rand(0, 600);
            t_map["Bicycle"] = m.rand(0, 600);
            t_map["Airplane"] = m.rand(0, 600);
            t_map["Ship"] = m.rand(0, 600);
            ParkIniInfo.push_back(t_map);
        }

        p.ini(ParkIniInfo);
    });
    cout << endl
         << "Generated " << p.getPlotsID().size() << " Plots in "
         << p.getMaxLevel() << " Floors!!" << endl;
    system("pause");

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

void manualIni(Park& p) {
    ovo::math m;
    std::vector<std::map<string, int>> ParkIniInfo;
    std::map<string, int> t_map;

    system("cls");

    cout << "Please Input the Floors you want = ";
    int t;
    char c;
    cin >> t;
    std::vector<string> types;
    string s;
    cout << "Please Input the types (split by space) = ";
    getchar();

    while ((c = getchar()) != '\n') {
        if (c != ' ') {
            ungetc(c, stdin);
            cin >> s;
            types.push_back(s);
        }
    }

    for (int i = 0; i < t; i++) {
        cout << endl << "This is Floor " << i << ":" << endl;
        for (string ii : types) {
            cout << "The Number of " << ii << " = ";
            cin >> t_map[ii];
            t_map[ii];
        }
        ParkIniInfo.push_back(t_map);
    }

    p.ini(ParkIniInfo);

    cout << endl
         << "Generated " << p.getPlotsID().size() << " Plots in "
         << p.getMaxLevel() << " Floors!!" << endl;
    system("pause");

    std::map<string, std::vector<int>> feeTable;
    std::vector<int> fee;

    for (int i = 0; i < 24; i++) {
        fee.push_back(0);
    }

    for (string i : types) {
        cout << endl
             << "This is " << i
             << " Type. Please set fee table (from 0 to 24 hours)!!" << endl;
        for (int ii = 0; ii < 24; ii++) {
            cout << "The " << ii << "th hour = ";
            cin >> fee[ii];
        }
        feeTable[i] = fee;
    }

    p.updateFeeTable(feeTable);
}

void displayInfo(auto f, auto get) {
    while (1) {
        system("cls");

        std::vector<string> v;
        recordCostTime([&]() {
            v = f();
            cout << "Found " << v.size() << " items of data." << endl;
        });
        cout << endl << "1. back to menu." << endl;
        cout << "2. show All." << endl << endl;

        cout << "Please select = ";
        string s;
        cin >> s;

        if (s == "1") {
            return;
        }

        if (s == "2") {
            for (auto i : v) {
                cout << get(i).showAll();
                cout << endl;
            }

            system("pause");
        }
    }
}

void displayLog(auto f) {
    while (1) {
        system("cls");

        std::vector<ovo::data> v;
        recordCostTime([&]() {
            v = f();
            cout << "Found " << v.size() << " items of Log." << endl;
        });
        cout << endl << "1. back to menu." << endl;
        cout << "2. show All." << endl << endl;

        cout << "Please select = ";
        string s;
        cin >> s;

        if (s == "1") {
            return;
        }

        if (s == "2") {
            for (auto i : v) {
                cout << i.showAll();
                cout << endl;
            }

            system("pause");
        }
    }
}