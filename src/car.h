




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
    };

    Car(const string& licenseNum){

        this->_d = db.getData(licenseNum);
    };

    ~Car(){

        this->_d.classify();
        db.pushData(this->_d["id"], this->_d);
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


};


#endif //__CAR_H__