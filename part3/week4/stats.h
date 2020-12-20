#pragma once

#include <string_view>
#include <map>
#include <set>
#include <vector>

#include "http_request.h"

using namespace std;

class Stats {
public:
    Stats();
    void AddMethod(string_view method);
    void AddUri(string_view uri);
    const map<string_view, int>& GetMethodStats() const;
    const map<string_view, int>& GetUriStats() const;

private:
    void initMethodStats();
    void initUriStats();

    const set<string> SupportedMethods = { "GET", "POST", "PUT", "DELETE" };
    const set<string> SupportedUri = { "/", "/order", "/product", "/basket", "/help" };
    const string UnknownMethod = "UNKNOWN";
    const string UnknownUri = "unknown";

    map<string_view, int> methodStats, uriStats;
};

vector<string_view> SplitIntoWords(string_view line);
HttpRequest ParseRequest(string_view line);
