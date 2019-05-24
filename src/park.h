

#ifndef __PARK_H__
#define __PARK_H__

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <map>
#include <thread>
#include "../lib/ovo.h"

#include "plot.h"
#include "car.h"
#include "feeTable.h"

const string g_ParkID = "EEE102AS4";

using namespace std;

class Park{

public:
    Park(){

        this->_threadFinished = true;
        this->_threadPointer = false;

        this->_d = db.getData(g_ParkID);
        if(!this->isExist()) return ;

        this->_threadFinished = false;

        this->_t = new std::thread([&]{

            this->_threadPointer = true;

            this->_plotsList = db.getData(this->_d["plotsList"]);
            this->_carsList = db.getData(this->_d["carsList"]);
            this->_recoverTypes();
            this->_levels = atoi(this->_d["levels"].c_str());
            this->_threadFinished = true;


        });


    };



    ~Park(){

        if(!this->_threadFinished) this->_t->join();

        this->_d.classify();
        this->_plotsList.classify();
        this->_carsList.classify();
        db.pushData(g_ParkID, this->_d);
        db.pushData(this->_d["plotsList"], this->_plotsList);
        db.pushData(this->_d["carsList"], this->_carsList);
    };

    void join(){
        if(!this->_threadFinished) 
        {
            this->_t->join();

            delete this->_t;
            this->_threadPointer = false;
            this->_threadFinished = true;
        }

        if(this->_threadPointer){

            delete this->_t;
            this->_threadPointer = false;
        }
    }

    bool isExist(){

        if(this->_d["_isExist"] == "NO"){
            return false;
        }
        return true;
    };

    inline int getMaxLevel(){
        if(!this->_threadFinished) this->_t->join();
        return this->_levels;
    }
/*
    bool checkType(const string& type){
        if(!this->_threadFinished) this->_t->join();
        if(find(this->_types.begin(), this->_types.end(), type) == this->_types.end()){
            return false;
        }
        return true;
    };

    std::vector<Plot> getPlots(){
        if(!this->_threadFinished) this->_t->join();
        std::vector<Plot> v;
        this->_plotsList.forEach([&](string first, string second){
            v.push_back(Plot(second));
        });
        return v;
    };
*/
  /*  std::vector<string> getPlotsID(){
        if(!this->_threadFinished) this->_t->join();
        std::vector<string> v;
        this->_plotsList.forEach([&](string first, string second){
            v.push_back(this->_plotsList.strToData(second)["id"]);
        });
        return v;
    };*/
/*
    std::vector<Plot> getPlots(bool isOccupied){
        if(!this->_threadFinished) this->_t->join();
        return this->_plots;
    };


    std::vector<Plot> getPlots(const int& level){
        if(!this->_threadFinished) this->_t->join();
        int t = time(NULL);
        std::vector<Plot> v;
        for(auto i : this->_plots){
            if(i.getLevel() == level){
                v.push_back(i);
            }
        }
        cout << endl << time(NULL) - t << endl;
        return v;
    };

    std::vector<Plot> getPlots(const string& type){
        if(!this->_threadFinished) this->_t->join();
        int t = time(NULL);
        std::vector<Plot> v;
        for(auto i : this->_plots){
            if(i.getType() == type){
                v.push_back(i);
            }
        }
        cout << endl << time(NULL) - t << endl;
        return v;
    };

    std::vector<Plot> getPlots(const int& level, const string& type){
        return getPlots(type, level);
    }

    std::vector<Plot> getPlots(const string& type, const int& level){
        if(!this->_threadFinished) this->_t->join();
        int t = time(NULL);
        std::vector<Plot> v;
        for(auto i : this->_plots){
            if(i.getLevel() == level && i.getType() == type){
                v.push_back(i);
            }
        }
        cout << endl << time(NULL) - t << endl;
        return v;
    };

    Plot getPlot(Car& car){
        if(!this->_threadFinished) this->_t->join();
        int t = time(NULL);
        if(car.getPlot() == "null") throw "Park::getPlots::Plot Not Exist!!!";
        for(auto i : this->_plots){
            if(i.getID() == car.getPlot()){
                return i;
            }
        }
        cout << endl << time(NULL) - t << endl;
        return Plot("null", "null");
    };

    std::vector<Car> getCars(){
        if(!this->_threadFinished) this->_t->join();
        return this->_cars;
    };

    std::vector<Car> getCars(const int& level){
        if(!this->_threadFinished) this->_t->join();
        int t = time(NULL);
        std::vector<Car> v;
        for(auto i : this->_plots){
            if(i.getLevel() == level && i.getCar() != "null"){
                for(auto ii : this->_cars){
                    if(ii.getID() == i.getCar()){
                        v.push_back(ii);
                        break;
                    }
                }
            }
        }
        cout << endl << time(NULL) - t << endl;
        return v;
    };

    std::vector<Car> getCars(const string& type){
        if(!this->_threadFinished) this->_t->join();
        int t = time(NULL);
        std::vector<Car> v;
        for(auto i : this->_cars){
            if(i.getType() == type){
                v.push_back(i);
            }
        }
        cout << endl << time(NULL) - t << endl;
        return v;
    };

    std::vector<Car> getCars(const int& level, const string& type){
        return getCars(type, level);
    }

    std::vector<Car> getCars(const string& type, const int& level){
        if(!this->_threadFinished) this->_t->join();
        int t = time(NULL);
        std::vector<Car> v, v1, v2;

        v1 = this->getCars(type);
        v2 = this->getCars(level);

        // 待实现 

        cout << endl << time(NULL) - t << endl;
        return v;
    };

    Car getCar(Plot& p){
        if(!this->_threadFinished) this->_t->join();
        return Car(p.getCar());
    }

    void checkIn(const string& licenseNum, const string& type){
        if(!this->_threadFinished) this->_t->join();

        if(!this->checkType(type)) throw "Park::checkIn::Wrong Type!!";
        Car c = Car(licenseNum, type);
    
        this->_cars.push_back(c);
        this->_carsList[licenseNum] = time(NULL);
    };

    Car checkIn(const string& licenseNum, const string& type, const int& level){
        if(!this->_threadFinished) this->_t->join();

        if(!this->checkType(type)) throw "Park::checkIn::Wrong Type!!";
        Car c = Car(licenseNum, type);
        this->_cars.push_back(c);
        this->_carsList[licenseNum] = time(NULL);
        return c;
    };
*/

    void ini(std::vector<std::map<string, int>>& v){

        if(!this->_threadFinished) this->_t->join();

        this->_d.clear();
        this->_plotsList.clear();
        this->_carsList.clear();
        this->_getTypes(v);
        this->_levels = v.size();
        this->_d["id"] = g_ParkID;
        this->_d["carsList"] = m.randStr();
        this->_d["plotsList"] = m.randStr();
        this->_d["feeTable"] = m.randStr();
        this->_d["log"] = m.randStr();
        this->_d["levels"] = to_string(this->_levels);
        this->_d["types"] = "";
        for(string i : this->_types){

            this->_d["types"] += i + "|||$$|||";
        }
        this->_setupPlots(v);
        this->_feeTable.setTypes(this->_types);

        std::vector<string> vv;
        vv.push_back("uid");
        vv.push_back("licenseNum");
        vv.push_back("type");
        vv.push_back("level");
        vv.push_back("plot");
        vv.push_back("LastInTime");
        vv.push_back("LastOutTime");
        vv.push_back("fee");
        vv.push_back("date");

        db.createTable(this->_d["log"],  vv);

    };

    void updateFeeTable(std::map<string, std::vector<int>>& m){
        this->_feeTable.set(m);
    }
    
    vector<string> getPlotsID(){
        if(!this->_threadFinished) this->_t->join();
        std::vector<string> v;
        this->_plotsList.forEach([&](string first, string second){
            v.push_back(first);
        });

        return v;
    };

    std::vector<string> getPlotsID(const bool& isOccupied){
        if(!this->_threadFinished) this->_t->join();
        std::vector<string> v;
        this->_plotsList.forEach([&](string first, string second){
            if(isOccupied && this->_simpleGet(second, "car") != "null") v.push_back(first);
            if(!isOccupied && this->_simpleGet(second, "car") == "null") v.push_back(first);
        });
        return v;
    };

    std::vector<string> getPlotsID(const int& level){
        if(!this->_threadFinished) this->_t->join();
        std::vector<string> v;
        this->_plotsList.forEach([&](string first, string second){
            if(this->_simpleGet(second, "level") == to_string(level)) v.push_back(first);
        });
        return v;
    };

    std::vector<string> getPlotsID(const string& type){
        if(!this->_threadFinished) this->_t->join();
        std::vector<string> v;
        this->_plotsList.forEach([&](string first, string second){
            if(this->_simpleGet(second, "type") == type) v.push_back(first);
        });
        return v;
    };

    std::vector<string> getPlotsID(const int& level, const bool& isOccupied){
        if(!this->_threadFinished) this->_t->join();
        std::vector<string> v;
        this->_plotsList.forEach([&](string first, string second){
            if(isOccupied && this->_simpleGet(second, "car") != "null" && this->_simpleGet(second, "level") == to_string(level)) v.push_back(first);
            if(!isOccupied && this->_simpleGet(second, "car") == "null" && this->_simpleGet(second, "level") == to_string(level)) v.push_back(first);
        });
        return v;
    };

    std::vector<string> getPlotsID(const string& type, const bool& isOccupied){
        if(!this->_threadFinished) this->_t->join();
        std::vector<string> v;
        this->_plotsList.forEach([&](string first, string second){
            if(isOccupied && this->_simpleGet(second, "car") != "null" && this->_simpleGet(second, "type") == type) v.push_back(first);
            if(!isOccupied && this->_simpleGet(second, "car") == "null" && this->_simpleGet(second, "type") == type) v.push_back(first);
        });
        return v;
    };


    std::vector<string> getPlotsID(const int& level, const string& type){
        if(!this->_threadFinished) this->_t->join();
        std::vector<string> v;
        this->_plotsList.forEach([&](string first, string second){
            if(this->_simpleGet(second, "level") == to_string(level) && this->_simpleGet(second, "type") == type) v.push_back(first);
        });
        return v;
    };

    std::vector<string> getPlotsID(const string& type, const int& level){

        return this->getPlotsID(level, type);
    }


    std::vector<string> getPlotsID(const int& level, const string& type, const bool& isOccupied){
        if(!this->_threadFinished) this->_t->join();
        std::vector<string> v;
        this->_plotsList.forEach([&](string first, string second){
            if(isOccupied && this->_simpleGet(second, "car") != "null" && this->_simpleGet(second, "level") == to_string(level) && this->_simpleGet(second, "type") == type) v.push_back(first);
            if(!isOccupied && this->_simpleGet(second, "car") == "null" && this->_simpleGet(second, "level") == to_string(level) && this->_simpleGet(second, "type") == type) v.push_back(first);
        });
        return v;
    };

    inline std::vector<string> getPlotsID(const string& type, const int& level, const bool& isOccupied){

        return this->getPlotsID(level, type, isOccupied);
    };


    Plot getPlot(const string& id){
        if(this->_plotsList[id] == "undefined"){

            return Plot();
        }
        return Plot(this->_plotsList[id]);
    };



    Plot getPlotByCar(const string& licenseNum){

        if(this->_carsList[licenseNum] == "undefined"){

            return Plot();
        }

        return Plot(this->_plotsList[this->_simpleGet(this->_carsList[licenseNum], "plot")]);
    };



    Plot getPlotByCar(Car& car){

        if(this->_carsList[car.getID()] == "undefined"){

            return Plot();
        }

        return Plot(this->_plotsList[this->_simpleGet(this->_carsList[car.getID()], "plot")]);
    };


    bool newCar(const string& licenseNum, const string& type, const string& plotID){
        string s;
        return this->newCar(licenseNum, type, plotID, s);
    }
    bool newCar(const string& licenseNum, const string& type, const string& plotID, string& msg){

        if(licenseNum.length() < 1){

            msg += "Car " + licenseNum + " LicenseNum Illegal!!!";
            return false;
        }

        if(this->_carsList.isExist(licenseNum)){

            msg += "Car " + licenseNum + " Already in the Park!!";
            return false;
        }

        if(this->isGoodType(type)){

            msg += "Car " + licenseNum + " Wrong Type!!!";
            return false;
        }

        if(this->_plotsList[plotID] == "undefined"){

            msg += "Car " + licenseNum + " Assigned Plot Not Exist!!!";
            return false;
        }

        Car c(licenseNum, type, plotID);

        this->_carsList[licenseNum] = c.getDataStr();
        this->_plotsList[plotID] = this->_simpleUpdate(this->_plotsList[plotID], "car", licenseNum);

        return true;
    };

    bool delCar(const string& licenseNum){

        string s;
        return this->delCar(licenseNum, s);
    }

    bool delCar(const string& licenseNum, string& msg){

        if(!this->_carsList.isExist(licenseNum)){

            msg += "Car " + licenseNum + " Not In Plot!!!";
            return false;
        }

        Car c(this->_carsList[licenseNum]);

        this->_plotsList[c.getPlot()] = this->_simpleUpdate(this->_plotsList[c.getPlot()], "car", "null");
        this->_carsList.clear(licenseNum);
        return true;
    }



    std::vector<string> getCarsID(){

        if(!this->_threadFinished) this->_t->join();
        std::vector<string> v;
        this->_carsList.forEach([&](string first, string second){
            v.push_back(first);
        });

        return v;
    };


    std::vector<string> getCarsID(const int& level){

        std::vector<string> v;

        v = this->getPlotsID(level, true);

        for(string& i : v){

            i = this->_simpleGet(this->_plotsList[i], "car");
        }

        return v;
    };

    std::vector<string> getCarsID(const string& type){

        std::vector<string> v;

        v = this->getPlotsID(type, true);

        for(string& i : v){

            i = this->_simpleGet(this->_plotsList[i], "car");
        }

        return v;
    };

    std::vector<string> getCarsID(const int& level, const string& type){

        std::vector<string> v;

        v = this->getPlotsID(level, type, true);

        for(string& i : v){

            i = this->_simpleGet(this->_plotsList[i], "car");
        }

        return v;
    };


    Car getCar(const string& licenseNum){

        if(this->_carsList[licenseNum] == "undefined"){

            return Car();
        }

        return Car(this->_carsList[licenseNum]);
    }


    Car getCarByPlot(string& id){

        if(this->_carsList[id] == "undefined"){

            return Car();
        }

        Plot p = this->getPlot(id);

        return Car(this->_carsList[p.getCar()]);
    }


    inline Car getCarByPlot(Plot& p){

        if(this->_carsList[p.getCar()] == "undefined"){

            return Car();
        }

        return Car(this->_carsList[p.getCar()]);
    }



    bool updatePlot(Plot& plot, const int& level){

        if(level < 0 || level > this->_levels){
            return false;
        }

        this->_plotsList[plot.getID()] = this->_simpleUpdate(this->_plotsList[plot.getID()], 
            "level", to_string(level)); 

        plot.updateLevel(level);

        return true;
    }

    bool updatePlot(Plot& plot, const string& type){

        if(!this->isGoodType(type)){

            return false;
        }

        this->_plotsList[plot.getID()] = this->_simpleUpdate(this->_plotsList[plot.getID()], 
            "type", type); 

        plot.updateType(type);

        return true;
    }


    bool checkIn(const string& licenseNum, const string& type){
        string msg;
        return checkIn(licenseNum, type, msg);
    }

    bool checkIn(const string& licenseNum, const string& type, string& msg){


        std::vector<string> v = this->getPlotsID(type, false);

        if(!v.size()){
            msg += type + " has no more Plots!!";
            return false;
        }

        if(!newCar(licenseNum, type, v[0], msg)) return false;

        return true;
    }

    bool checkIn(const string& licenseNum, const string& type, const int& level){

        string msg;
        return checkIn(licenseNum, type, level, msg);
    }
    bool checkIn(const string& licenseNum, const string& type, const int& level, string& msg){


        std::vector<string> v = this->getPlotsID(level, type, false);

        if(!v.size()){
            msg += type + " on Level " + to_string(level) + " has no more Plots!!";
            return false;
        }

        if(!newCar(licenseNum, type, v[0], msg)) return false;

        return true;
    }

    bool checkInByPlotID(const string& licenseNum, const string& type, const string& plotID){

        string msg;
        return checkInByPlotID(licenseNum, type, plotID, msg);
    }
    bool checkInByPlotID(const string& licenseNum, const string& type, const string& plotID, string& msg){

        if(!newCar(licenseNum, type, plotID, msg)) return false;
        return true;
    }

    int checkOut(const string& licenseNum){

        if(!this->_carsList.isExist(licenseNum)) return -1;
        this->_carsList[licenseNum] = this->_simpleUpdate(this->_carsList[licenseNum], "LastOutTime", to_string(time(NULL)));
        
        Car c(this->_carsList[licenseNum]);

        int fee = this->_feeTable.getFee(c.getType(), c.getLastInTime(), c.getLastOutTime());

        //this->_threadFinished = false;

        //this->_t = new std::thread([&]{

            //this->_threadPointer = true;

            ovo::data d;
            d["uid"] = m.randStr();
            d["licenseNum"] = licenseNum;
            d["type"] = c.getType();
            d["plot"] = c.getPlot();
            d["level"] = this->_simpleGet(this->_plotsList[c.getPlot()], "level");
            d["LastInTime"] = c.getLastInTime();
            d["LastOutTime"] = c.getLastOutTime();
            d["fee"] = to_string(fee);
            d["date"] = this->_getDate();

            db.insertSQL(this->_d["log"], d);

            this->delCar(licenseNum);

            //this->_threadFinished = true;
        //});

        return fee;
    }


    std::vector<std::map<string, string>> getLog(std::map<string, string> Filter){

        ovo::data d;
        std::vector<ovo::data> v;
        std::vector<std::map<string, string>> o;
        for(auto i : Filter){
            d[i.first] = d[i.second];
        }

        v = db.getSQL(this->_d["log"], d);

        for(auto i : v){

            o.push_back(i._data);
        }

        return o;
    }



    std::vector<ovo::data> getLog(ovo::data FilterData){

        return db.getSQL(this->_d["log"], FilterData);
    }


    std::vector<ovo::data> getLog(){

        return db.getSQL(this->_d["log"]);
    }

    std::vector<ovo::data> getLogByCarID(const string& licenseNum){

        ovo::data d;
        d["licenseNum"] = licenseNum;
        return db.getSQL(this->_d["log"], d);
    }

    std::vector<ovo::data> getLogByType(const string& type){

        ovo::data d;
        d["type"] = type;
        return db.getSQL(this->_d["log"], d);
    }

    std::vector<ovo::data> getLogByType(const string& type, const string& date){

        ovo::data d;
        d["type"] = type;
        d["date"] = date;
        return db.getSQL(this->_d["log"], d);
    }

    std::vector<ovo::data> getLogByLevel(const int& level){

        ovo::data d;
        d["level"] = to_string(level);
        return db.getSQL(this->_d["log"], d);
    }

    std::vector<ovo::data> getLogByLevel(const int& level, const string& date){

        ovo::data d;
        d["level"] = to_string(level);
        d["date"] = date;
        return db.getSQL(this->_d["log"], d);
    }

    std::vector<ovo::data> getLogByFee(const int& fee){

        ovo::data d;
        d["fee"] = to_string(fee);
        return db.getSQL(this->_d["log"], d);
    }

    std::vector<ovo::data> getLogByPlotID(const string& plot){

        ovo::data d;
        d["plot"] = plot;
        return db.getSQL(this->_d["log"], d);
    }


    std::vector<ovo::data> getLogByDate(const string& date){ //2019-05-24

        ovo::data d;
        d["date"] = date;
        return db.getSQL(this->_d["log"], d);
    }

//private:
    ovo::data _d, _carsList, _plotsList;
    ovo::index _isOccupiedIndex, _typeIndex, _levelIndex;
    std::vector<string> _types;
    unsigned int _levels;
    ovo::math m;
    ovo::String S;
    ovo::db db;
    std::thread *_t;
    bool _threadFinished, _threadPointer;
    FeeTable _feeTable;

    void _getTypes(std::vector<std::map<string, int>>& v){

        this->_types.clear(); //清空vec
        for(auto i : v){
            for(auto ii : i){
                if(find(this->_types.begin(), this->_types.end(), ii.first) == this->_types.end()){

                    this->_types.push_back(ii.first);
                }
            }
        }
    };

    void _setupPlots(std::vector<std::map<string, int>>& v){

        for(unsigned int i = 0; i < v.size(); i ++){

            for(auto ii : v[i]){

                for(int iii = 0; iii < ii.second; iii ++){
                    string s = m.randStr();
                    this->_plotsList[s] = this->_simplePlot(s, i, ii.first);
                    //cout << _simpleGet(_plotsList[s], "type") << endl;
                }
            }
        }

    };

    string _simplePlot(const string& id, const int& level, const string& type){

        return "__OVO_DATA__id$$||$$" + id + "$$||$$level$$||$$" + to_string(level) + "$$||$$type$$||$$"
        + type + "$$||$$car$$||$$null$$||$$LastOperateTime$$||$$" + to_string(time(NULL)) + "$$||$$CreatedTime$$||$$" + to_string(time(NULL)) + "$$||$$";
    }

    string _simpleGet(const string& s, const string& what){

        std::vector<string> v;
        S.split(s, v, "$$||$$");

        vector <string>::iterator it = find(v.begin(), v.end(), what);
        if(it != v.end()) return v[distance(v.begin(), it) + 1];
        return string();
    }

    string _simpleUpdate(const string& s, const string& what, const string& to){

        std::vector<string> v;
        S.split(s, v, "$$||$$");

        vector <string>::iterator it = find(v.begin(), v.end(), what);
        if(it == v.end()) return s;

        v[distance(v.begin(), it) + 1] = to;

        it = find(v.begin(), v.end(), "LastOperateTime");
        if(it != v.end()) v[distance(v.begin(), it) + 1] = to_string(time(NULL));

        string ss = "";
        for(string i : v){
            ss += i + "$$||$$";
        }

        return ss;
    }

    void _updateIndex(){

    };

    void _recoverTypes(){

        S.split(this->_d["types"], this->_types, "|||$$|||");
    }

    bool isGoodType(const string& type){
        return (bool)(find(this->_types.begin(), this->_types.end(), type) == this->_types.end());
    }

    string _getDate(){
        char now[64];
        time_t tt;
        struct tm *ttime;
        //tt = atol(argv[1]);
        //tt = 1212132599;  //uint
        time(&tt);
        ttime = localtime(&tt);
        strftime(now,64,"%Y-%m-%d",ttime);
        string s = now;
        return s;
    }

};





#endif //__PARK_H__