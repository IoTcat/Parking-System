/*
 * @Author: IoTcat (https://iotcat.me) 
 * @Date: 2019-05-24 17:01:26 
 * @Last Modified by:   IoTcat 
 * @Last Modified time: 2019-05-24 17:01:26 
 */


#include "park.h"

Park::Park() {
    this->_threadFinished = true;
    this->_threadPointer = false;

    this->_d = db.getData(g_ParkID);

    if (!this->isExist()) return;

    this->_threadFinished = false;

    this->_t = new std::thread([&] {
        this->_threadPointer = true;

        this->_plotsList = db.getData(this->_d["plotsList"]);
        this->_carsList = db.getData(this->_d["carsList"]);
        this->_recoverTypes();
        this->_levels = atoi(this->_d["levels"].c_str());
        this->_threadFinished = true;
    });
};

Park::~Park() {
    this->_storeData();
};

void Park::join() {
    if (!this->_threadFinished) {
        this->_t->join();

        delete this->_t;
        this->_threadPointer = false;
        this->_threadFinished = true;
    }

    if (this->_threadPointer) {
        delete this->_t;
        this->_threadPointer = false;
    }
}

void Park::ini(std::vector<std::map<string, int>>& v) {
    if (!this->_threadFinished) this->_t->join();

    this->_d.clear();
    this->_plotsList.clear();
    this->_carsList.clear();
    this->_getTypes(v);
    this->_levels = v.size();
    this->_d["id"] = g_ParkID;
    this->_d["carsList"] = m.randStr();
    this->_d["plotsList"] = m.randStr();
    this->_d["feeTable"] = m.randStr();
    this->_d["log"] = m.randStr();
    this->_d["levels"] = to_string(this->_levels);
    this->_d["types"] = "";
    for (string i : this->_types) {
        this->_d["types"] += i + "|||$$|||";
    }
    this->_setupPlots(v);
    this->_feeTable.setTypes(this->_types);

    std::vector<string> vv;
    vv.push_back("uid");
    vv.push_back("licenseNum");
    vv.push_back("type");
    vv.push_back("level");
    vv.push_back("plot");
    vv.push_back("LastInTime");
    vv.push_back("LastOutTime");
    vv.push_back("fee");
    vv.push_back("date");

    db.createTable(this->_d["log"], vv);

    this->_storeData();
};

const vector<string> Park::getPlotsID() {
    if (!this->_threadFinished) this->_t->join();
    std::vector<string> v;
    this->_plotsList.forEach(
        [&](string first, string second) { v.push_back(first); });

    return v;
};

const std::vector<string> Park::getPlotsID(const bool& isOccupied) {
    if (!this->_threadFinished) this->_t->join();
    std::vector<string> v;
    this->_plotsList.forEach([&](string first, string second) {
        if (isOccupied && this->_simpleGet(second, "car") != "null")
            v.push_back(first);
        if (!isOccupied && this->_simpleGet(second, "car") == "null")
            v.push_back(first);
    });
    return v;
};

const std::vector<string> Park::getPlotsID(const int& level) {
    if (!this->_threadFinished) this->_t->join();
    std::vector<string> v;
    this->_plotsList.forEach([&](string first, string second) {
        if (this->_simpleGet(second, "level") == to_string(level))
            v.push_back(first);
    });
    return v;
};

const std::vector<string> Park::getPlotsID(const string& type) {
    if (!this->_threadFinished) this->_t->join();
    std::vector<string> v;
    this->_plotsList.forEach([&](string first, string second) {
        if (this->_simpleGet(second, "type") == type) v.push_back(first);
    });
    return v;
};

const std::vector<string> Park::getPlotsID(const int& level,
                                           const bool& isOccupied) {
    if (!this->_threadFinished) this->_t->join();
    std::vector<string> v;
    this->_plotsList.forEach([&](string first, string second) {
        if (isOccupied && this->_simpleGet(second, "car") != "null" &&
            this->_simpleGet(second, "level") == to_string(level))
            v.push_back(first);
        if (!isOccupied && this->_simpleGet(second, "car") == "null" &&
            this->_simpleGet(second, "level") == to_string(level))
            v.push_back(first);
    });
    return v;
};

const std::vector<string> Park::getPlotsID(const string& type,
                                           const bool& isOccupied) {
    if (!this->_threadFinished) this->_t->join();
    std::vector<string> v;
    this->_plotsList.forEach([&](string first, string second) {
        if (isOccupied && this->_simpleGet(second, "car") != "null" &&
            this->_simpleGet(second, "type") == type)
            v.push_back(first);
        if (!isOccupied && this->_simpleGet(second, "car") == "null" &&
            this->_simpleGet(second, "type") == type)
            v.push_back(first);
    });
    return v;
};

const std::vector<string> Park::getPlotsID(const int& level,
                                           const string& type) {
    if (!this->_threadFinished) this->_t->join();
    std::vector<string> v;
    this->_plotsList.forEach([&](string first, string second) {
        if (this->_simpleGet(second, "level") == to_string(level) &&
            this->_simpleGet(second, "type") == type)
            v.push_back(first);
    });
    return v;
};

const std::vector<string> Park::getPlotsID(const int& level, const string& type,
                                           const bool& isOccupied) {
    if (!this->_threadFinished) this->_t->join();
    std::vector<string> v;
    this->_plotsList.forEach([&](string first, string second) {
        if (isOccupied && this->_simpleGet(second, "car") != "null" &&
            this->_simpleGet(second, "level") == to_string(level) &&
            this->_simpleGet(second, "type") == type)
            v.push_back(first);
        if (!isOccupied && this->_simpleGet(second, "car") == "null" &&
            this->_simpleGet(second, "level") == to_string(level) &&
            this->_simpleGet(second, "type") == type)
            v.push_back(first);
    });
    return v;
};

Plot Park::getPlot(const string& id) {
    if (!this->_threadFinished) this->_t->join();

    if (this->_plotsList[id] == "undefined") {
        return Plot();
    }
    return Plot(this->_plotsList[id]);
};

Plot Park::getPlotByCar(const string& licenseNum) {
    if (!this->_threadFinished) this->_t->join();

    if (this->_carsList[licenseNum] == "undefined") {
        return Plot();
    }

    return Plot(this->_plotsList[this->_simpleGet(this->_carsList[licenseNum],
                                                  "plot")]);
};

Plot Park::getPlotByCar(Car& car) {
    if (!this->_threadFinished) this->_t->join();

    if (this->_carsList[car.getID()] == "undefined") {
        return Plot();
    }

    return Plot(this->_plotsList[this->_simpleGet(this->_carsList[car.getID()],
                                                  "plot")]);
};

const bool Park::newCar(const string& licenseNum, const string& type,
                        const string& plotID, string& msg) {
    if (!this->_threadFinished) this->_t->join();

    if (licenseNum.length() < 1) {
        msg += "Car " + licenseNum + " LicenseNum Illegal!!!";
        return false;
    }

    if (this->_carsList.isExist(licenseNum)) {
        msg += "Car " + licenseNum + " Already in the Park!!";
        return false;
    }

    if (this->isGoodType(type)) {
        msg += "Car " + licenseNum + " Wrong Type!!!";
        return false;
    }

    if (this->_plotsList[plotID] == "undefined") {
        msg += "Car " + licenseNum + " Assigned Plot Not Exist!!!";
        return false;
    }

    Car c(licenseNum, type, plotID);

    this->_carsList[licenseNum] = c.getDataStr();
    this->_plotsList[plotID] =
        this->_simpleUpdate(this->_plotsList[plotID], "car", licenseNum);

    this->_storeData();

    return true;
};

const bool Park::delCar(const string& licenseNum, string& msg) {
    if (!this->_threadFinished) this->_t->join();

    if (!this->_carsList.isExist(licenseNum)) {
        msg += "Car " + licenseNum + " Not In Plot!!!";
        return false;
    }

    Car c(this->_carsList[licenseNum]);

    this->_plotsList[c.getPlot()] =
        this->_simpleUpdate(this->_plotsList[c.getPlot()], "car", "null");
    this->_carsList.clear(licenseNum);

    this->_storeData();

    return true;
}

const std::vector<string> Park::getCarsID() {
    if (!this->_threadFinished) this->_t->join();
    std::vector<string> v;
    this->_carsList.forEach(
        [&](string first, string second) { v.push_back(first); });

    return v;
};

const std::vector<string> Park::getCarsID(const int& level) {
    if (!this->_threadFinished) this->_t->join();

    std::vector<string> v;

    v = this->getPlotsID(level, true);

    for (string& i : v) {
        i = this->_simpleGet(this->_plotsList[i], "car");
    }

    return v;
};

const std::vector<string> Park::getCarsID(const string& type) {
    if (!this->_threadFinished) this->_t->join();

    std::vector<string> v;

    v = this->getPlotsID(type, true);

    for (string& i : v) {
        i = this->_simpleGet(this->_plotsList[i], "car");
    }

    return v;
};

const std::vector<string> Park::getCarsID(const int& level,
                                          const string& type) {
    if (!this->_threadFinished) this->_t->join();

    std::vector<string> v;

    v = this->getPlotsID(level, type, true);

    for (string& i : v) {
        i = this->_simpleGet(this->_plotsList[i], "car");
    }

    return v;
};

const bool Park::updatePlot(Plot& plot, const int& level) {
    if (!this->_threadFinished) this->_t->join();

    if (level < 0 || level > this->_levels) {
        return false;
    }

    this->_plotsList[plot.getID()] = this->_simpleUpdate(
        this->_plotsList[plot.getID()], "level", to_string(level));

    plot.updateLevel(level);

    this->_storeData();

    return true;
}

const bool Park::updatePlot(Plot& plot, const string& type) {
    if (!this->_threadFinished) this->_t->join();

    if (!this->isGoodType(type)) {
        return false;
    }

    this->_plotsList[plot.getID()] =
        this->_simpleUpdate(this->_plotsList[plot.getID()], "type", type);

    plot.updateType(type);

    this->_storeData();

    return true;
}

const bool Park::checkIn(const string& licenseNum, const string& type,
                         string& msg) {
    if (!this->_threadFinished) this->_t->join();

    std::vector<string> v = this->getPlotsID(type, false);

    if (!v.size()) {
        msg += type + " has no more Plots!!";
        return false;
    }

    if (!newCar(licenseNum, type, v[0], msg)) return false;

    return true;
}

const bool Park::checkIn(const string& licenseNum, const string& type,
                         const int& level, string& msg) {
    if (!this->_threadFinished) this->_t->join();

    std::vector<string> v = this->getPlotsID(level, type, false);

    if (!v.size()) {
        msg += type + " on Level " + to_string(level) + " has no more Plots!!";
        return false;
    }

    if (!newCar(licenseNum, type, v[0], msg)) return false;

    return true;
}

const bool Park::checkInByPlotID(const string& licenseNum, const string& type,
                                 const string& plotID, string& msg) {
    if (!this->_threadFinished) this->_t->join();

    if (!newCar(licenseNum, type, plotID, msg)) return false;
    return true;
}

int Park::checkOut(const string& licenseNum) {
    if (!this->_threadFinished) this->_t->join();

    if (!this->_carsList.isExist(licenseNum)) return -1;
    this->_carsList[licenseNum] = this->_simpleUpdate(
        this->_carsList[licenseNum], "LastOutTime", to_string(time(NULL)));

    Car c(this->_carsList[licenseNum]);

    int fee = this->_feeTable.getFee(c.getType(), c.getLastInTime(),
                                     c.getLastOutTime());

    // this->_threadFinished = false;

    // this->_t = new std::thread([&]{

    // this->_threadPointer = true;

    ovo::data d;
    d["uid"] = m.randStr();
    d["licenseNum"] = licenseNum;
    d["type"] = c.getType();
    d["plot"] = c.getPlot();
    d["level"] = this->_simpleGet(this->_plotsList[c.getPlot()], "level");
    d["LastInTime"] = c.getLastInTime();
    d["LastOutTime"] = c.getLastOutTime();
    d["fee"] = to_string(fee);
    d["date"] = this->_getDate();

    db.insertSQL(this->_d["log"], d);

    this->delCar(licenseNum);

    this->_storeData();

    // this->_threadFinished = true;
    //});

    return fee;
}


void Park::_storeData(){

    if (!this->_threadFinished) this->_t->join();

     this->_threadFinished = false;

     this->_t = new std::thread([&]{

        this->_threadPointer = true;
        this->_needStoreData = false;

        this->_d.classify();
        this->_plotsList.classify();
        this->_carsList.classify();
        db.pushData(g_ParkID, this->_d);
        db.pushData(this->_d["plotsList"], this->_plotsList);
        db.pushData(this->_d["carsList"], this->_carsList);

        this->_threadFinished = true;

    });
}

void Park::_getTypes(std::vector<std::map<string, int>>& v) {
    this->_types.clear();  //清空vec
    for (auto i : v) {
        for (auto ii : i) {
            if (find(this->_types.begin(), this->_types.end(), ii.first) ==
                this->_types.end()) {
                this->_types.push_back(ii.first);
            }
        }
    }
};

void Park::_setupPlots(std::vector<std::map<string, int>>& v) {
    for (unsigned int i = 0; i < v.size(); i++) {
        for (auto ii : v[i]) {
            for (int iii = 0; iii < ii.second; iii++) {
                string s = m.randStr();
                this->_plotsList[s] = this->_simplePlot(s, i, ii.first);
                // cout << _simpleGet(_plotsList[s], "type") << endl;
            }
        }
    }
};

const string Park::_simpleGet(const string& s, const string& what) {
    std::vector<string> v;
    S.split(s, v, "$$||$$");

    vector<string>::iterator it = find(v.begin(), v.end(), what);
    if (it != v.end()) return v[distance(v.begin(), it) + 1];
    return string();
}

const string Park::_simpleUpdate(const string& s, const string& what,
                                 const string& to) {
    std::vector<string> v;
    S.split(s, v, "$$||$$");

    vector<string>::iterator it = find(v.begin(), v.end(), what);
    if (it == v.end()) return s;

    v[distance(v.begin(), it) + 1] = to;

    it = find(v.begin(), v.end(), "LastOperateTime");
    if (it != v.end()) v[distance(v.begin(), it) + 1] = to_string(time(NULL));

    string ss = "";
    for (string i : v) {
        ss += i + "$$||$$";
    }

    return ss;
}

const string Park::_getDate() const {
    char now[64];
    time_t tt;
    struct tm* ttime;
    // tt = atol(argv[1]);
    // tt = 1212132599;  //uint
    time(&tt);
    ttime = localtime(&tt);
    strftime(now, 64, "%Y-%m-%d", ttime);
    string s = now;
    return s;
}
