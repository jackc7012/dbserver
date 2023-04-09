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

enum class DLL_API ERRTYPE
{
    OK,
    COMMANDINJECTION
};

class DLL_API SqlRequest
{
public:
    SqlRequest(const std::string& str);
    SqlRequest();
    ~SqlRequest();
    SqlRequest(const SqlRequest&)               = delete;
    SqlRequest(SqlRequest&&)                    = delete;
    SqlRequest& operator = (const SqlRequest&)  = delete;
    SqlRequest& operator = (SqlRequest&&)       = delete;

    SqlRequest& operator <<(const std::string& sqlRequest);
    SqlRequest& operator <<(const long long sqlRequest);

    void clear();
    std::string str() const;

private:
    std::stringstream str_;
    ERRTYPE errType_{ ERRTYPE::OK };
};

std::string DLL_API toDbString(const std::string& src);

std::string DLL_API dbJoin(const std::vector<long long>& srcList);

std::string DLL_API dbJoin(const std::vector<std::string>& srcList);

class DLL_API DataBase
{
public:
    DataBase();
    ~DataBase();

    DataBase(const DataBase &)                  = delete;
    DataBase(DataBase &&)                       = delete;
    DataBase& operator = (const DataBase &)     = delete;
    DataBase& operator = (DataBase &&)          = delete;

    /* ���ݿ��ʼ��
        * ip:���ݿ������ip
        * dataBaseName:���ݿ���
        * uid:���ݿ��¼�û���
        * pwd:���ݿ��¼����
        * return ���ӳɹ����
        */
    BOOL initSqlDataBase(const std::string& ip, const std::string& dataBaseName, const std::string& uid, const std::string& pwd);

    /* ��ȡ���ݿ���
        * return ���ݿ���
        */
    std::string getDbName() const;

    /* ��ȡ���ݿ������ip
        * return ������ip
        */
    std::string getServerIp() const;

    /* ��ȡ���ݿ��¼�û���
        * return ��������¼�û���
        */
    std::string getDbUid() const;

    /* ��ѯ���ݿ�����
        * sqlRequest sql����
        * return ���ҽ��
        */
    std::vector<std::vector<std::string>> selectDbInfo(const SqlRequest& sqlRequest);

    /* �������ݿ�����
        * sqlRequest sql����
        * return ����ɹ����
        */
    BOOL insertDbInfo(const SqlRequest& sqlRequest);

    /* �������ݿ�����
        * sqlRequest sql����
        * return ���³ɹ����
        */
    BOOL updateDbInfo(const SqlRequest& sqlRequest);

    /* ɾ�����ݿ�����
        * sqlRequest sql����
        * return ɾ���ɹ����
        */
    BOOL delDbInfo(const SqlRequest& sqlRequest);

    /* ɾ�����ݿ�����
        * sqlRequest sql����
        * return ɾ���ɹ����
        */
    BOOL uninitDataBase();
};

#endif // !MY_DATA_BASE_H
