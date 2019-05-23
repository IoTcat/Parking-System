

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

const string g_ParkID = "EEE102AS4";

using namespace std;

class Park{

public:
    Park(){

        this->_threadFinished = true;

        this->_d = db.getData(g_ParkID);
        if(!this->isExist()) return ;

        this->_threadFinished = false;

        this->_t = new std::thread([&]{

            this->_plotsList = db.getData(this->_d["plotsList"]);
            this->_carsList = db.getData(this->_d["carsList"]);

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
            this->_threadFinished = true;
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
    };*/

    std::vector<Plot> getPlots(){
        if(!this->_threadFinished) this->_t->join();
        std::vector<Plot> v;
        this->_plotsList.forEach([&](string first, string second){
            v.push_back(Plot(second));
        });
        return v;
    };

    std::vector<string> getPlotsID(){
        if(!this->_threadFinished) this->_t->join();
        std::vector<string> v;
        this->_plotsList.forEach([&](string first, string second){
            v.push_back(this->_plotsList.strToData(second)["id"]);
        });
        return v;
    };
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
        this->_getTypes(v);
        this->_levels = v.size();
        this->_d["id"] = g_ParkID;
        this->_d["carsList"] = m.randStr();
        this->_d["plotsList"] = m.randStr();
        this->_d["levels"] = this->_levels;
        this->_d["types"] = "";
        for(string i : this->_types){

            this->_d["types"] += i + "|||$$|||";
        }
        this->_setupPlots(v);

    };
    

//private:
    ovo::data _d, _carsList, _plotsList;
    std::vector<string> _types;
    unsigned int _levels;
    ovo::math m;
    ovo::String S;
    ovo::db db;
    std::thread *_t;
    bool _threadFinished;

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

        int t = time(NULL);
        for(unsigned int i = 0; i < v.size(); i ++){

            for(auto ii : v[i]){

                for(int iii = 0; iii < ii.second; iii ++){
                    string s = m.randStr();
                    this->_plotsList[s] = this->_simplePlot(s, i, ii.first);
                }
            }
        }

        cout << "Used" << time(NULL) - t;
    };

    string _simplePlot(const string& id, const int& level, const string& type){

        return "__OVO_DATA__id$$||$$" + id + "$$||$$level$$||$$" + to_string(level) + "$$||$$type$$||$$"
        + type + "$$||$$car$$||$$null$$||$$LastOperateTime$$||$$null$$||$$CreatedTime$$||$$null$$||$$";
    }

};





#endif //__PARK_H__