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
    DataBaseImpl::createInstance()->uninitDataBase();
}

BOOL DataBase::initSqlDataBase(const std::string& ip, const std::string& dataBaseName, const std::string& uid, const std::string& pwd)
{
    return DataBaseImpl::createInstance()->initDataBase(ip, dataBaseName, uid, pwd);
}

std::string DataBase::getDbName() const
{
    return DataBaseImpl::createInstance()->getDbName();
}

std::string DataBase::getServerIp() const
{
    return DataBaseImpl::createInstance()->getServerIp();
}

std::string DataBase::getDbUid() const
{
    return DataBaseImpl::createInstance()->getDbUid();
}

DataRecords DataBase::execSql(const SqlRequest& sqlRequest, const char* separator/* = nullptr*/)
{
    std::vector<SqlRequest> tmp;
    if (separator != nullptr)
    {
        tmp = sqlRequest.split(separator);
    }
    return DataRecords();
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

BOOL DataBase::createDbInfo(const SqlRequest& sqlRequest)
{
    return DataBaseImpl::createInstance()->operSql(DBTYPE::CREATETABLE, sqlRequest.str());
}

BOOL DataBase::dropDbInfo(const SqlRequest& sqlRequest)
{
    return DataBaseImpl::createInstance()->operSql(DBTYPE::DROPTABLE, sqlRequest.str());
}

BOOL DataBase::uninitDataBase()
{
    return DataBaseImpl::createInstance()->uninitDataBase();
}

std::string DataBase::getErrMessage() const
{
    return DataBaseImpl::createInstance()->getErrMessage();
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
    if (checkSqlValid(sqlRequest))
    {
        str_ << sqlRequest;
    }
    else
    {
        errType_ = ERRTYPE::COMMANDINJECTION;
    }
    return *this;
}

SqlRequest& SqlRequest::operator<<(const long long sqlRequest)
{
    std::string tmp = std::to_string(sqlRequest);
    if (checkSqlValid(tmp))
    {
        str_ << tmp;
    }
    else
    {
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

size_t SqlRequest::getLength() const
{
    return str_.str().length();
}

std::vector<SqlRequest> SqlRequest::split(const char* separator) const
{
    if (separator == nullptr)
    {
        return {};
    }
    std::vector<SqlRequest> result;
    size_t pos = 0;
    while (pos <= getLength())
    {
        size_t pos1 = str_.str().find(separator, pos);
        result.emplace_back(str_.str().substr(pos, pos1));
        pos = pos1 + 1;
    }
    return result;
}

std::string DLL_API toDbString(const std::string& src)
{
    std::ostringstream result;
    if (checkValid(src))
    {
        result << "'" << src << "'";
    }
    return result.str();
}

std::string DLL_API dbJoin(const std::vector<long long>& srcList)
{
    std::string result("(");
    for (const auto& srcStr : srcList)
    {
        std::string src = std::to_string(srcStr);
        if (checkValid(src))
        {
            result += "'" + src + "', ";
        }
    }
    result += ")";
    return result;
}

std::string DLL_API dbJoin(const std::vector<std::string>& srcList)
{
    std::string result("(");
    for (const auto& src : srcList)
    {
        if (checkValid(src))
        {
            result += "'" + src + "', ";
        }
    }
    result = result.substr(0, result.length() - 2);
    result += ")";
    return result;
}
