#include "DocumentDB.hpp"

#include <functional>

DocumentDB::DocID DocumentDB::addDocument(const std::string& docName) {
    return std::hash<std::string>()(docName);
}
