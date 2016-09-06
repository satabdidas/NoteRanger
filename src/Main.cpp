#include "Parser.hpp"
#include "DocumentDB.hpp"
#include "TermDB.hpp"

#include <iostream>

void printHelp() {
    std::cout << "noteranger <filelist path>\n";
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printHelp();
        return 1;
    }

    std::cout << "Parsing the file list path "
              << argv[1] << '\n';

    Parser parser(argv[1]);
    DocumentDB docDB;
    TermDB termDB;

    parser.parseFileList(termDB, docDB);

#ifdef NRDEBUG
    termDB.printPostingsTable();
#endif

    termDB.writeIndexToDisk();
    docDB.writeDocInfoToDisk();
    return 0;
}
