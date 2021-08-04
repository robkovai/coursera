#include "ini.h"

using namespace std;

namespace Ini {

Section &Document::AddSection(string name) {
    return this->sections[name];
}

const Section &Document::GetSection(const string &name) const {
    return this->sections.at(name);
}

size_t Document::SectionCount() const {
    return this->sections.size();
}

string LoadSectionName(string &input) {
    return input.substr(1, input.size() - 2);
}

pair<string, string> LoadKeyValue(string &input) {
    auto pos = input.find('=');
    return { input.substr(0, pos), input.substr(pos + 1, input.size() - pos - 1) };
}

Document Load(istream &input) {
    Document doc;
    Section *section = nullptr;

    string line;
    while (getline(input, line)) {
        if (line.empty())
            continue;

        if (line[0] == '[')
            section = &doc.AddSection(LoadSectionName(line));
        else {
            if (section)
                section->insert(LoadKeyValue(line));
        }
    }
    return doc;
}

} // Ini
