#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <string>
#include <unordered_map>
#include <vector>

class Parser {
 public:
    using DocID = unsigned int;
    using Tokens = std::unordered_map<std::string, DocID>;
    void parseFileList();

    Parser(const std::string& fileListPath);

 private:
    std::string                   _fileListPath;
    std::vector<std::string>      _fileList;
    Tokens                        _tokens;
};

#endif // __PARSER_HPP__
