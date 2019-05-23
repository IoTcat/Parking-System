




#ifndef __CAR_H__
#define __CAR_H__

#include <iostream>
#include <vector>
#include <string>
#include "../lib/ovo.h"


using namespace std;

class Car{

public:
    Car(const string& licenseNum, const string& type, const string& plot){
        this->_d["id"] = licenseNum;
        this->_d["type"] = type;
        this->_d["plot"] = plot;
        this->_d["LastInTime"] = to_string(time(NULL));
        this->_d["LastOutTime"] = "null";
        this->_isExist = true;
    };

    Car(const string& s){

        this->_isExist = false;

        if(s == "undefined"){
            return;
        }

        this->_d = this->_d.strToData(s);

        if(this->_d["id"] == "undefined") return;

        this->_isExist = true;
    };

    Car(){

        this->_isExist = false;
    };

    ~Car(){

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

    inline string getLastInTime(){
        return this->_d["LastInTime"];
    };

    inline string getLastOutTime(){
        return this->_d["LastOutTime"];
    };


    inline string getPlot(){
        return this->_d["plot"];
    };

    inline string showAll(){
        return this->_d.showAll();
    };

    inline string getDataStr(){

        this->_d.classify();
        return this->_d.dataToStr(this->_d);
    };

private:
    ovo::data _d;
    bool _isExist;


};


#endif //__CAR_H__