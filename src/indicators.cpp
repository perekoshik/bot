#include <indicators.h>
#include <cmath>
#include <algorithm>

double calculateRMA(const std::vector<Candle>& candles, int period) {
    double multiplier = 2.0 / (period + 1);
    double rma = std::stod(candles[0].close);

    for (size_t i = 1; i < candles.size(); ++i) {
        rma = ((rma * (period - 1)) + std::stod(candles[i].close)) / period;
    }

    return rma;
}

double calculateEMA(const std::vector<Candle>& candles, int period) {
    if (candles.empty() || period <= 0) return 0.0;

    double multiplier = 2.0 / (period + 1);
    double ema = std::stod(candles[0].close);

    for (size_t i = 1; i < candles.size(); ++i) {
        double closePrice = std::stod(candles[i].close);
        ema = closePrice * multiplier + ema * (1 - multiplier);
    }

    return ema;
}




double calculateRSI(const std::vector<Candle>& candles, int period) {
    if (candles.size() < static_cast<size_t>(period + 1)) {
        throw std::runtime_error("Not enough data to calculate RSI!");
    }

    double gain = 0.0, loss = 0.0;

    for (size_t i = 1; i <= static_cast<size_t>(period); ++i) {
        double change = std::stod(candles[i].close) - std::stod(candles[i - 1].close);
        if (change > 0) gain += change;
        else loss -= change;
    }

    double avgGain = gain / period;
    double avgLoss = loss / period;

    for (size_t i = period + 1; i < candles.size(); ++i) {
        double change = std::stod(candles[i].close) - std::stod(candles[i - 1].close);

        double currentGain = change > 0 ? change : 0.0;
        double currentLoss = change < 0 ? -change : 0.0;

        avgGain = (avgGain * (period - 1) + currentGain) / period;
        avgLoss = (avgLoss * (period - 1) + currentLoss) / period;
    }

    if (avgLoss == 0) return 100;

    double rs = avgGain / avgLoss;
    double rsi = 100 - (100 / (1 + rs));

    return rsi;
}


double calculateATR(const std::vector<Candle>& candles, int period) {
    double trueRangeSum = 0.0;

    for (size_t i = 1; i < period; ++i) {
        double highLow = std::stod(candles[i].high) - std::stod(candles[i].low);
        double highClose = std::fabs(std::stod(candles[i].high) - std::stod(candles[i-1].close));
        double lowClose = std::fabs(std::stod(candles[i].low) - std::stod(candles[i-1].close));

        double trueRange = std::max({highLow, highClose, lowClose});
        trueRangeSum += trueRange;
    }

    return trueRangeSum / period;
}

std::pair<double, double> calculateMACD(const std::vector<Candle>& candles, int fastPeriod, int slowPeriod, int signalPeriod) {
    double fastEMA = calculateRMA(candles, fastPeriod);
    double slowEMA = calculateRMA(candles, slowPeriod);
    
    double macd = fastEMA - slowEMA;

    std::vector<Candle> macdCandles = candles;
    double signalLine = calculateRMA(macdCandles, signalPeriod);

    return { macd, signalLine };
}

double calculateStochasticOscillator(const std::vector<Candle>& candles, int period) {
    double highestHigh = std::stod(candles[0].high);
    double lowestLow = std::stod(candles[0].low);

    for (size_t i = 1; i < period; ++i) {
        highestHigh = std::max(highestHigh, std::stod(candles[i].high));
        lowestLow = std::min(lowestLow, std::stod(candles[i].low));
    }

    double currentClose = std::stod(candles[period-1].close);

    return ((currentClose - lowestLow) / (highestHigh - lowestLow)) * 100;
}

