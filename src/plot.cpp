/*
 * @Author: IoTcat (https://iotcat.me) 
 * @Date: 2019-05-24 17:01:19 
 * @Last Modified by:   IoTcat 
 * @Last Modified time: 2019-05-24 17:01:19 
 */


#include "plot.h"

Plot::Plot(const string& id, const unsigned int& level, const string& type) {
    this->_d["id"] = id;
    this->_d["level"] = to_string(level);
    this->_d["type"] = type;
    this->_d["car"] = "null";
    this->_d["LastOperateTime"] = to_string(time(NULL));
    this->_d["CreatedTime"] = to_string(time(NULL));
    this->_isExist = true;
}

Plot::Plot(const string& s) {
    this->_isExist = false;
    if (s == "undefined") {
        return;
    }
    this->_d = this->_d.strToData(s);
    if (this->_d["id"] == "undefined") {
        return;
    }
    this->_isExist = true;
}
