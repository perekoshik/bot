#include "api.h"
#include "candles.h"
#include "analysis.h"
#include "telegram.h"
#include <iostream>
#include <string>
#include <vector>
#include <jsoncpp/json/json.h>








int main() {
    std::string token = "7576806013:AAEOTX5V2D1gu5LjgNyJcIJgnCeUtrI3KvA";
    std::string chat_id = "683934649";

    while (true) {
        std::vector<std::string> pairs = getAllPairs();

        for (const auto& pair : pairs) {
            std::string url = "https://api.kraken.com/0/public/OHLC?pair=" + pair + "&interval=5";
            std::string jsonData = getDataFromAPI(url);

            std::vector<Candle> candles = parseCandles(jsonData, pair);
            analyzeCoin(pair, candles, token, chat_id);
        }

        sendTelegramMessage(token, chat_id, "Просмотр закончен. Перезапуск...");
    }

    return 0;
}
