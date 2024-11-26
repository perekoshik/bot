#include "analysis.h"
#include "indicators.h"
#include "api.h"
#include "telegram.h"
#include <sstream>
#include <iostream>

void analyzeCoin(const std::string& pair, const std::string& token, const std::string& chat_id) {
    std::vector<double> getData;
    try {
        getData = getTaapiData(pair);
        if (getData.empty()) {
            std::cerr << "Error: Empty data received for pair " << pair << std::endl;
            sendTelegramMessage(token, chat_id, "Error: No data available for pair " + pair);
            return;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << " for pair " << pair << std::endl;
        sendTelegramMessage(token, chat_id, "Exception: " + std::string(e.what()) + " for pair " + pair);
        return;
    }

    double average_rsi = 0.0;
    for (int i = 0; i < 5; i++) {
        average_rsi += getData[i];
    }
    average_rsi = average_rsi / 5;
    
    double ema20 = getData[5];
    double ema50 = getData[6];
    double ema200 = getData[7];

    std::cout << pair << "\n";
    std::cout << "EMA20 " << ema20 << "\n";
    std::cout << "EMA50 " << ema50 << "\n";
    std::cout << "EMA200 " << ema200 << "\n";
    std::cout << "RSI " << average_rsi << "\n";

    if (average_rsi <= 42 && ema20 > ema50 && ema20 > ema200 && ema50 > ema200) {
        std::string message = "Пара: " + pair + "\n";
        message += "RSI: " + std::to_string(average_rsi) + "\n";
        message += "EMA 20: " + std::to_string(ema20) + "\n";
        message += "EMA 50: " + std::to_string(ema50) + "\n";
        message += "Покупать\n------------------------\n";

        sendTelegramMessage(token, chat_id, message);
    }
}
