#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct Email {
    using Pointer = unique_ptr<Email>;

    explicit Email() = default;
    explicit Email(string from, string to, string body): from(move(from)), to(move(to)), body(move(body)) { }

    string from;
    string to;
    string body;
};

class Worker {
public:
    using Pointer = unique_ptr<Worker>;

private:
    Worker::Pointer next;

public:
    virtual ~Worker() = default;
    virtual void Process(Email::Pointer email) = 0;
    virtual void Run() {
        // только первому worker-у в пайплайне нужно это имплементировать
        throw logic_error("Unimplemented");
    }

protected:
    // реализации должны вызывать PassOn, чтобы передать объект дальше
    // по цепочке обработчиков
    void PassOn(Email::Pointer email) const {
        if (this->next)
            this->next->Process(move(email));
    }

public:
    void SetNext(Worker::Pointer next) {
        if (this->next)
            this->next->SetNext(move(next));
        else
            this->next = move(next);
    }
};

class Reader : public Worker {
    istream &stream;

public:
    explicit Reader(istream &stream): stream(stream) { }

    void Process(Email::Pointer) override {
        throw logic_error("Unimplemented");
    }

    void Run() override {
        while (true) {
            auto email = make_unique<Email>();
            getline(this->stream, email->from);
            getline(this->stream, email->to);
            getline(this->stream, email->body);
            if (this->stream)
                this->PassOn(move(email));
            else
                break;
        }
    }
};

class Filter : public Worker {
public:
    using Function = function<bool(const Email&)>;

private:
    Function filter;

public:
    explicit Filter(Function filter): filter(move(filter)) { }

    void Process(Email::Pointer email) override {
        if (this->filter(*email))
            this->PassOn(move(email));
    }
};

class Copier : public Worker {
    string recipient;

public:
    explicit Copier(string recipient): recipient(move(recipient)) { }

    void Process(Email::Pointer email) override {
        if (email->to != this->recipient) {
            auto copy = make_unique<Email>(email->from, this->recipient, email->body);
            this->PassOn(move(email));
            this->PassOn(move(copy));
        } else
            this->PassOn(move(email));
    }
};

class Sender : public Worker {
    ostream& stream;

public:
    explicit Sender(ostream& stream): stream(stream) { }

    void Process(Email::Pointer email) override {
        this->stream << email->from << '\n' << email->to << '\n' << email->body << '\n';
        this->PassOn(move(email));
    }
};

// реализуйте класс
class PipelineBuilder {
    Worker::Pointer worker;

public:
    // добавляет в качестве первого обработчика Reader
    explicit PipelineBuilder(istream& in) {
        this->worker = make_unique<Reader>(in);
    }

    // добавляет новый обработчик Filter
    PipelineBuilder& FilterBy(Filter::Function filter) {
        this->worker->SetNext(make_unique<Filter>(move(filter)));
        return *this;
    }

    // добавляет новый обработчик Copier
    PipelineBuilder& CopyTo(string recipient) {
        this->worker->SetNext(make_unique<Copier>(move(recipient)));
        return *this;
    }

    // добавляет новый обработчик Sender
    PipelineBuilder& Send(ostream& out) {
        this->worker->SetNext(make_unique<Sender>(out));
        return *this;
    }

    // возвращает готовую цепочку обработчиков
    Worker::Pointer Build() {
        return move(this->worker);
    }
};

void TestSanity() {
    string input = (
                "erich@example.com\n"
                "richard@example.com\n"
                "Hello there\n"

                "erich@example.com\n"
                "ralph@example.com\n"
                "Are you sure you pressed the right button?\n"

                "ralph@example.com\n"
                "erich@example.com\n"
                "I do not make mistakes of that kind\n"
                );
    istringstream inStream(input);
    ostringstream outStream;

    PipelineBuilder builder(inStream);
    builder.FilterBy([](const Email& email) {
        return email.from == "erich@example.com";
    });
    builder.CopyTo("richard@example.com");
    builder.Send(outStream);
    auto pipeline = builder.Build();

    pipeline->Run();

    string expectedOutput = (
                "erich@example.com\n"
                "richard@example.com\n"
                "Hello there\n"

                "erich@example.com\n"
                "ralph@example.com\n"
                "Are you sure you pressed the right button?\n"

                "erich@example.com\n"
                "richard@example.com\n"
                "Are you sure you pressed the right button?\n"
                );

    ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSanity);
    return 0;
}
