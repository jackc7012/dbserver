#ifndef __DATA_BASE_H__
#define __DATA_BASE_H__

#include <windows.h>
#include <string>
#include <vector>

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF", "adoEOF")

enum class DBTYPE {
    INSERT,
    DEL,
    MODIFY,
    SEARCH
};

namespace cwy {
    class DataBaseImpl
    {
    public:
        static DataBaseImpl* createInstance();

        ~DataBaseImpl();

        BOOL initDataBase(const std::string& ip, const std::string& dataBaseName);

        BOOL operSql(const DBTYPE dbType, const std::string& sqlRequest);

        void selectSql(const std::string& sqlRequest, std::vector<std::vector<std::string>>& result);

        std::string getDbName() const {
            return dataBaseName_;
        }

        std::string getServerIp() const {
            return dataBaseIp_;
        }

    private:
        BOOL judgeCommand(const DBTYPE dbType, const std::string& command);

    private:
        DataBaseImpl();

        DataBaseImpl(const DataBaseImpl&) = delete;
        DataBaseImpl(const DataBaseImpl&&) = delete;
        DataBaseImpl operator=(const DataBaseImpl&) = delete;
        DataBaseImpl operator=(const DataBaseImpl&&) = delete;

    private:
        _ConnectionPtr pMyConnect{ nullptr };
        _RecordsetPtr pRecordset{ nullptr };
        std::string dataBaseName_;
        std::string dataBaseIp_;
    };
}

#endif // !__DATA_BASE_H__