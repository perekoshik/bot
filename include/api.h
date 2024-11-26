#ifndef API_H
#define API_H

#include <string>
#include <vector>

std::string getDataFromAPI(const std::string& url);

std::string getDataFrom_Taapi();

std::vector<double> getTaapiData(const std::string& pair);

std::vector<std::string> getAllPairs();

std::vector<std::string> loadPairsFromFile(const std::string& filename);

std::string getTestRSI();

void getIndicators();

#endif
