#include "Common.h"

#include <unordered_map>
#include <list>
#include <mutex>
#include <iostream>

using namespace std;

class LruCache : public ICache {
public:
    LruCache(shared_ptr<IBooksUnpacker> books_unpacker, const Settings& settings): books_unpacker(move(books_unpacker)), settings(settings) { }

    BookPtr GetBook(const string& book_name) override {
        lock_guard lock(this->data_mutex);

        if (auto book = this->Find(book_name); book)
            return book;

        BookPtr book = this->books_unpacker->UnpackBook(book_name);
        if (book->GetContent().size() > this->settings.max_memory)
            return book;

        while (this->current_memory + book->GetContent().size() > this->settings.max_memory)
            this->EraseLast();

        return this->Push(book);
    }

private:
    BookPtr Push(BookPtr book) {
        this->data.push_back(book);
        this->iterators[book->GetName()] = prev(this->data.end());
        this->current_memory += book->GetContent().size();
        return this->data.back();
    }

    BookPtr RunkUp(list<BookPtr>::iterator data_iterator) {
        auto book = *data_iterator;
        this->data.erase(data_iterator);
        this->data.push_back(book);
        this->iterators[book->GetName()] = prev(this->data.end());
        return book;
    }

    BookPtr Find(const string& book_name) {
        auto it = this->iterators.find(book_name);
        return it != this->iterators.end() ? this->RunkUp(it->second) : nullptr;
    }

    void Erase(list<BookPtr>::iterator data_iterator) {
        for (auto it = this->iterators.begin(); it != this->iterators.end(); ++it) {
            if (it->second != data_iterator)
                continue;
            this->current_memory -= it->second->get()->GetContent().size();
            this->iterators.erase(it);
            this->data.erase(data_iterator);
            return;
        }
    }

    void EraseLast() {
        if (!this->data.empty())
            this->Erase(this->data.begin());
    }

    shared_ptr<IBooksUnpacker> books_unpacker;
    const Settings settings;
    mutex data_mutex;
    list<BookPtr> data;
    unordered_map<string, list<BookPtr>::iterator> iterators;
    size_t current_memory = 0;
};

unique_ptr<ICache> MakeCache(shared_ptr<IBooksUnpacker> books_unpacker, const ICache::Settings& settings) {
    return make_unique<LruCache>(move(books_unpacker), settings);
}
