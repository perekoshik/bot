#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "candles.h"
#include <string>

void analyzeCoin(const std::string& pair, const std::string& token, const std::string& chat_id);

void getIndicators();

#endif
