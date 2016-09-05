#ifndef __DOCUMENT_DB_HPP__
#define __DOCUMENT_DB_HPP__

#include <string>
#include <unordered_map>

class DocumentDB {
public:
    using DocID = unsigned int;
    using Documents = std::unordered_map<DocID, std::string>;

    DocID addDocument(const std::string& docName);
private:
    Documents     _documents;
};

#endif // __DOCUMENT_DB_HPP__
