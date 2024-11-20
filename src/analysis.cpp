#include "analysis.h"
#include "indicators.h"
#include "telegram.h"
#include <sstream>
#include <iostream>

void analyzeCoin(const std::string& pair, const std::vector<Candle>& candles, const std::string& token, const std::string& chat_id) {
    if (candles.empty()) {
        sendTelegramMessage(token, chat_id, "Error: No candles available for pair " + pair);
        return;
    }

    int period = 14;
    double rsi = 0.0;

    if (candles.size() < static_cast<size_t>(period + 1)) {
        sendTelegramMessage(token, chat_id, "Error: Not enough data to calculate RSI for pair " + pair);
        return;
    }

    try {
        rsi = calculateRSI(candles, period);
    } catch (const std::exception& e) {
        sendTelegramMessage(token, chat_id, "Exception: " + std::string(e.what()));
        return;
    }

    double ema20 = calculateRMA(candles, 20);
    double ema50 = calculateRMA(candles, 50);
    double atr = calculateATR(candles, period);
    auto macd = calculateMACD(candles, 12, 26, 9);
    double stochastic = calculateStochasticOscillator(candles, period);

    if (rsi <= 40 && ema20 > ema50 && stochastic < 80 && atr > 0.001) {
        std::string message = "Пара: " + pair + "\n";
        message += "RSI: " + std::to_string(rsi) + "\n";
        message += "EMA 20: " + std::to_string(ema20) + "\n";
        message += "EMA 50: " + std::to_string(ema50) + "\n";
        message += "ATR: " + std::to_string(atr) + "\n";
        message += "MACD: " + std::to_string(macd.first) + " (MACD), " + std::to_string(macd.second) + " (Signal)\n";
        message += "Stochastic Oscillator: " + std::to_string(stochastic) + "\n";
        message += "Покупать\n------------------------\n";

        sendTelegramMessage(token, chat_id, message);
    }
}