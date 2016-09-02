#include "Parser.hpp"

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
    parser.parseFileList();

#ifdef NRDEBUG
    parser.printTokenTable();
#endif

    return 0;
}
