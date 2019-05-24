/*
 * @Author: IoTcat (https://iotcat.me) 
 * @Date: 2019-05-24 17:01:11 
 * @Last Modified by:   IoTcat 
 * @Last Modified time: 2019-05-24 17:01:11 
 */


#ifndef __PLOT_H__
#define __PLOT_H__

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include "../lib/ovo.h"

using namespace std;

class Plot {
   public:
    Plot(const string& id, const unsigned int& level, const string& type);
    Plot(const string& plot);
    Plot() { this->_isExist = false; };
    ~Plot(){};

    inline const bool isExist() const { return this->_isExist; };

    inline const string getID() { return this->_d["id"]; };

    inline const int getLevel() { return atoi(this->_d["level"].c_str()); };

    inline const string getType() { return this->_d["type"]; };

    inline const string getCar() { return this->_d["car"]; };

    inline const bool isOccupied() {
        return (this->_d["car"] == "null") ? false : true;
    };

    inline const string showAll() { return this->_d.showAll(); };

    friend class Park;

   private:
    ovo::data _d;
    bool _isExist;
    inline const string getStrContent() {
        return this->_d.dataToStr(this->_d);
    };

    inline void updateLevel(const unsigned int& level) {
        this->_d["level"] = to_string(level);
    };

    inline void updateType(const string& type) { this->_d["type"] = type; };
};

#endif  //__PLOT_H__