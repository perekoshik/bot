#ifndef API_H
#define API_H

#include <string>
#include <vector>

std::string getDataFromAPI(const std::string& url);

std::vector<std::string> getAllPairs();

#endif
