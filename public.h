#ifndef PUBLIC_H
#define PUBLIC_H

#include <string>
#include <sstream>

bool checkSqlValid(const std::string& src)
{
    std::string key[9] = { "%", "/", "union", "|", "&", "^", "#", "/*", "*/" };
    for (int i = 0; i < 9; i++)
    {
        if (src.find(key[i]) != std::string::npos)
        {
            return false;
        }
    }
    return true;
}

bool checkValid(const std::string& src)
{
    std::string key[14] = { "and","*","="," ","%0a","%","/","union","|","&","^" ,"#","/*","*/" };
    for (int i = 0; i < 14; i++)
    {
        if (src.find(key[i]) != std::string::npos)
        {
            return false;
        }
    }
    return true;
}

#endif // !PUBLIC_H
