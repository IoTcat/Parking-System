

#ifndef __PLOT_H__
#define __PLOT_H__

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "../lib/ovo.h"

using namespace std;

class Plot{

public:
    Plot(const string& id, const unsigned int& level, const string& type){
        this->_d["id"] = id;
        this->_d["level"] = to_string(level);
        this->_d["type"] = type;
        this->_d["car"] = "null";
        this->_d["LastOperateTime"] = to_string(time(NULL));
        this->_d["CreatedTime"] = to_string(time(NULL));
        this->_isExist = true;
    };

    Plot(const string& s){

        this->_d = this->_d.strToData(s);
        this->_isExist = true;
    };

    Plot(const string& id, const string& isExist){

        this->_isExist = false;
    };
    
    ~Plot(){

        this->_d.classify();
        db.pushData(this->_d["id"], this->_d);
    };

    inline isExist(){
        return this->_isExist;
    };

    inline string getID(){
        return this->_d["id"];
    };

    inline int getLevel(){
        return atoi(this->_d["level"].c_str());
    };

    inline string getType(){
        return this->_d["type"];
    };

    inline string getCar(){
        return this->_d["car"];
    };

    inline bool isOccupied(){
        return (this->_d["car"] == "null") ? false : true;
    };

    inline void updateLevel(const unsigned int& level){
        this->_d["level"] = to_string(level);
    };

    inline void updateType(const string& type){
        this->_d["type"] = type;
    };

    friend class Park;

//private:
    ovo::data _d;
    ovo::db db;
    bool _isExist;
    string getStrContent(){

        return this->_d.dataToStr(this->_d);
    };


};


#endif //__PLOT_H__