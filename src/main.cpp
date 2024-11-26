#include "api.h"
#include "candles.h"
#include "analysis.h"
#include "telegram.h"
#include <knn_strategy.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <jsoncpp/json/json.h>


int main() {
    std::string token = "7576806013:AAEOTX5V2D1gu5LjgNyJcIJgnCeUtrI3KvA";
    std::string chat_id = "683934649";
    sendTelegramMessage(token, chat_id, "Начнём...");
    // getIndicators();
    //std::vector <double> arr = getTaapiData("BTC/USDT");
    while (true) {
        std::vector<std::string> pairs = loadPairsFromFile("pairs.txt");

        for (const auto& pair : pairs) {
            // std::cout << pair << std::endl;
            analyzeCoin(pair, token, chat_id);
            std::this_thread::sleep_for(std::chrono::seconds(2));
            // std::string url = "https://api.kraken.com/0/public/OHLC?pair=" + pair + "&interval=5";
            // std::string jsonData = getDataFromAPI(url);

            // std::vector<Candle> candles = parseCandles(jsonData, pair);
            // std::cout<< calculate_signal(candles, 14, 28, 252, false, 252) << " " << pair << std::endl;
            // analyzeCoin(pair, candles, token, chat_id);
            //getTaapiData(pair);
        }

        sendTelegramMessage(token, chat_id, "Просмотр закончен. Перезапуск...");
    }

    return 0;
}
