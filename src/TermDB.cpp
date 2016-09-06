#include "TermDB.hpp"

#include <fstream>
#include <iostream>

void TermDB::addToPostings(const std::string& token, DocID docID) {
    Postings::iterator it = _postings.find(token);
    if (it == _postings.end()) {
        _postings.insert(std::make_pair(token, std::unordered_set<DocID>({docID})));
    } else {
        it->second.insert(docID);
    }
}

void TermDB::addTerm(const std::string& token, DocID docID) {
    addToPostings(token, docID);
}

void TermDB::printPostingsTable() {
    std::cout << "Size of postings table " << _postings.size() << '\n';
    for (const auto& posting : _postings) {
        std::cout << posting.first << " :";
        std::for_each(posting.second.begin(), posting.second.end(),
                      [] (const DocID& id) { std::cout << " " << id; });
        std::cout << '\n';
    }
    std::cout << '\n';
}

void TermDB::writeIndexToDisk() {
    std::ofstream file("IndexEntries.js", std::ofstream::out);

    file << "var IndexEntries={\n";
    for (const auto& posting: _postings) {
        file << "    \"" << posting.first << "\": \n";
        file << "        [";
        std::for_each(posting.second.begin(), posting.second.end(),
                      [&] (const DocID& id) { file << "\"" << id << "\", "; });
        file << "],\n";
    }
    file << "};";
    file.close();
}
