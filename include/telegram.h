#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <string>

void sendTelegramMessage(const std::string& token, const std::string& chat_id, const std::string& message);

#endif
