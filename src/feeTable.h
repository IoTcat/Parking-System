




#ifndef __FEETABLE_H__
#define __FEETABLE_H__

#include <iostream>
#include <vector>
#include <string>
#include "../lib/ovo.h"


const string g_feeTableID = "__Fee_Table__AS4";

using namespace std;

class FeeTable{

public:
    FeeTable(){

        this->_d.clear();
        this->_d = db.getData(g_feeTableID);
        this->_tableData = db.getData(g_feeTableID + "_Table");

        this->_tableData.forEach([&](string first, string second){

            this->_table[first] = this->_vecFromStr(second);
        });
    };


    ~FeeTable(){

        this->_d.classify();
        db.pushData(g_feeTableID, this->_d);
        this->_pushTable();
        db.pushData(g_feeTableID + "_Table", this->_tableData);
    };


    void setTypes(std::vector<string> v){

        std::vector<int> vv;
        vv = this->_classify(vv);

        this->_table.erase(this->_table.begin(), this->_table.end());

        for(auto i : v){

            this->_table[i] = vv;
        }
    }


    void set(std::map<string, std::vector<int>>& m){

        for(auto& i : m){
            if(this->_table.count(i.first)){
                this->_table[i.first].erase(this->_table[i.first].begin(), this->_table[i.first].end());
                this->_table[i.first] = this->_classify(i.second);
            }
        }
    }


    inline std::map<string, std::vector<int>> getTable(){
        return this->_table;
    }

    inline std::vector<int> getTable(const string& type){
        if(this->_table.count(type)){
            return this->_table[type];
        }

        return std::vector<int>();
    }

    int getFee(const string& type, const string& LastInTime, const string& LastOutTime){

        if(!this->_table.count(type)) return -1;

        int t = atoi(LastOutTime.c_str()) - atoi(LastInTime.c_str());

        t /= 3600;

        int days = t / 24;
        int hours = t % 24;

        int fee = 0;

        for(int i = 0; i <= hours; i ++){
            fee += this->_table[type][i];
        }

        int DailyFee = 0;
        for(int i : this->_table[type]){
            DailyFee += i;
        }

        fee += days * DailyFee;

        return fee;
    }


    string showAll(){

        string s = "{\n";

        for(auto i : this->_table){
            s += "  \"" + i.first + "\": [";

            for(auto ii : i.second){
                s += to_string(ii) + ", ";
            }
            s += "],\n";
        }

        s += "}";

        return s;
    }


//private:
    ovo::data _d, _tableData;
    ovo::db db;
    ovo::String S;
    std::map<string, std::vector<int>> _table;

    std::vector<int> _classify(std::vector<int>& v){

        std::vector<int> o;

        if(v.size() < 24){
            for(int i : v){
                o.push_back(i);
            }
            for(int i = 0; i < 24 - v.size(); i ++){
                o.push_back(0);
            }
        }else{
            for(int i = 0; i < 24; i ++){
                o.push_back(v[i]);
            }
        }
        return o;
    }

    string _vecToStr(std::vector<int>& v){

        string s = "";
        for(int i : v){
            s += to_string(i) + "|||$$|||";
        }

        return s;
    }

    std::vector<int> _vecFromStr(const string& s){

        std::vector<string> v;

        S.split(s, v, "|||$$|||");

        std::vector<int> o;

        for(string i : v){
            o.push_back(atoi(i.c_str()));
        }

        return o;
    }

    void _pushTable(){
        this->_tableData.clear();

        for(auto i : this->_table){

            this->_tableData[i.first] = this->_vecToStr(i.second);
        }
    }

};


#endif //__FEETABLE_H__