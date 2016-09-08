#ifndef __DOCUMENT_DB_HPP__
#define __DOCUMENT_DB_HPP__

#include <string>
#include <unordered_map>

class DocumentDB {
public:

    struct DocumentInfo {
        std::string _docName;
        std::string _docHeader;
    };

    using DocID = unsigned int;
    using Documents = std::unordered_map<DocID, DocumentInfo>;

    DocID addDocument(const std::string& docName, const std::string& header);
    void writeDocInfoToDisk();
private:
    Documents     _documents;
};

#endif // __DOCUMENT_DB_HPP__
