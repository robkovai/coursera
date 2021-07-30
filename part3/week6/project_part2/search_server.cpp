#include "search_server.h"
#include "paginator.h"
#include "profile.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <numeric>

vector<string> SplitIntoWords(const string& line) {
    istringstream words_input(line);
    return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream& document_input) {
    CreateIndex(document_input, index);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
    async_items.push_back(async(&SearchServer::CreateIndex, this, ref(document_input), ref(index)));
}

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output) {
    async_items.push_back(async(&SearchServer::AddQueries, this, ref(query_input), ref(search_results_output), ref(index)));
}

void SearchServer::AddQueries(istream &query_input, ostream &search_results_output, Synchronized<InvertedIndex>& index) {
    vector<Query> queries;

    for (string current_query; getline(query_input, current_query); )
        queries.emplace_back(move(current_query));

    vector<pair<int64_t, size_t>> search_results;//(index.GetAccess().ref_to_value.GetDocumentsCount(), {-1, 0});

    for (auto& query : queries) {
        const auto words = SplitIntoWords(query.getQuery());
        {
            auto access = index.GetAccess();

            search_results.assign(access.ref_to_value.GetDocumentsCount(), {-1, 0});

            for (const auto& word : words) {
                for (const auto& index_item : access.ref_to_value.Lookup(word)) {
                    search_results[index_item.docid].first = index_item.docid;
                    search_results[index_item.docid].second += index_item.count;
                }
            }
        }

        partial_sort(search_results.begin(), Head(search_results, 5).end(), search_results.end(), [](const auto& lhs, const auto& rhs) {
            return make_pair(lhs.second, -lhs.first) > make_pair(rhs.second, -rhs.first);
        });

        ostringstream search_results_output;
        search_results_output << query.getQuery() << ':';
        for (const auto& [docid, count] : Head(search_results, 5)) {
            if (count == 0)
                break;
            search_results_output << " {" << "docid: " << docid << ", " << "hitcount: " << count << '}';
        }
        search_results_output << "\n";
        query.setResult(search_results_output.str());
    }

    for (const auto& query : queries)
        search_results_output << query.getResult();
}

void SearchServer::CreateIndex(istream &document_input, Synchronized<InvertedIndex>& index) {
    InvertedIndex new_index;

    for (string current_document; getline(document_input, current_document); )
        new_index.Add(move(current_document));

    swap(index.GetAccess().ref_to_value, new_index);
}

void InvertedIndex::Add(const string& document) {
    docs.push_back(document);
    auto docid = docs.size() - 1;
    for (const auto& word : SplitIntoWords(document)) {
        auto& index_word = index[word];
        if (!index_word.empty()) {
            if (index_word.back().docid == docid) {
                index_word.back().count++;
                continue;
            }
        }
        index_word.push_back({docid, 1});
    }
}

const vector<InvertedIndex::IndexItem> &InvertedIndex::Lookup(const string &word) const {
    static const vector<InvertedIndex::IndexItem> empty;
    if (auto it = index.find(word); it != index.end())
        return it->second;
    else
        return empty;
}

