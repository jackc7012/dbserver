#ifndef MY_DATA_BASE_H
#define MY_DATA_BASE_H

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

#pragma warning(disable:4251)

#include <iostream>
#include <sstream>
#include <windows.h>
#include <vector>

typedef std::vector<std::string> DataRecordLine;
typedef std::vector<DataRecordLine> DataRecords;

enum class DLL_API ERRTYPE {
    OK,
    COMMANDINJECTION
};

class DLL_API SqlRequest {
public:
    SqlRequest(const std::string& str);
    SqlRequest();
    ~SqlRequest();
    SqlRequest(const SqlRequest&) = delete;
    SqlRequest(SqlRequest&&) = delete;
    SqlRequest& operator = (const SqlRequest&) = delete;
    SqlRequest& operator = (SqlRequest&&) = delete;

    SqlRequest& operator <<(const std::string& sqlRequest);
    SqlRequest& operator <<(const long long sqlRequest);

    void clear();
    std::string str() const;
    size_t getLength() const;
    std::vector<SqlRequest> split(const char* separator) const;

private:
    std::stringstream str_;
    ERRTYPE errType_{ ERRTYPE::OK };
};

std::string DLL_API toDbString(const std::string& src);

std::string DLL_API dbJoin(const std::vector<long long>& srcList);

std::string DLL_API dbJoin(const std::vector<std::string>& srcList);

class DLL_API DataBase {
public:
    DataBase();
    ~DataBase();

    DataBase(const DataBase&) = delete;
    DataBase(DataBase&&) = delete;
    DataBase& operator = (const DataBase&) = delete;
    DataBase& operator = (DataBase&&) = delete;

    /* 数据库初始化
        * ip:数据库服务器ip
        * dataBaseName:数据库名
        * uid:数据库登录用户名
        * pwd:数据库登录密码
        * return 连接成功与否
        */
    BOOL initSqlDataBase(const std::string& ip, const std::string& dataBaseName, const std::string& uid, const std::string& pwd);

    /* 获取数据库名
        * return 数据库名
        */
    std::string getDbName() const;

    /* 获取数据库服务器ip
        * return 服务器ip
        */
    std::string getServerIp() const;

    /* 获取数据库登录用户名
        * return 服务器登录用户名
        */
    std::string getDbUid() const;

    DataRecords execSql(const SqlRequest& sqlRequest, const char* separator = nullptr);

    /* 查询数据表数据
        * sqlRequest sql请求
        * return 查找结果
        */
    std::vector<std::vector<std::string>> selectDbInfo(const SqlRequest& sqlRequest);

    /* 插入数据表数据
        * sqlRequest sql请求
        * return 插入成功与否
        */
    BOOL insertDbInfo(const SqlRequest& sqlRequest);

    /* 更新数据表数据
        * sqlRequest sql请求
        * return 更新成功与否
        */
    BOOL updateDbInfo(const SqlRequest& sqlRequest);

    /* 删除数据表数据
        * sqlRequest sql请求
        * return 删除成功与否
        */
    BOOL delDbInfo(const SqlRequest& sqlRequest);

    /* 创建数据表
        * sqlRequest sql请求
        * return 创建成功与否
        */
    BOOL createDbInfo(const SqlRequest& sqlRequest);

    /* 删除数据表
        * sqlRequest sql请求
        * return 删除成功与否
        */
    BOOL dropDbInfo(const SqlRequest& sqlRequest);

    /* 数据库反初始化
        * return 反初始化成功与否
        */
    BOOL uninitDataBase();

    /* 获取数据库失败操作信息
        * return 错误信息
        */
    std::string getErrMessage() const;
};

#endif // !MY_DATA_BASE_H
