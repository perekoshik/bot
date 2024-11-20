#include <candles.h>
#include <vector>
#include <jsoncpp/json/json.h>
#include <iostream>

std::vector<Candle> parseCandles(const std::string& jsonData, const std::string& pair) {
    std::vector<Candle> candles;
    Json::Value root;
    Json::Reader reader;

    if (reader.parse(jsonData, root)) {
        const Json::Value& ohlc = root["result"][pair];
        int numCandles = ohlc.size();

        if (numCandles == 0) {
            std::cerr << "No candles returned for pair " << pair << std::endl;
            return candles;
        }

        for (int i = std::max(0, numCandles - 50); i < numCandles; ++i) {
            const Json::Value& candle = ohlc[i];

            Candle c;
            c.open = candle[1].asString();
            c.high = candle[2].asString();
            c.low = candle[3].asString();
            c.close = candle[4].asString();
            c.vwap = candle[5].asString();
            c.volume = candle[6].asString();

            candles.push_back(c);
        }
    } else {
        std::cerr << "Failed to parse JSON response!" << std::endl;
    }

    return candles;
}