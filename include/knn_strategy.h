#ifndef KNN_STRATEGY_H
#define KNN_STRATEGY_H

#include <vector>
#include "candles.h"

int calculate_signal(const std::vector<Candle>& candles, int short_window, int long_window, int base_k, bool volatility_filter, int bar_threshold);

#endif // KNN_STRATEGY_H
