/*
 * @Author: IoTcat (https://iotcat.me) 
 * @Date: 2019-05-24 17:01:21 
 * @Last Modified by:   IoTcat 
 * @Last Modified time: 2019-05-24 17:01:21 
 */


#ifndef __PARK_H__
#define __PARK_H__

#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <vector>
#include "../lib/ovo.h"

#include "car.h"
#include "feeTable.h"
#include "plot.h"

const string g_ParkID = "EEE102AS4";

using namespace std;

class Park {
   public:
    Park();
    ~Park();

    void join();
    void ini(std::vector<std::map<string, int>>& v);

    const vector<string> getPlotsID();
    const std::vector<string> getPlotsID(const bool& isOccupied);
    const std::vector<string> getPlotsID(const int& level);
    const std::vector<string> getPlotsID(const string& type);
    const std::vector<string> getPlotsID(const int& level,
                                         const bool& isOccupied);
    const std::vector<string> getPlotsID(const string& type,
                                         const bool& isOccupied);
    const std::vector<string> getPlotsID(const int& level, const string& type);
    const std::vector<string> getPlotsID(const int& level, const string& type,
                                         const bool& isOccupied);
    Plot getPlot(const string& id);
    Plot getPlotByCar(const string& licenseNum);
    Plot getPlotByCar(Car& car);

    const bool newCar(const string& licenseNum, const string& type,
                      const string& plotID, string& msg);
    const bool delCar(const string& licenseNum, string& msg);

    const std::vector<string> getCarsID();
    const std::vector<string> getCarsID(const int& level);
    const std::vector<string> getCarsID(const string& type);
    const std::vector<string> getCarsID(const int& level, const string& type);

    const bool updatePlot(Plot& plot, const int& level);
    const bool updatePlot(Plot& plot, const string& type);

    const bool checkIn(const string& licenseNum, const string& type,
                       string& msg);
    const bool checkIn(const string& licenseNum, const string& type,
                       const int& level, string& msg);
    const bool checkInByPlotID(const string& licenseNum, const string& type,
                               const string& plotID, string& msg);
    int checkOut(const string& licenseNum);

    inline bool isExist() {
        if (this->_d["_isExist"] == "NO") {
            return false;
        }
        return true;
    };

    inline int getMaxLevel() const {
        if (!this->_threadFinished) this->_t->join();
        return this->_levels;
    };

    inline void updateFeeTable(std::map<string, std::vector<int>>& m) {
        this->_feeTable.set(m);
    };

    inline const std::vector<string> getPlotsID(const string& type,
                                                const int& level) {
        return this->getPlotsID(level, type);
    };

    inline const std::vector<string> getPlotsID(const string& type,
                                                const int& level,
                                                const bool& isOccupied) {
        return this->getPlotsID(level, type, isOccupied);
    };

    inline const bool newCar(const string& licenseNum, const string& type,
                             const string& plotID) {
        string s;
        return this->newCar(licenseNum, type, plotID, s);
    };

    inline const bool delCar(const string& licenseNum) {
        string s;
        return this->delCar(licenseNum, s);
    };

    inline Car getCar(const string& licenseNum) {
        if (!this->_threadFinished) this->_t->join();
        if (this->_carsList[licenseNum] == "undefined") {
            return Car();
        }
        return Car(this->_carsList[licenseNum]);
    };

    inline Car getCarByPlot(string& id) {
        if (!this->_threadFinished) this->_t->join();
        if (this->_carsList[id] == "undefined") {
            return Car();
        }
        Plot p = this->getPlot(id);
        return Car(this->_carsList[p.getCar()]);
    };

    inline Car getCarByPlot(Plot& p) {
        if (!this->_threadFinished) this->_t->join();
        if (this->_carsList[p.getCar()] == "undefined") {
            return Car();
        }
        return Car(this->_carsList[p.getCar()]);
    };

    inline const bool checkIn(const string& licenseNum, const string& type) {
        string msg;
        return checkIn(licenseNum, type, msg);
    };

    inline const bool checkIn(const string& licenseNum, const string& type,
                              const int& level) {
        string msg;
        return checkIn(licenseNum, type, level, msg);
    };

    inline const bool checkInByPlotID(const string& licenseNum,
                                      const string& type,
                                      const string& plotID) {
        string msg;
        return checkInByPlotID(licenseNum, type, plotID, msg);
    };

    inline std::vector<ovo::data> getLog(ovo::data FilterData) {
        return db.getSQL(this->_d["log"], FilterData);
    };

    inline std::vector<ovo::data> getLog() {
        return db.getSQL(this->_d["log"]);
    };

    inline std::vector<ovo::data> getLogByCarID(const string& licenseNum) {
        ovo::data d;
        d["licenseNum"] = licenseNum;
        return db.getSQL(this->_d["log"], d);
    };

    inline std::vector<ovo::data> getLogByType(const string& type) {
        ovo::data d;
        d["type"] = type;
        return db.getSQL(this->_d["log"], d);
    };

    inline std::vector<ovo::data> getLogByType(const string& type,
                                               const string& date) {
        ovo::data d;
        d["type"] = type;
        d["date"] = date;
        return db.getSQL(this->_d["log"], d);
    };

    inline std::vector<ovo::data> getLogByLevel(const int& level) {
        ovo::data d;
        d["level"] = to_string(level);
        return db.getSQL(this->_d["log"], d);
    };

    inline std::vector<ovo::data> getLogByLevel(const int& level,
                                                const string& date) {
        ovo::data d;
        d["level"] = to_string(level);
        d["date"] = date;
        return db.getSQL(this->_d["log"], d);
    };

    inline std::vector<ovo::data> getLogByFee(const int& fee) {
        ovo::data d;
        d["fee"] = to_string(fee);
        return db.getSQL(this->_d["log"], d);
    };

    inline std::vector<ovo::data> getLogByPlotID(const string& plot) {
        ovo::data d;
        d["plot"] = plot;
        return db.getSQL(this->_d["log"], d);
    };

    inline std::vector<ovo::data> getLogByDate(
        const string& date) {  // 2019-05-24
        ovo::data d;
        d["date"] = date;
        return db.getSQL(this->_d["log"], d);
    };

private:
    ovo::data _d, _carsList, _plotsList;
    // ovo::index _isOccupiedIndex, _typeIndex, _levelIndex;
    std::vector<string> _types;
    unsigned int _levels;
    ovo::math m;
    ovo::String S;
    ovo::db db;
    std::thread* _t;
    bool _threadFinished, _threadPointer, _needStoreData;
    FeeTable _feeTable;

    void _storeData();
    void _getTypes(std::vector<std::map<string, int>>& v);
    void _setupPlots(std::vector<std::map<string, int>>& v);

    const string _simpleGet(const string& s, const string& what);
    const string _simpleUpdate(const string& s, const string& what,
                               const string& to);
    const string _getDate() const;

    inline const string _simplePlot(const string& id, const int& level,
                                    const string& type) {
        return "__OVO_DATA__id$$||$$" + id + "$$||$$level$$||$$" +
               to_string(level) + "$$||$$type$$||$$" + type +
               "$$||$$car$$||$$null$$||$$LastOperateTime$$||$$" +
               to_string(time(NULL)) + "$$||$$CreatedTime$$||$$" +
               to_string(time(NULL)) + "$$||$$";
    };

    inline void _recoverTypes() {
        S.split(this->_d["types"], this->_types, "|||$$|||");
    };

    inline const bool isGoodType(const string& type) const {
        return (bool)(find(this->_types.begin(), this->_types.end(), type) ==
                      this->_types.end());
    };
};

#endif  //__PARK_H__