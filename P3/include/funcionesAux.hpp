#ifndef FUNCIONES_AUX_HPP
#define FUNCIONES_AUX_HPP
#include <string>

std::string padWithZeros(const std::string src, const size_t desiredSize);
void removeRedundantZeros(std::string& str);
bool isNumber(const std::string value);

#endif