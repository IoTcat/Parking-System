/*
 * @Author: IoTcat (https://iotcat.me) 
 * @Date: 2019-05-24 17:01:44 
 * @Last Modified by:   IoTcat 
 * @Last Modified time: 2019-05-24 17:01:44 
 */

#ifndef __CAR_H__
#define __CAR_H__

#include <iostream>
#include <vector>
#include <string>
#include "../lib/ovo.h"


using namespace std;

class Car{

public:
    Car(const string& licenseNum, const string& type, const string& plot);
    Car(const string& s);
    Car(){

        this->_isExist = false;
    };
    ~Car(){};

    inline const bool isExist() const{
        return this->_isExist;
    };

    inline const string getID(){
        return this->_d["id"];
    };

    inline const string getType(){
        return this->_d["type"];
    };

    inline const string getLastInTime(){
        return this->_d["LastInTime"];
    };

    inline const string getLastOutTime(){
        return this->_d["LastOutTime"];
    };

    inline const string getPlot(){
        return this->_d["plot"];
    };

    inline const string showAll(){
        return this->_d.showAll();
    };

    inline const string getDataStr(){
        this->_d.classify();
        return this->_d.dataToStr(this->_d);
    };

private:
    ovo::data _d;
    bool _isExist;


};


#endif //__CAR_H__