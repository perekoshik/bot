#ifndef CANDLES_H
#define CANDLES_H

#include <string>
#include <vector>
#include <jsoncpp/json/json.h>

struct Candle {
    std::string open;
    std::string high;
    std::string low;
    std::string close;
    std::string vwap;
    std::string volume;
};

std::vector<Candle> parseCandles(const std::string& jsonData, const std::string& pair);

#endif
