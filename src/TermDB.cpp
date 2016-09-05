#include "TermDB.hpp"

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
