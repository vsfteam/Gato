#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

class Style
{
private:
    std::map<std::string, std::string> styleMap;

public:
    static std::pair<int, std::string> GetLength(std::string value)
    {
        std::regex r("([-+]?[0-9]+)(px|%)?");
        std::smatch m;
        bool found = std::regex_match(value, m, r);

        if (found)
        {
            std::string unit = "px";
            if (m.size() >= 3 && !m.str(2).empty())
            {
                unit = m.str(2);
            }
            if (m.str(0) != "auto")
            {
                return std::pair<int, std::string>(std::stoi(m.str(1)), unit);
            }
        }
        else
        {
            std::cout << "match result:"
                      << "Not Found"
                      << "\n";
        }
    }

    bool MatchLength(std::string value)
    {
        std::regex r("([-+]?[0-9]+)(px|%)?|(auto)");
        return std::regex_match(value, r);
    }
    void Set(std::string key, std::string value)
    {
        if (key == "width" || key == "height")
        {
            if (value == "")
                value = "auto";
            if (!MatchLength(value))
            {
                std::cout << "Format Error!";
                exit(1);
                return;
            }
            if (value != "auto")
            {
                auto pair = GetLength(value);
                if (pair.first < 0)
                {
                    value = "auto";
                }
            }
        }
        else if(key == "display")
        {
            if(!std::regex_match(value, std::regex("block|inline-block")))
            {
                std::cout << "Format Error!";
                exit(1);
                return;
            }
        }
        else if(key == "vertical-align")
        {
            if(!std::regex_match(value, std::regex("top|bottom")))
            {
                std::cout << "Format Error!";
                exit(1);
                return;
            }
        }
        
        styleMap[key] = value;
    }
    std::string Get(std::string key)
    {
        if (styleMap.find(key) != styleMap.end())
        {
            return styleMap[key];
        }
        else
        {
            return "";
        }
    }
};