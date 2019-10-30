#include "funcionesAux.hpp"
#include <string>

std::string padWithZeros(const std::string src, const size_t desiredSize)
{
    int nZeros = desiredSize - src.length();
    if (nZeros < 0)
        exit(1);
    std::string result = "";
    for (int i = 0; i < nZeros; ++i) {
        result += '0';
    }
    result += src;
    return result;
}

void removeRedundantZeros(std::string& str)
{
    int count = -1;
    for (int i = 0; count < 0 && i < str.length(); ++i) {
        if (str[i] != '0') {
            count = i;
        }
    }

    if (count >= 0)
        str = str.substr(count);
}

bool isNumber(const std::string value)
{
    for (int i = 0; i < value.length(); ++i) {
        if (!isdigit(value[i]))
            return false;
    }
    return true;
}