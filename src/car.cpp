/*
 * @Author: IoTcat (https://iotcat.me) 
 * @Date: 2019-05-24 17:01:37 
 * @Last Modified by:   IoTcat 
 * @Last Modified time: 2019-05-24 17:01:37 
 */


#include "car.h"

Car::Car(const string& licenseNum, const string& type, const string& plot) {
    this->_d["id"] = licenseNum;
    this->_d["type"] = type;
    this->_d["plot"] = plot;
    this->_d["LastInTime"] = to_string(time(NULL));
    this->_d["LastOutTime"] = "null";
    this->_isExist = true;
}

Car::Car(const string& s) {
    this->_isExist = false;

    if (s == "undefined") {
        return;
    }

    this->_d = this->_d.strToData(s);

    if (this->_d["id"] == "undefined") return;

    this->_isExist = true;
}
