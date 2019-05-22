# API

## 后端综述
- 提供四个类，分别是`Park`(停车场控制器), `Plot`(停车位), `Car`(车辆), `FeeTable`(费用计算器)
- 使用C++14标准，使用多线程，字符集utf-8
- API设计主要提供方法(函数), 不提供属性

## Park

### 构造
+ `Park()`: 构造一个Park对象
> 本类提供实例化的对象应全局唯一，如果重复声明会出现异常  
> 请在程序启动时实例化，然后再进行登录等操作(此时会在后台整理数据)

### 初始化相关函数
+ `bool isExist()`: 判断数据库中是否存在Park
+ `void ini(std::vector<std::map<string, int>>& v)`: 若不存在，使用这个函数初始化新Park(第一次登录)
> 请传入一个map的vector。map的键名为停车位种类，键值为个数。vector顺序代表层数，从0层开始。
+ `void updateFeeTable(std::map<string, std::vector<int>>& m)`: 更新费用计算方法。map的键名是种类type, 键值是这个type的计费方式，用vector表示。注意vector从0开始，顺序对应小时，最大为24小时。对应的值是这一小时的计费。

### 获取车位函数
+ `std::vector<Plot> getPlots()`: 获取全部车位
+ `std::vector<Plot> getPlots(const bool isOccupied)`: 获取全部占有/未占有车位
+ `std::vector<Plot> getPlots(const int& level)`: 获取某一层的全部车位
+ `std::vector<Plot> getPlots(const int& level, const bool isOccupied)`: 获取某一层的已占有/未占有车位
+ `std::vector<Plot> getPlots(const string& type)`: 获取某一类型全部车位
+ `std::vector<Plot> getPlots(const string& type, const bool isOccupied)`: 获取某一类型占有/未占有车位
+ `std::vector<Plot> getPlots(const int& level, const string& type)`: 获取某一层，某一种类全部车位
+ `std::vector<Plot> getPlots(const int& level, const string& type, const bool isOccupied)`: 获取某一层，某一种类占有/未占有车位
+ `Plot getPlot(const string& licenseNum)`: 根据车牌号获取车位
+ `Plot getPlot(const Car& car)`: 根据car对象获取车位

> 注：通过牌号等返回的Plot可能不存在，使用前请使用`bool Plot.isExist()`判断

### 获取车函数
+ `std::vector<Car> getCars()`: 获取全部停车场中的车
+ `std::vector<Car> getCars(const int& level)`: 获取某一层的全部车
+ `std::vector<Car> getCars(const string& type)`: 获取某一类型全部车
+ `std::vector<Car> getCars(const int& level, const string& type)`: 获取某一层，某一种类全部车位
+ `Car getCar(const string& licenseNum)`: 根据车牌号获取车
+ `Car getCar(const Plot& plot)`: 根据plot对象获取车

### 功能函数
+ `void checkIn(const string& licenseNum, const string& type)`: 本函数适用于车进入停车场时登记。
+ `void checkIn(const string& licenseNum, const string& type, const int& level)`: 指定层数登记。使用前请务必保证对应层数有空车位！
+ `int checkOut(const string& licenseNum)`: 车出停车场时结算，输出整数金额。

### 更改设置函数
+ `void updatePlot(const Plot& plot, const int& level)`: 更改plot的level
+ `void updatePlot(const Plot& plot, const string& type)`: 更改plot的种类

## Car

### 函数
+ `bool isExist()`:是否存在
+ `string getID()`: 获取车牌号
+ `string getType()`: 获取种类
+ `string getPlot()`: 获取车位编号
+ `string getID()`: 获取车牌号


## Plot

### 函数
+ `bool isExist()`:是否存在
+ `bool isOccupied()`:是否被占有
+ `string getID()`: 获取车位编号
+ `string getType()`: 获取车位种类
+ `int getLevel()`: 获取车位所在层数
+ `string getCar()`: 获取车牌号


## 日志功能

- 待定

## 时间安排
- 周五下午提供完整代码。






