




#ifndef __CAR_H__
#define __CAR_H__

#include <iostream>
#include <vector>
#include <string>
#include "../lib/ovo.h"


using namespace std;

class Car{

public:
    Car(const string& licenseNum, const string& type){
        this->_d["id"] = licenseNum;
        this->_d["type"] = type;
        this->_d["plot"] = "null";
        this->_d["LastInTime"] = "null";
        this->_d["LastOutTime"] = "null";
        this->_isExist = true;
    };

    Car(const string& licenseNum){

        this->_d = db.getData(licenseNum);
        this->_isExist = true;
    };

    ~Car(){

        this->_d.classify();
        db.pushData(this->_d["id"], this->_d);
    };

    inline bool isExist(){
        return this->_isExist;
    };

    inline string getID(){
        return this->_d["id"];
    };

    inline string getType(){
        return this->_d["type"];
    };

    inline string getPlot(){
        return this->_d["plot"];
    };


private:
    ovo::data _d;
    ovo::db db;
    bool _isExist;


};


#endif //__CAR_H__