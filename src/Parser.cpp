#include "Parser.hpp"

#include <cassert>
#include <fstream>
#include <iostream>

Parser::Parser(const std::string& fileListPath) :
    _fileListPath(fileListPath)
{}

void Parser::parseFileList() {
    std::ifstream file(_fileListPath);
    std::string line;
    while (std::getline(file, line)) {
        _fileList.push_back(line);
    }
    file.close();
    DocID docID = 0;
    for (const auto& docName : _fileList) {
        std::ifstream doc(docName);

        assert(doc.is_open());
        std::cout << "Tokenizing file " << docName << '\n';

        // DocID docID = documentDB.addDocument(file); // TODO
        ++docID;

        std::string token;
        while (doc >> token) {
            Tokens::iterator it = _tokens.find(token);
            if (it == _tokens.end()) {
                _tokens.insert(std::make_pair(token, DocIDs({docID})));
            } else {
                it->second.push_back(docID);
            }
        }
    }
}

void Parser::printTokenTable() {
    std::cout << "Total no. of tokens in the table: " << _tokens.size() << '\n';
    std::cout << "Token   : DocIDs\n";
    for (const auto& row : _tokens) {
        std::cout << row.first << " :";
        std::for_each(row.second.begin(), row.second.end(),
                      [] (const DocID& id) { std::cout << ' ' << id; });
        std::cout << '\n';
    }
}
