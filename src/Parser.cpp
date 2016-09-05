#include "Parser.hpp"

#include "DocumentDB.hpp"
#include "TermDB.hpp"

#include <cassert>
#include <fstream>
#include <iostream>

Parser::Parser(const std::string& fileListPath) :
    _fileListPath(fileListPath)
{}

void Parser::parseFileList(TermDB& termDB, DocumentDB& docDB) {
    std::ifstream file(_fileListPath);
    std::string line;
    while (std::getline(file, line)) {
        _fileList.push_back(line);
    }
    file.close();
    for (const auto& docName : _fileList) {
        std::ifstream doc(docName);

        assert(doc.is_open());
        DocID docID = docDB.addDocument(docName);
        std::cout << "Tokenizing file " << docName << '\n';

        std::string token;
        while (doc >> token) {
            termDB.addTerm(token, docID);
        }
        doc.close();
    }
}
