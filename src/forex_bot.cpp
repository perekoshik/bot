#include <iostream>
#include <curl/curl.h>
#include <string>
#include <chrono>  // Для замера времени

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    s->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void getPrice() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    auto start = std::chrono::high_resolution_clock::now(); // Старт замера времени

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.binance.com/api/v3/ticker/price?symbol=BTCUSDT");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        auto end = std::chrono::high_resolution_clock::now(); // Конец замера времени
        std::chrono::duration<double> duration = end - start;

        std::cout << "Price data: " << readBuffer << std::endl;
        std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;
    }
}

int main() {
    getPrice();
    return 0;
}
