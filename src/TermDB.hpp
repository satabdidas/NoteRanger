#ifndef __TERM_DB_HPP__
#define __TERM_DB_HPP__

#include <string>
#include <unordered_map>
#include <unordered_set>

class TermDB {
public:
    using DocID = unsigned int;
    using Postings = std::unordered_map<std::string, std::unordered_set<DocID>>;;

    void addTerm(const std::string& token, DocID docID);
    void printPostingsTable();

private:
    void addToPostings(const std::string& token, DocID docID);

    Postings           _postings;
};

#endif // __TERM_DB_HPP__
