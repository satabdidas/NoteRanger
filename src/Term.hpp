#ifndef __TERM_HPP__
#define __TERM_HPP__

#include <unordered_set>

class Term {
public:
    using DocID = unsigned int;
    using PostingList = std::unordered_set<DocID>;

    unsigned int getDF() const;

    void addDocID(DocID docID);

    Term(DocID docID);
private:
    PostingList    _postingList;
};

#endif // __TERM_HPP__
