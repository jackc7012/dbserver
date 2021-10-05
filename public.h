#ifndef PUBLIC_H
#define PUBLIC_H

#include <string>
#include <sstream>

void trim(std::string& str)
{
    if (!str.empty())
    {
        str.erase(0, str.find_first_not_of(" "));
        str.erase(str.find_last_not_of(" ") + 1);
    }
}

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
