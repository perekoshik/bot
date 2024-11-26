// #include "candles.h"

// #include <vector>
// #include <cmath>
// #include <algorithm>
// #include <numeric>
// #include <iostream>
// #include <string>

// // Нормализация значения
// float minimax(float value, const std::vector<float>& data, float min, float max) {
//     auto min_val = *std::min_element(data.begin(), data.end());
//     auto max_val = *std::max_element(data.begin(), data.end());
//     return (max - min) * (value - min_val) / (max_val - min_val) + min;
// }
// #include <vector>
// #include <cmath>
// #include <iostream>

// // Структура для представления свечей
// struct Candle {
//     double open;
//     double high;
//     double low;
//     double close;
//     double volume;
// };

// // Вспомогательные функции для индикаторов (пустые, их нужно реализовать самостоятельно)
// double rsi(const std::vector<Candle>& candles, int period, int currentIndex) {
//     // Реализация RSI
//     return 50.0; // Заглушка
// }

// double roc(const std::vector<Candle>& candles, int period, int currentIndex) {
//     // Реализация ROC
//     return 0.0; // Заглушка
// }

// double cci(const std::vector<Candle>& candles, int period, int currentIndex) {
//     // Реализация CCI
//     return 0.0; // Заглушка
// }

// double minimax(const std::vector<double>& values, int period, int currentIndex) {
//     double minVal = values[currentIndex], maxVal = values[currentIndex];
//     for (int i = std::max(0, currentIndex - period + 1); i <= currentIndex; ++i) {
//         minVal = std::min(minVal, values[i]);
//         maxVal = std::max(maxVal, values[i]);
//     }
//     double value = values[currentIndex];
//     return (value - minVal) / (maxVal - minVal) * 100.0; // Нормализация
// }

// // Функция для определения окна (временного периода анализа)
// bool insideWindow(int index, int startIndex, int stopIndex) {
//     return index >= startIndex && index <= stopIndex;
// }

// // Главная функция алгоритма
// std::pair<int, int> knnBasedStrategy(const std::vector<Candle>& candles, int shortWindow, int longWindow, int kBase, int barThreshold, int startIndex, int stopIndex) {
//     int k = std::sqrt(kBase); // Значение k для kNN
//     int lastSignalIndex = -1; // Индекс последнего сигнала
//     int lastSignalType = 0;   // Тип последнего сигнала (1 = BUY, -1 = SELL)

//     std::vector<double> feature1;
//     std::vector<double> feature2;
//     std::vector<int> directions;

//     // Проходим по свечам
//     for (int i = 0; i < candles.size(); ++i) {
//         // Проверяем окно
//         if (!insideWindow(i, startIndex, stopIndex)) {
//             continue;
//         }

//         // Вычисляем индикаторы
//         double rs = rsi(candles, longWindow, i);
//         double rf = rsi(candles, shortWindow, i);
//         double os = roc(candles, longWindow, i);
//         double of = roc(candles, shortWindow, i);
//         double cs = cci(candles, longWindow, i);
//         double cf = cci(candles, shortWindow, i);

//         // Обработка Volume для minimax
//         std::vector<double> volumes;
//         for (const auto& candle : candles) {
//             volumes.push_back(candle.volume);
//         }
//         double vs = minimax(volumes, longWindow, i);
//         double vf = minimax(volumes, shortWindow, i);

//         // Выбор фич для алгоритма
//         double f1 = (rs + os + cs + vs) / 4.0; // Среднее для фичи 1
//         double f2 = (rf + of + cf + vf) / 4.0; // Среднее для фичи 2

//         // Вычисляем класс (направление движения следующей свечи)
//         int classLabel = 0;
//         if (i > 0) {
//             classLabel = (candles[i].close > candles[i - 1].close) ? 1 : ((candles[i].close < candles[i - 1].close) ? -1 : 0);
//         }

//         // Сохраняем фичи и классы в массивы
//         feature1.push_back(f1);
//         feature2.push_back(f2);
//         directions.push_back(classLabel);

//         // Пропускаем, если недостаточно данных для анализа
//         if (feature1.size() < k) {
//             continue;
//         }

//         // Реализация алгоритма kNN
//         double prediction = 0.0;
//         for (size_t j = 0; j < feature1.size(); ++j) {
//             double distance = std::sqrt(std::pow(f1 - feature1[j], 2) + std::pow(f2 - feature2[j], 2));
//             if (feature1.size() > k) {
//                 feature1.erase(feature1.begin());
//                 feature2.erase(feature2.begin());
//                 directions.erase(directions.begin());
//             }
//             prediction += directions[j];
//         }

//         // Нормализуем prediction
//         prediction = (prediction > 0) ? 1 : ((prediction < 0) ? -1 : 0);

//         // Сохраняем последний сигнал
//         if (prediction != 0) {
//             lastSignalIndex = i;
//             lastSignalType = prediction; // 1 = BUY, -1 = SELL
//         }
//     }

//     // Возвращаем индекс и тип последнего сигнала
//     return {lastSignalIndex, lastSignalType};
// }

// int main() {
//     // Пример свечей
//     std::vector<Candle> candles = {
//         {100, 105, 95, 102, 1000}, {102, 107, 100, 105, 1200}, {105, 110, 103, 109, 1100},
//         {109, 113, 108, 112, 1400}, {112, 115, 110, 114, 1300}, {114, 118, 113, 117, 1500},
//         {117, 121, 116, 120, 1600}, {120, 125, 119, 123, 1700}, {123, 128, 122, 127, 1800}};

//     // Параметры алгоритма
//     int shortWindow = 14;
//     int longWindow = 28;
//     int kBase = 252;
//     int barThreshold = 300;
//     int startIndex = 0; // Начало окна
//     int stopIndex = candles.size() - 1; // Конец окна

//     // Вызываем стратегию
//     auto result = knnBasedStrategy(candles, shortWindow, longWindow, kBase, barThreshold, startIndex, stopIndex);

//     // Вывод результата
//     std::cout << "Индекс последнего сигнала: " << result.first << "\n";
//     std::cout << "Тип последнего сигнала: " << (result.second == 1 ? "BUY" : (result.second == -1 ? "SELL" : "NONE")) << "\n";

//     return 0;
// }

