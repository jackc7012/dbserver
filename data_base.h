#ifndef MY_DATA_BASE_H
#define MY_DATA_BASE_H

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

#include <iostream>
#include <windows.h>
#include <vector>

extern "C" {
    class DLL_API DataBase
    {
    public:
        DataBase();

        ~DataBase();

        BOOL initSqlDataBase(const std::string& ip, const std::string& dataBaseName);

        std::string getDbName() const;

        std::string getServerIp() const;

        std::vector<std::vector<std::string>> selectDbInfo(const std::string& sqlRequest);

        BOOL insertDbInfo(const std::string& sqlRequest);

        BOOL updateDbInfo(const std::string& sqlRequest);
    };
}


#endif // !MY_DATA_BASE_H


