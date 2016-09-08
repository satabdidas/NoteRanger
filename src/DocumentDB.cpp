#include "DocumentDB.hpp"

#include <fstream>
#include <functional>
#include <iostream>

DocumentDB::DocID DocumentDB::addDocument(const std::string& docName,
                                          const std::string& header) {
    DocID id = std::hash<std::string>()(docName);
    _documents.insert(std::make_pair(id, DocumentInfo{docName, header}));
    return id;
}

void DocumentDB::writeDocInfoToDisk() {
    std::ofstream file("TupleStorage.js");

    std::cout << "Writing out TupleStorage.js\n";

    file << "var TupleStorage = {\n";
    for (const auto& doc: _documents) {
        file << "    \"" << doc.first << "\": [\""
             << doc.second._docName
             << "\", \"" << doc.second._docHeader << "\"],\n";
    }
    file << "};\n";
}
