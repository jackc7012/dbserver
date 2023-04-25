#include "data_interface.h"
using namespace cwy;

DataBaseImpl::DataBaseImpl()
{
}

DataBaseImpl* DataBaseImpl::createInstance()
{
    static DataBaseImpl* ptr = nullptr;
    if (ptr == nullptr)
    {
        ptr = new DataBaseImpl();
    }
    return ptr;
}

DataBaseImpl::~DataBaseImpl()
{
}

BOOL DataBaseImpl::initDataBase(const std::string& ip, const std::string& dataBaseName, const std::string& uid, const std::string& pwd)
{
    dataBaseName_ = dataBaseName;
    dataBaseIp_ = ip;
    dataBaseUid_ = uid;
    HRESULT result = CoInitialize(NULL);
    if (result != S_OK)
    {
        return FALSE;
    }
    if (pMyConnect.CreateInstance(__uuidof(Connection)) != 0)
    {
        return FALSE;
    }
    if (pRecordset.CreateInstance(__uuidof(Recordset)) != 0)
    {
        return FALSE;
    }
    char connectionString[100] = { 0 };
    sprintf_s(connectionString, 100, "Driver={sql server};server=%s;uid=%s;pwd=%s;database=%s;"
        , ip.c_str(), uid.c_str(), pwd.c_str(), dataBaseName.c_str());
    if (pMyConnect->Open(connectionString, "", "", adModeUnknown) != 0)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL DataBaseImpl::uninitDataBase()
{
    try
    {
        pMyConnect->Close();
        pMyConnect.Release();
        CoUninitialize();
    } catch (_com_error e)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL DataBaseImpl::operSql(const DBTYPE dbType, const std::string& sqlRequest)
{
    try
    {
        if (!judgeCommand(dbType, sqlRequest))
        {
            return FALSE;
        }
        pRecordset = pMyConnect->Execute(sqlRequest.c_str(), NULL, adCmdText);
    } catch (_com_error e)
    {
        errMessage_.clear();
        errMessage_ = e.Description();
        return FALSE;
    }
    return TRUE;
}

void DataBaseImpl::selectSql(const std::string& sqlRequest, std::vector<std::vector<std::string>>& result)
{
    try
    {
        if (!judgeCommand(DBTYPE::SEARCH, sqlRequest))
        {
            return;
        }
        pRecordset = pMyConnect->Execute(sqlRequest.c_str(), NULL, adCmdText);
        while (!pRecordset->adoEOF)
        {
            long fieldCount = pRecordset->GetFields()->Count;
            std::vector<std::string> fieldRecord;
            for (long j = 0; j < fieldCount; ++j)
            {
                _variant_t tmp = pRecordset->GetFields()->GetItem((long)j)->GetValue();
                fieldRecord.emplace_back((std::string)(_bstr_t)&tmp);
            }
            result.emplace_back(fieldRecord);
            pRecordset->MoveNext();
        }
    } catch (_com_error e)
    {
        return;
    }
}

BOOL DataBaseImpl::judgeCommand(const DBTYPE dbType, const std::string& command)
{
    switch (dbType)
    {
    case DBTYPE::CREATETABLE: {
        if (command.substr(0, command.find_first_of(' ')) == "create")
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
        break;
    }

    case DBTYPE::DROPTABLE: {
        if (command.substr(0, command.find_first_of(' ')) == "drop")
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
        break;
    }

    case DBTYPE::MODIFY: {
        if (command.substr(0, command.find_first_of(' ')) == "update")
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
        break;
    }

    case DBTYPE::INSERT: {
        if (command.substr(0, command.find_first_of(' ')) == "insert")
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
        break;
    }

    case DBTYPE::DEL: {
        if (command.substr(0, command.find_first_of(' ')) == "delete")
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
        break;
    }

    case DBTYPE::SEARCH: {
        if (command.substr(0, command.find_first_of(' ')) == "select")
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
        break;
    }

    default:
        return FALSE;
    }
    return FALSE;
}
