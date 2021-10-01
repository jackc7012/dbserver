#ifndef __DATA_BASE_H__
#define __DATA_BASE_H__

#include <windows.h>
#include <string>
#include <vector>

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF", "adoEOF")

namespace cwy {
    class DataBaseImpl
    {
    public:
        static DataBaseImpl* createInstance();

        ~DataBaseImpl();

        BOOL initDataBase(const std::string& ip, const std::string& dataBaseName);

        void selectSql(const std::string& sqlRequest, std::vector<std::vector<std::string>>& result);

        BOOL insertSql(const std::string& sqlRequest);



        void GetId();

        int SearchDataBaseLogin(const long long loginID, std::string& name, std::string& ip, char* password, int& loginStatus);

        int UpdateLoginStatus(const int type = 0, const long long loginID = -1);

        long long InsertRegister(const std::string& registerName, const char* password, const std::string ip);
        
        std::string getDbName() const {
            return dataBaseName_;
        }

        std::string getServerIp() const {
            return dataBaseIp_;
        }

    private:
        DataBaseImpl();

        DataBaseImpl(const DataBaseImpl&) = delete;
        DataBaseImpl operator=(const DataBaseImpl&) = delete;

    private:
        _ConnectionPtr pMyConnect{ nullptr };
        _RecordsetPtr pRecordset{ nullptr };
        std::string dataBaseName_;
        std::string dataBaseIp_;
    };
}

#endif // !__DATA_BASE_H__