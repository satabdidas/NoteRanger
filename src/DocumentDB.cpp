#include "DocumentDB.hpp"

#include <fstream>
#include <functional>

DocumentDB::DocID DocumentDB::addDocument(const std::string& docName) {
    DocID id = std::hash<std::string>()(docName);
    _documents.insert(std::make_pair(id, docName));
    return id;
}

void DocumentDB::writeDocInfoToDisk() {
    std::ofstream file("TupleStorage.js");

    file << "var TupleStorage = {\n";
    for (const auto& doc: _documents) {
        file << "    \"" << doc.first << "\": [\""
             << "file\", \""
             << doc.second
             << "\", \"test text\"],\n";
    }
    file << "};\n";
}
