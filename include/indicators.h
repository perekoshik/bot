#ifndef INDICATORS_H
#define INDICATORS_H

#include "candles.h"
#include <vector>
#include <utility>

double calculateRMA(const std::vector<Candle>& candles, int period);
double calculateRSI(const std::vector<Candle>& candles, int period);
double calculateATR(const std::vector<Candle>& candles, int period);
std::pair<double, double> calculateMACD(const std::vector<Candle>& candles, int fastPeriod, int slowPeriod, int signalPeriod);
double calculateStochasticOscillator(const std::vector<Candle>& candles, int period);

#endif
