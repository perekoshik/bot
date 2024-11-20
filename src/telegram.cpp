#include <telegram.h>
#include <curl/curl.h>
#include <iostream>




void sendTelegramMessage(const std::string& token, const std::string& chat_id, const std::string& message) {
    CURL* curl;
    CURLcode res;
    std::string url = "https://api.telegram.org/bot" + token + "/sendMessage?chat_id=" + chat_id + "&text=" + curl_easy_escape(curl_easy_init(), message.c_str(), message.size());

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
}