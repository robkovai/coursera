#include <map>
#include <string>
#include <vector>
#include <future>

#include "test_runner.h"
#include "profile.h"

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end): it_begin(begin), it_end(end), range_size(distance(it_begin, it_end)) {}

    Iterator begin() const {
        return it_begin;
    }

    Iterator end() const {
        return it_end;
    }

    size_t size() const {
        return range_size;
    }

private:
    Iterator it_begin, it_end;
    size_t range_size;
};

template <typename Iterator>
class Paginator {
public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        for (auto it = begin; distance(it, end) > 0; it = next(it, page_size))
            result.emplace_back(it, next(it, min(page_size, size_t(distance(it, end)))));
    }

    auto begin() const {
        return result.begin();
    }

    auto end() const {
        return result.end();
    }

    size_t size() const {
        return result.size();
    }

private:
    vector<IteratorRange<Iterator>> result;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator(c.begin(), c.end(), page_size);
}

struct Stats {
    map<string, int> word_frequences;

    void operator+=(const Stats& other) {
        for (const auto& item : other.word_frequences)
            word_frequences[item.first] += item.second;
    }
};

Stats ExploreLine(const set<string>& key_words, const string& word) {
    Stats stats;
    if (key_words.count(word))
        stats.word_frequences[word]++;
    return stats;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    vector<string> words;
    string word;
    while (input >> word)
        words.push_back(move(word));

    vector<future<Stats>> futures;
    for (const auto& item : Paginate(words, max(int(words.size() / thread::hardware_concurrency()), 1)))
        futures.push_back(async([item, &key_words] {
            Stats stats;
            for (auto it = item.begin(); it != item.end(); ++it)
                stats += ExploreLine(key_words, *it);
            return stats;
        }));

    Stats result;
    for (auto& future : futures)
        result += future.get();

    return result;
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
        {"yangle", 6},
        {"rocks", 2},
        {"sucks", 1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}
