#pragma once

#include <algorithm>
#include <vector>

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

template <typename Container>
auto Head(Container& c, int top) {
    return IteratorRange(begin(c), begin(c) + min<size_t>(max(top, 0), c.size()));
}
