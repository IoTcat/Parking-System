/*
 * @Author: IoTcat (https://iotcat.me) 
 * @Date: 2019-05-24 17:01:28 
 * @Last Modified by:   IoTcat 
 * @Last Modified time: 2019-05-24 17:01:28 
 */


#ifndef __FEETABLE_H__
#define __FEETABLE_H__

#include <iostream>
#include <string>
#include <vector>
#include "../lib/ovo.h"

const string g_feeTableID = "__Fee_Table__AS4";

using namespace std;

class FeeTable {
   public:
    FeeTable();
    ~FeeTable();

    void setTypes(std::vector<string>& v);
    void set(std::map<string, std::vector<int>>& m);
    int const getFee(const string& type, const string& LastInTime,
                     const string& LastOutTime);
    const string showAll() const;

    inline const std::map<string, std::vector<int>> getTable() const {
        return this->_table;
    };

    inline const std::vector<int> getTable(const string& type) {
        if (this->_table.count(type)) {
            return this->_table[type];
        }
        return std::vector<int>();
    };

   private:
    ovo::data _d, _tableData;
    ovo::db db;
    ovo::String S;
    std::map<string, std::vector<int>> _table;

    const std::vector<int> _classify(std::vector<int>& v) const;
    const string _vecToStr(std::vector<int>& v) const;
    const std::vector<int> _vecFromStr(const string& s);
    void _pushTable();
};

#endif  //__FEETABLE_H__