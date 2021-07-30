#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>

using namespace std;

class InvertedIndex {
public:
    struct IndexItem {
        size_t docid;
        size_t count;
    };

    void Add(const string& document);
    const vector<IndexItem>& Lookup(const string& word) const;

    const string& GetDocument(size_t id) const {
        return docs[id];
    }

    size_t GetDocumentsCount() const {
        return docs.size();
    }

private:
    unordered_map<string, vector<IndexItem>> index;
    vector<string> docs;
};

class Query {
public:
    Query(string query): query(move(query)) {}

    const string& getQuery() const {
        return this->query;
    }

    const string& getResult() const {
        return this->result;
    }

    void setResult(string result) {
        this->result = move(result);
    }

private:
    const string query;
    string result;
};

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input);
    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
    InvertedIndex index;
};
