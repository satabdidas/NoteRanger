#include "Parser.hpp"

#include "CommonMacros.hpp"
#include "DocumentDB.hpp"
#include "TermDB.hpp"

#include <boost/regex.hpp>

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

        notesAssert(doc.is_open(), docName + " should be open");

        std::string header;
        std::getline(doc, header);
        doc.seekg(0, doc.beg);

        strip(header, "#+(.+)", 1);
        DocID docID = docDB.addDocument(docName, header);
        std::cout << "Tokenizing file " << docName << '\n';

        std::string token;
        while (doc >> token) {
            if (validateToken(token)) {
                termDB.addTerm(token, docID);
            }
        }
        doc.close();
    }
}

bool Parser::validateToken(std::string& token) {
    strip(token, "([#*_\\>`[(]+|[0-9]+.)([a-zA-Z]*)([*_`\\])]*)", 2);
    if (token.empty()) {
        return false;
    }
    return true;
}

void Parser::strip(std::string& token, const std::string& regex, int matchIdx) {
    boost::regex expr{regex};
    boost::smatch what;
    if (boost::regex_search(token, what, expr)) {
        token = what[matchIdx];
    }
}
