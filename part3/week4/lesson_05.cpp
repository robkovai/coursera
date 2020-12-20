#include <string>
#include <list>

#include "test_runner.h"

using namespace std;

class Editor {
public:
    using Data = list<char>;
    using Iterator = typename Data::iterator;

    Editor() = default;

    void Left() {
        if (pos != data.begin())
            pos--;
    }

    void Right() {
        if (pos != data.end())
            pos++;
    }

    void Insert(char token) {
        data.insert(pos, token);
    }

    void Cut(size_t tokens = 1) {
        buffer.clear();
        auto nextPos = pos;
        for (size_t i = 0; i < tokens; ++i) {
            if (nextPos == data.end())
                break;
            nextPos++;
        }
        buffer.splice(buffer.begin(), data, pos, nextPos);
        pos = nextPos;
    }

    void Copy(size_t tokens = 1) {
        buffer.clear();
        for (size_t i = 0; i < tokens; ++i) {
            buffer.push_back(*pos++);
            if (pos == data.end())
                break;
        }
    }

    void Paste() {
        for (const auto& token : buffer)
            Insert(token);
    }

    string GetText() const {
        return { data.begin(), data.end() };
    }

private:
    Data data, buffer;
    Iterator pos = data.end();
};

void TypeText(Editor& editor, const string& text) {
    for(char c : text) {
        editor.Insert(c);
    }
}

void TestEditing() {
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
        for(size_t i = 0; i < text_len; ++i) {
            editor.Left();
        }
        editor.Cut(first_part_len);
        for(size_t i = 0; i < text_len - first_part_len; ++i) {
            editor.Right();
        }
        TypeText(editor, ", ");
        editor.Paste();
        editor.Left();
        editor.Left();
        editor.Cut(3);

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse() {
    Editor editor;

    const string text = "esreveR";
    for(char c : text) {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    return 0;
}
