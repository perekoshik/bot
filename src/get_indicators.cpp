// #include <iostream>
// #include <string>
// #include <curl/curl.h>
// #include <nlohmann/json.hpp>

// using json = nlohmann::json;
// using namespace std;

// // Функция для записи ответа от сервера в строку
// size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
//     ((string*)userp)->append((char*)contents, size * nmemb);
//     return size * nmemb;
// }

// int main() {
//     // Переменные
//     int period_ema_20 = 20;
//     int period_ema_50 = 50;
//     int period_ema_200 = 200;
//     string symbol = "XRP/USDT";
//     string interval = "5m";
//     string secret = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJjbHVlIjoiNjVlMjRhYjkyYzczYzFlM2ZkYTU5M2YyIiwiaWF0IjoxNzMyMjc2ODQxLCJleHAiOjMzMjM2NzQwODQxfQ.G_YJFM2P7T_SAsDtGCA9_UmoxnjrHYAtJqzCwt6wYNA";

//     // Создаем JSON-структуру
//     json payload = {
//         {"secret", secret},
//         {"construct", {
//             {"exchange", "binance"},
//             {"symbol", symbol},
//             {"interval", interval},
//             {"indicators", json::array({
//                 {{"indicator", "rsi"}},
//                 {{"indicator", "ema"}, {"period", period_ema_20}},
//                 {{"indicator", "ema"}, {"period", period_ema_50}},
//                 {{"indicator", "ema"}, {"period", period_ema_200}},
//                 {{"indicator", "macd"}},
//                 {{"indicator", "kdj"}},
//                 {{"indicator", "atr"}}
//             })}
//         }}
//     };

//     // Преобразуем JSON в строку
//     string json_data = payload.dump();

//     CURL *curl;
//     CURLcode res;
//     string readBuffer;

//     // Инициализация cURL
//     curl_global_init(CURL_GLOBAL_DEFAULT);
//     curl = curl_easy_init();

//     if(curl) {
//         const string url = "https://api.taapi.io/bulk";

//         curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
//         curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data.c_str());
//         curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, json_data.length());

//         // Устанавливаем заголовки
//         struct curl_slist *headers = NULL;
//         headers = curl_slist_append(headers, "Content-Type: application/json");
//         curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

//         // Устанавливаем функцию для записи ответа
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

//         // Выполнение запроса
//         res = curl_easy_perform(curl);

//         // Проверка на ошибку
//         if(res != CURLE_OK) {
//             cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
//         } else {
//             cout << "Response: " << readBuffer << endl;
//         }

//         // Очистка ресурсов
//         curl_easy_cleanup(curl);
//     }

//     // Завершаем использование cURL
//     curl_global_cleanup();

//     return 0;
// }
