#include "DocumentDB.hpp"

#include <boost/filesystem.hpp>

#include <fstream>
#include <functional>
#include <iostream>

DocumentDB::DocumentDB(const std::string& outDir) :
    _outDir(outDir)
{}

DocumentDB::DocID DocumentDB::addDocument(const std::string& docName,
                                          const std::string& header) {
    DocID id = std::hash<std::string>()(docName);
    _documents.insert(std::make_pair(id, DocumentInfo{docName, header}));
    return id;
}

void DocumentDB::writeDocInfoToDisk() {
    std::string fileName;
    if (_outDir.empty()) {
        fileName = "TupleStorage.js";
    } else {
        boost::filesystem::path filePath(_outDir);
        if (!boost::filesystem::is_directory(filePath)) {
            // NOTE: This throws an exception which is unhandled now
            boost::filesystem::create_directory(filePath);
        }
        fileName = _outDir + "/TupleStorage.js";
    }
    std::ofstream file(fileName, std::ofstream::out);

    std::cout << "Writing out " << fileName << '\n';

    file << "var TupleStorage = {\n";
    for (const auto& doc: _documents) {
        file << "    \"" << doc.first << "\": [\""
             << doc.second._docName
             << "\", \"" << doc.second._docHeader << "\"],\n";
    }
    file << "};\n";
}
