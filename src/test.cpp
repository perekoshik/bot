// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <algorithm>
// #include <string>

// //int signal = calculate_signal(candles, 14, 28, 252, false, 300);


// struct Candle {
//     double open;
//     double high;
//     double low;
//     double close;
//     double vwap;
//     double volume;
// };

// enum Signal { BUY = 1, SELL = -1, CLEAR = 0 };

// class KNNStrategy {
// public:
//     KNNStrategy(int shortWindow, int longWindow, int baseK)
//         : shortWindow(shortWindow), longWindow(longWindow), k(static_cast<int>(std::sqrt(baseK))) {}

//     void processCandles(const std::vector<Candle>& candles) {
//         for (size_t i = 0; i < candles.size(); ++i) {
//             if (i < longWindow) continue;

//             double rs = rsi(candles, i, longWindow);
//             double rf = rsi(candles, i, shortWindow);
//             double os = roc(candles, i, longWindow);
//             double of = roc(candles, i, shortWindow);

//             double f1 = (rs + os) / 2.0;
//             double f2 = (rf + of) / 2.0;

//             int classLabel = classify(candles, i);

//             features1.push_back(f1);
//             features2.push_back(f2);
//             directions.push_back(classLabel);

//             if (i >= k) {
//                 double prediction = predict(f1, f2);
//                 evaluateSignal(prediction);
//             }
//         }
//     }

//     void printSignals() const {
//         for (const auto& signal : signals) {
//             std::cout << "Signal: " << (signal == BUY ? "BUY" : signal == SELL ? "SELL" : "CLEAR") << "\n";
//         }
//     }

// private:
//     int shortWindow;
//     int longWindow;
//     int k;
//     std::vector<double> features1;
//     std::vector<double> features2;
//     std::vector<int> directions;
//     std::vector<Signal> signals;

//     double rsi(const std::vector<Candle>& candles, size_t index, int period) {
//         double gain = 0.0, loss = 0.0;
//         for (int i = 0; i < period; ++i) {
//             double change = candles[index - i].close - candles[index - i - 1].close;
//             if (change > 0) gain += change;
//             else loss -= change;
//         }
//         if (loss == 0) return 100.0;
//         double rs = gain / loss;
//         return 100.0 - (100.0 / (1.0 + rs));
//     }

//     double roc(const std::vector<Candle>& candles, size_t index, int period) {
//         if (index < period) return 0.0;
//         return ((candles[index].close - candles[index - period].close) / candles[index - period].close) * 100.0;
//     }

//     int classify(const std::vector<Candle>& candles, size_t index) {
//         if (index < 1) return CLEAR;
//         double diff = candles[index].close - candles[index - 1].close;
//         return diff > 0 ? BUY : (diff < 0 ? SELL : CLEAR);
//     }

//     double predict(double f1, double f2) {
//         std::vector<std::pair<double, int>> distances;

//         for (size_t i = 0; i < features1.size(); ++i) {
//             double dist = std::sqrt(std::pow(f1 - features1[i], 2) + std::pow(f2 - features2[i], 2));
//             distances.emplace_back(dist, directions[i]);
//         }

//         std::sort(distances.begin(), distances.end());
//         distances.resize(k);

//         double prediction = 0;
//         for (const auto& [dist, direction] : distances) {
//             prediction += direction;
//         }

//         return prediction;
//     }

//     void evaluateSignal(double prediction) {
//         Signal signal = prediction > 0 ? BUY : (prediction < 0 ? SELL : CLEAR);
//         signals.push_back(signal);
//     }
// };

// // int main() {
// //     std::vector<Candle> candles = {
// //         {1.0, 2.0, 0.5, 1.8, 1.6, 1000},
// //         {1.8, 2.1, 1.7, 2.0, 1.9, 1200},
// //         // Добавьте больше свечей...
// //     };

// //     KNNStrategy strategy(14, 28, 252);
// //     strategy.processCandles(candles);
// //     strategy.printSignals();

// //     return 0;
// // }
