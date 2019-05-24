# API

## 后端综述
- 提供四个类，分别是`Park`(停车场控制器), `Plot`(停车位), `Car`(车辆), `FeeTable`(费用计算器)
- 使用**C++14标准**，使用多线程，字符集utf-8
- API设计主要提供方法(函数), 不提供属性

## Park

### 构造
+ `Park()`: 构造一个Park对象
> 本类提供实例化的对象应**全局唯一**，如果重复声明会出现异常  
> 请在程序**启动时**实例化，然后再进行登录等操作(此时会在后台整理数据)

### 初始化相关函数
+ `bool isExist()`: 判断数据库中是否存在Park
+ `void ini(std::vector<std::map<string, int>>& v)`: 若不存在，使用这个函数初始化新Park(第一次登录)
> 请传入一个map的vector。map的键名为停车位种类，键值为个数。vector顺序代表层数，从0层开始。
+ `void updateFeeTable(std::map<string, std::vector<int>>& m)`: 更新费用计算方法。map的键名是种类type, 键值是这个type的计费方式，用vector表示。注意vector从0开始，顺序对应小时，最大为24小时。对应的值是这一小时的计费。**首次运行时，本函数必须在ini()之后调用**。

### 获取车位函数
+ `std::vector<string> getPlotsID()`: 获取全部车位ID
+ `std::vector<string> getPlotsID(const bool isOccupied)`: 获取全部占有/未占有车位ID
+ `std::vector<string> getPlotsID(const int& level)`: 获取某一层的全部车位ID
+ `std::vector<string> getPlotsID(const int& level, const bool isOccupied)`: 获取某一层的已占有/未占有车位ID
+ `std::vector<string> getPlotsID(const string& type)`: 获取某一类型全部车位ID
+ `std::vector<string> getPlotsID(const string& type, const bool isOccupied)`: 获取某一类型占有/未占有车位ID
+ `std::vector<string> getPlotsID(const int& level, const string& type)`: 获取某一层，某一种类全部车位ID
+ `std::vector<string> getPlotsID(const int& level, const string& type, const bool isOccupied)`: 获取某一层，某一种类占有/未占有车位ID
+ `Plot getPlot(const string& id)`: 根据ID获取车位对象
+ `Plot getPlotByCar(const string& licenseNum)`: 根据车牌号获取车位对象
+ `Plot getPlotByCar(const Car& car)`: 根据car对象获取车位对象

> 注：通过牌号等返回的Plot可能不存在，使用前请使用`bool Plot.isExist()`判断

### 获取车函数
+ `std::vector<string> getCarsID()`: 获取全部停车场中的车牌号
+ `std::vector<string> getCarsID(const int& level)`: 获取某一层的全部车牌号
+ `std::vector<string> getCarsID(const string& type)`: 获取某一类型全部车牌号
+ `std::vector<string> getCarsID(const int& level, const string& type)`: 获取某一层，某一种类全部车牌号
+ `Car getCar(const string& licenseNum)`: 根据车牌号获取车对象
+ `Car getCarByPlot(const string& id)`: 根据plot的id获取车对象
+ `Car getCarByPlot(const Plot& plot)`: 根据plot对象获取车对象

### 功能函数
+ `bool checkIn(const string& licenseNum, const string& type, string& errMsg)`: 本函数适用于车进入停车场时登记。成功返回true，失败(车位已满)返回false。失败信息将追加到errMsg中。**所有errMsg参数均可不填**。
+ `bool checkIn(const string& licenseNum, const string& type, const int& level, string& errMsg)`: 指定层数登记。成功返回true，失败返回false。错误信息追加到errMsg。
+ `bool checkInByPlotID(const string& licenseNum, const string& type, const string& plotID, string& errMsg)`: 指定plotID登记，失败信息追加errMsg。
+ `int checkOut(const string& licenseNum)`: 车出停车场时结算，输出整数金额。**异常则返回-1**。

### 更改设置函数
+ `void updatePlot(const Plot& plot, const int& level)`: 更改plot的level
+ `void updatePlot(const Plot& plot, const string& type)`: 更改plot的种类

### 读取日志
> 当车checkOut时，记录会被自动记入日志  
> 日志返回数据使用ovo::data类型，类似map<string, string>。详见[这里](https://github.com/eeeneko/ovo/tree/master/docs/ovo_data)
+ `std::vector<ovo::data> getLog()`: 获取**全部记录**
+ `std::vector<ovo::data> getLogByDate(const string& date)`: 根据**日期**获取记录，格式`2019-05-24`
+ `std::vector<ovo::data> getLogByCarID(const string& licenseNum)`: 根据**车牌号**获取记录
+ `std::vector<ovo::data> getLogByType(const string& type)`: 根据**车类型**获取记录
+ `std::vector<ovo::data> getLogByLevel(const int& level)`: 根据**层数**获取记录
+ `std::vector<ovo::data> getLogByfee(const int& fee)`: 根据**计费**获取记录
+ `std::vector<ovo::data> getLogByType(const string& type, const string& date)`: 根据**车类型**和**日期**获取记录
+ `std::vector<ovo::data> getLogByLevel(const int& level, const string& date)`: 根据**层数**和**日期**获取记录

## Car

### 函数
+ `bool isExist()`:是否存在
+ `string getID()`: 获取车牌号
+ `string getType()`: 获取种类
+ `string getPlot()`: 获取车位编号
+ `string getID()`: 获取车牌号
+ `string getLastInTime()`: 获取出场时间戳
+ `string getLastOutTime()`: 获取出场时间戳
+ `string showAll()`: JSON格式打印car的所有数据到**字符串**


## Plot

### 函数
+ `bool isExist()`:是否存在
+ `bool isOccupied()`:是否被占有
+ `string getID()`: 获取车位编号
+ `string getType()`: 获取车位种类
+ `int getLevel()`: 获取车位所在层数
+ `string getCar()`: 获取车牌号
+ `string showAll()`: JSON格式打印plot的所有数据到**字符串**



## 时间安排
- 周五下午**5点**提供完整代码。






