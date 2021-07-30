#pragma once

#include <string_view>
#include <map>
#include <set>
#include <vector>
#include <string>

#include "http_request.h"

class Stats {
public:
    Stats();
    void AddMethod(std::string_view method);
    void AddUri(std::string_view uri);
    const std::map<std::string_view, int>& GetMethodStats() const;
    const std::map<std::string_view, int>& GetUriStats() const;

private:
    void initMethodStats();
    void initUriStats();

    std::map<std::string_view, int> methodStats, uriStats;
};

std::vector<std::string_view> SplitIntoWords(std::string_view line);
HttpRequest ParseRequest(std::string_view line);
