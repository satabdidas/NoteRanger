#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <string>
#include <vector>

class DocumentDB;
class TermDB;

class Parser {
 public:
    using DocID = unsigned int;
    using DocIDs = std::vector<DocID>;

    void parseFileList(TermDB& termDB, DocumentDB& docDB);

    Parser(const std::string& fileListPath);

 private:
    std::string                   _fileListPath;
    std::vector<std::string>      _fileList;
};

#endif // __PARSER_HPP__
