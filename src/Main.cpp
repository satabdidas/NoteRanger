#include "Parser.hpp"
#include "DocumentDB.hpp"
#include "TermDB.hpp"

#include <iostream>

void printHelp() {
    std::cout << "noteranger <filelist path> <output directory path>\n";
}

int main(int argc, char* argv[]) {
    if (argc != 2 && argc != 3) {
        printHelp();
        return 1;
    }

    std::string outDir;
    if (argc == 3) {
        outDir = argv[2];
    }
    std::cout << "Parsing the file list path "
              << argv[1] << '\n';

    Parser parser(argv[1]);
    DocumentDB docDB(outDir);
    TermDB termDB(outDir);

    parser.parseFileList(termDB, docDB);

#ifdef NRDEBUG
    termDB.printPostingsTable();
#endif

    termDB.writeIndexToDisk();
    docDB.writeDocInfoToDisk();
    return 0;
}
