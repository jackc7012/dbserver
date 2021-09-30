#define DLL_EXPORTS
#include "data_base.h"
#include "data_interface.h"
using namespace cwy;

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF", "adoEOF")

DataBase::DataBase()
{
}

DataBase::~DataBase()
{
}

BOOL DataBase::initSqlDataBase(const std::string& ip, const std::string& dataBaseName)
{
    return DataBaseImpl::createInstance()->initDataBase(ip, dataBaseName);
}

std::string DataBase::getName()
{
    return DataBaseImpl::createInstance()->getName();
}

std::vector<std::vector<std::string>> DataBase::selectDbInfo(const std::string& sqlRequest)
{
    std::vector<std::vector<std::string>> result;
    DataBaseImpl::createInstance()->selectSql(sqlRequest, result);
    return result;
}


