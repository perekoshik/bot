#include "api.h"
#include "taapi.h"
#include <curl/curl.h>
#include <iostream>
#include <vector>
#include <jsoncpp/json/json.h>
#include <fstream>

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

std::string getDataFrom_Taapi(const std::string& url, const std::string& json_data) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, json_data.length());

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            readBuffer = "Error: Unable to retrieve data.";
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

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

std::vector<std::string> loadPairsFromFile(const std::string& filename) {
    std::vector<std::string> pairs;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            pairs.push_back(line);
        }
    }

    file.close();
    return pairs;
}


std::vector<double> getTaapiData(const std::string& symbol) {
    std::vector <double> indicator_data;
    // double ema20;
    // double ema50;
    // double ema200;
    std::string url = "https://api.taapi.io/bulk";
    //std::string secret = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJjbHVlIjoiNjVlMjRhYjkyYzczYzFlM2ZkYTU5M2YyIiwiaWF0IjoxNzMyMjc2ODQxLCJleHAiOjMzMjM2NzQwODQxfQ.G_YJFM2P7T_SAsDtGCA9_UmoxnjrHYAtJqzCwt6wYNA";
    //std::string secret = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJjbHVlIjoiNjVlMjRhYjkyYzczYzFlM2ZkYTU5M2YyIiwiaWF0IjoxNzMyNTMzMDQxLCJleHAiOjMzMjM2OTk3MDQxfQ.ydoThxeQJm7GohGCqhXdgT7JDTN74StmzK18QtC0lzA";
    std::string secret = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJjbHVlIjoiNjVlMjRhYjkyYzczYzFlM2ZkYTU5M2YyIiwiaWF0IjoxNzMyNTM1MDM3LCJleHAiOjMzMjM2OTk5MDM3fQ.aEwDpz66JvNgyUoG3T44kdcA4lMQckHnb8qt1y1r18w";
    //std::string symbol = "/USDT";
    std::string interval = "5m";

    Json::Value payload;
    payload["secret"] = secret;

    Json::Value construct;
    construct["exchange"] = "bybit";
    construct["symbol"] = symbol;
    construct["interval"] = interval;

    Json::Value indicators(Json::arrayValue);
    Json::Value rsi;
    rsi["indicator"] = "rsi";
    rsi["results"] = 5;
    indicators.append(rsi);

    Json::Value ema_20;
    ema_20["indicator"] = "ema";
    ema_20["period"] = 20;
    indicators.append(ema_20);

    Json::Value ema_50;
    ema_50["indicator"] = "ema";
    ema_50["period"] = 50;
    indicators.append(ema_50);

    Json::Value ema_200;
    ema_200["indicator"] = "ema";
    ema_200["period"] = 200;
    indicators.append(ema_200);

    Json::Value atr;
    atr["indicator"] = "atr";
    indicators.append(atr);

    construct["indicators"] = indicators;

    payload["construct"] = construct;

    Json::StreamWriterBuilder writer;
    std::string json_data = Json::writeString(writer, payload);

    std::string response = getDataFrom_Taapi(url, json_data);
    // std::cout << response << "\n";

    Json::CharReaderBuilder reader;
    Json::Value jsonResponse;
    std::istringstream s(response);
    std::string errs;

    if (!Json::parseFromStream(reader, s, &jsonResponse, &errs)) {
        std::cerr << "Failed to parse JSON response: " << errs << std::endl;
        return {};
    }

    const Json::Value& data = jsonResponse["data"];
    // std::cout << data << std::endl << "------------------------------";
    for (const auto& item : data[0]["result"]["value"]){
        //std::cout << item << " ";
        indicator_data.push_back(item.asDouble());
    }
    indicator_data.push_back(data[1]["result"]["value"].asDouble());
    indicator_data.push_back(data[2]["result"]["value"].asDouble());
    indicator_data.push_back(data[3]["result"]["value"].asDouble());
    // std::cout << data[0]["result"]["value"] << "\n";
    // std::cout << indicator_data[0];
    return indicator_data;
}
