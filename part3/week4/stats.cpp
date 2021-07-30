#include "stats.h"

using namespace std;

const std::set<std::string> SupportedMethods = { "GET", "POST", "PUT", "DELETE" };
const std::set<std::string> SupportedUri = { "/", "/order", "/product", "/basket", "/help" };
const std::string UnknownMethod = "UNKNOWN";
const std::string UnknownUri = "unknown";

Stats::Stats() {
    initMethodStats();
    initUriStats();
}

void Stats::AddMethod(string_view method) {
    methodStats[SupportedMethods.count(string(method)) ? method : UnknownMethod]++;
}

void Stats::AddUri(string_view uri) {
    uriStats[SupportedUri.count(string(uri)) ? uri : UnknownUri]++;
}

const map<string_view, int> &Stats::GetMethodStats() const {
    return methodStats;
}

const map<string_view, int> &Stats::GetUriStats() const {
    return uriStats;
}

void Stats::initMethodStats() {
    for (auto it = SupportedMethods.begin(); it != SupportedMethods.end(); ++it)
        methodStats[*it] = 0;
    methodStats[UnknownMethod] = 0;
}

void Stats::initUriStats() {
    for (auto it = SupportedUri.begin(); it != SupportedUri.end(); ++it)
        uriStats[*it] = 0;
    uriStats[UnknownUri] = 0;
}

vector<string_view> SplitIntoWords(string_view line) {
    vector<string_view> result;

    while (true) {
        size_t space = line.find(' ');
        if (space)
            result.push_back(line.substr(0, space));
        if (space == line.npos)
            break;
        else
            line.remove_prefix(space + 1);
    }
    return result;
}

HttpRequest ParseRequest(string_view line) {
    HttpRequest request;
    const auto values = SplitIntoWords(line);
    if (values.size() >= 3) {
        request.method = values.at(0);
        request.uri = values.at(1);
        request.protocol = values.at(2);
    }
    return request;
}
