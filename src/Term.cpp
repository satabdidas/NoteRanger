#include "Term.hpp"

Term::Term(DocID docID) :
    _postingList({docID})
{}

void Term::addDocID(DocID docID) {
    _postingList.insert(docID);
}

unsigned int Term::getDF() const {
    return _postingList.size();
}
