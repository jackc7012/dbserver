#include "data_interface.h"
using namespace cwy;

DataBaseImpl::DataBaseImpl()
{
    
}

DataBaseImpl* DataBaseImpl::createInstance()
{
    static DataBaseImpl* ptr = nullptr;
    if (ptr == nullptr) {
        ptr = new DataBaseImpl();
    }
    return ptr;
}

DataBaseImpl::~DataBaseImpl()
{
    CoUninitialize();
}

int DataBaseImpl::initDataBase(const std::string& ip, const std::string& dataBaseName)
{
    dataBaseName_ = dataBaseName;
    HRESULT result =  CoInitialize(NULL);
    if (result != S_OK) {
        return FALSE;
    }
    if (pMyConnect.CreateInstance(__uuidof(Connection)) != 0) {
        return FALSE;
    }
    if (pRecordset.CreateInstance(__uuidof(Recordset)) != 0) {
        return FALSE;
    }
    char connectionString[100] = { 0 };
    sprintf_s(connectionString, 100, "Driver={sql server};server=%s;uid=sa;pwd=chen931125;database=%s;", ip.c_str(), dataBaseName.c_str());
    if (pMyConnect->Open(connectionString, "", "", adModeUnknown) != 0) {
        return FALSE;
    }
    return TRUE;
}

void cwy::DataBaseImpl::selectSql(const std::string& sqlRequest, std::vector<std::vector<std::string>>& result)
{
    try
    {
        pRecordset = pMyConnect->Execute(sqlRequest.c_str(), NULL, adCmdText);
        long recordCount = pRecordset->GetRecordCount();
        for (long i = 0; i < recordCount; ++i) {
            long fieldCount = pRecordset->GetFields()->Count;
            std::vector<std::string> fieldRecord;
            for (long j = 0; j < fieldCount; ++j) {
                _variant_t tmp = pRecordset->GetFields()->GetItem((long)1)->GetValue();
                fieldRecord.emplace_back((std::string)(_bstr_t)&tmp);
            }
            result.emplace_back(fieldRecord);
            pRecordset->MoveNext();
        }
    }
    catch (_com_error e)
    {
        return;
    }
}

void DataBaseImpl::GetId()
{
    /*char sql[100] = { 0 };
    sprintf_s(sql, 100, "select ID from tb_info order by ID desc");
    try
    {
        pRecordset = pMyConnect->Execute(sql, NULL, adCmdText);
        _variant_t id = pRecordset->GetFields()->GetItem((long)0)->GetValue();
        presentId = atoll(((std::string)(_bstr_t)&id).c_str());
    }
    catch (_com_error e)
    {
        logDataBase << "GetId failed descripton :" << (std::string)e.Description();
        logDataBase.PrintlogError(FILE_FORMAT);
    }*/
    return ;
}

int DataBaseImpl::SearchDataBaseLogin(const long long loginID, std::string& name, std::string& ip, char* password, int& loginStatus)
{
    /*int result = 0;
    char sql[100] = { 0 };
    sprintf_s(sql, 100, "select Name, Password, Ip, IsLogin from tb_info where ID = %lld", loginID);
    try
    {
        logDataBase << "sql :" << sql;
        logDataBase.PrintlogDebug(FILE_FORMAT);
        pRecordset = pMyConnect->Execute(sql, NULL, adCmdText);
        _variant_t sqlName = pRecordset->GetFields()->GetItem((long)0)->GetValue();
        _variant_t sqlPassword = pRecordset->GetFields()->GetItem((long)1)->GetValue();
        _variant_t sqlIp = pRecordset->GetFields()->GetItem((long)2)->GetValue();
        _variant_t sqlIsLogin = pRecordset->GetFields()->GetItem((long)3)->GetValue();
        memcpy_s(password, 50, (char*)(_bstr_t)&sqlPassword, strlen((_bstr_t)&sqlPassword) + 1);
        name = (std::string)(_bstr_t)&sqlName;
        ip = (std::string)(_bstr_t)&sqlIp;
        loginStatus = atoi(((std::string)(_bstr_t)&sqlIsLogin).c_str());
    }
    catch (_com_error e)
    {
        logDataBase << "SearchDataBaseLogin failed descripton :" << (std::string)e.Description();
        logDataBase.PrintlogError(FILE_FORMAT);
        result = -1;
    }*/
    return 0;
}

int DataBaseImpl::UpdateLoginStatus(const int type/* = 0*/, const long long loginID/* = -1*/)
{
    /*int result = 0;
    char sql[100] = { 0 };
    if (loginID == -1) {
        sprintf_s(sql, 100, "update tb_info set IsLogin = %d ", type);
    }
    else {
        sprintf_s(sql, 100, "update tb_info set IsLogin = %d where ID = %lld", type, loginID);
    }
    try
    {
        logDataBase << "sql :" << sql;
        logDataBase.PrintlogDebug(FILE_FORMAT);
        pRecordset = pMyConnect->Execute(sql, NULL, adCmdText);
    }
    catch (_com_error e)
    {
        logDataBase << "UpdateLoginStatus " << type << " failed descripton :" << (std::string)e.Description();
        logDataBase.PrintlogError(FILE_FORMAT);
        result = -1;
    }*/
    return 0;
}

long long DataBaseImpl::InsertRegister(const std::string& registerName, const char* password, const std::string ip)
{
    /*long long result = 0;
    char sql[100] = { 0 };
    sprintf_s(sql, 100, "insert into tb_info values(%lld, '%s', '%s', '%s', 0)", ++presentId, registerName.c_str(), password, ip.c_str());
    try
    {
        logDataBase << "sql :" << sql;
        logDataBase.PrintlogDebug(FILE_FORMAT);
        pRecordset = pMyConnect->Execute(sql, NULL, adCmdText);
        result = presentId;
    }
    catch (_com_error e)
    {
        logDataBase << "InsertRegister failed descripton :" << (std::string)e.Description();
        logDataBase.PrintlogError(FILE_FORMAT);
        result = -1;
    }*/
    return 0;
}
