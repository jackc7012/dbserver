#define DLL_EXPORTS
#include "public.h"
#include "data_base.h"
#include "data_interface.h"
using namespace cwy;

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

std::string DataBase::getDbName() const
{
    return DataBaseImpl::createInstance()->getDbName();
}

std::string DataBase::getServerIp() const
{
    return DataBaseImpl::createInstance()->getServerIp();
}

std::vector<std::vector<std::string>> DataBase::selectDbInfo(const SqlRequest& sqlRequest)
{
    std::vector<std::vector<std::string>> result;
    DataBaseImpl::createInstance()->selectSql(sqlRequest.str(), result);
    return result;
}

BOOL DataBase::insertDbInfo(const SqlRequest& sqlRequest)
{
    return DataBaseImpl::createInstance()->operSql(DBTYPE::INSERT, sqlRequest.str());
}

BOOL DataBase::updateDbInfo(const SqlRequest& sqlRequest)
{
    return DataBaseImpl::createInstance()->operSql(DBTYPE::MODIFY, sqlRequest.str());
}

BOOL DataBase::delDbInfo(const SqlRequest& sqlRequest)
{
    return DataBaseImpl::createInstance()->operSql(DBTYPE::DEL, sqlRequest.str());
}

SqlRequest::SqlRequest(const std::string& str)
{
    str_ << str;
}

SqlRequest::SqlRequest()
{
    str_.str("");
}

SqlRequest::~SqlRequest()
{
    str_.clear();
}

SqlRequest& SqlRequest::operator<<(const std::string& sqlRequest)
{
    if (checkSqlValid(sqlRequest)) {
        str_ << sqlRequest;
    }
    else {
        errType_ = ERRTYPE::COMMANDINJECTION;
    }
    return *this;
}

SqlRequest& SqlRequest::operator<<(const long long sqlRequest)
{
    std::string tmp = std::to_string(sqlRequest);
    if (checkSqlValid(tmp)) {
        str_ << tmp;
    }
    else {
        errType_ = ERRTYPE::COMMANDINJECTION;
    }
    return *this;
}

void SqlRequest::clear()
{
    str_.str("");
}

std::string SqlRequest::str() const
{
    return str_.str();
}

std::string DLL_API toDbString(const std::string& src)
{
    std::ostringstream result;
    if (checkValid(src)) {
        result << "'" << src << "'";
    }
    return result.str();
}

std::string DLL_API dbJoin(const std::vector<long long>& srcList)
{
    std::ostringstream result('(');
    for (const auto& srcStr : srcList) {
        std::string src = std::to_string(srcStr);
        if (checkValid(src)) {
            result << src << ", ";
        }
    }
    result << ")";
    return result.str();
}

std::string DLL_API dbJoin(const std::vector<std::string>& srcList)
{
    std::ostringstream result('(');
    for (const auto& src : srcList) {
        if (checkValid(src)) {
            result << "'" << src << "', ";
        }
    }
    result << ")";
    return result.str();
}
