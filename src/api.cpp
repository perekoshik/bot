#include "api.h"
#include <curl/curl.h>
#include <iostream>
#include <jsoncpp/json/json.h>


size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string getDataFromAPI(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        res = curl_easy_perform(curl);
        
        if (res != CURLE_OK) {
            std::cerr << "CURL Error: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

std::vector<std::string> getAllPairs() {
    std::string url = "https://api.kraken.com/0/public/AssetPairs";
    std::string jsonData = getDataFromAPI(url);

    std::vector<std::string> pairs;
    Json::Value root;
    Json::Reader reader;

    if (reader.parse(jsonData, root)) {
        const Json::Value& result = root["result"];
        for (const auto& pair : result.getMemberNames()) {
            if (pair.find("USD") != std::string::npos || pair.find("USDT") != std::string::npos) {
                pairs.push_back(pair);
            }
        }
    } else {
        std::cerr << "Failed to parse asset pairs!" << std::endl;
    }

    return pairs;
}