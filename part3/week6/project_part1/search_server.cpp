#include "search_server.h"
#include "paginator.h"
#include "profile.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <numeric>
#include <future>

vector<string> SplitIntoWords(const string& line) {
    istringstream words_input(line);
    return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream& document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
    InvertedIndex new_index;

    for (string current_document; getline(document_input, current_document); )
        new_index.Add(move(current_document));

    index = move(new_index);
}

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output) {
    vector<Query> queries;

    for (string current_query; getline(query_input, current_query); )
        queries.emplace_back(move(current_query));

    vector<future<void>> futures;
    for (const auto& item : Paginate(queries, max(int(queries.size() / thread::hardware_concurrency()), 1))) {
        futures.push_back(async(std::launch::async, [item, this] {
            vector<pair<int64_t, size_t>> search_results(index.GetDocumentsCount(), {-1, 0});

            for (auto& query : item) {
                const auto words = SplitIntoWords(query.getQuery());

                search_results.assign(index.GetDocumentsCount(), {-1, 0});

                for (const auto& word : words)
                    for (const auto& index_item : index.Lookup(word)) {
                        search_results[index_item.docid].first = index_item.docid;
                        search_results[index_item.docid].second += index_item.count;
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
        }));
    }

    for (auto& future : futures)
        future.get();

    for (const auto& query : queries)
        search_results_output << query.getResult();
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

