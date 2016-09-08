#include "TermDB.hpp"

#include <boost/filesystem.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>

TermDB::TermDB(const std::string& outDir) :
    _outDir(outDir)
{}

void TermDB::addToPostings(const std::string& token, DocID docID) {
    Postings::iterator it = _postings.find(token);
    if (it == _postings.end()) {
        _postings.insert(std::make_pair(token, std::unordered_set<DocID>({docID})));
    } else {
        it->second.insert(docID);
    }
}

void TermDB::addTerm(const std::string& token, DocID docID) {
    std::string term = normalize(token);
    addToPostings(term, docID);
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
    std::string fileName;
    if (_outDir.empty()) {
        fileName = "IndexEntries.js";
    } else {
        boost::filesystem::path filePath(_outDir);
        if (!boost::filesystem::is_directory(filePath)) {
            // NOTE: This throws an exception which is unhandled now
            boost::filesystem::create_directory(filePath);
        }
        fileName = _outDir + "/IndexEntries.js";
    }
    std::ofstream file(fileName, std::ofstream::out);

    std::cout << "Writing out " << fileName << '\n';

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

std::string TermDB::normalize(const std::string& token) {
    std::string normalizedTerm(token);
    std::transform(normalizedTerm.begin(), normalizedTerm.end(), normalizedTerm.begin(), ::tolower);
    return normalizedTerm;
}
