#include <fstream>
#include <iostream>
#include <string>
#include <simplexer.hpp>


namespace slm = Simplexer::Math;


struct ProgramOptions {
    std::string filepath;

    ProgramOptions(void) noexcept :
        filepath("")
    {}

    ProgramOptions(int argc, char **argv) {
        if (argc < 2) {
            throw std::string("No file path supplied");
        }
        filepath = argv[1];
    }
};


int run(ProgramOptions &progopts) {
    std::ifstream filestream(progopts.filepath.c_str());
    slm::Tokenizer tokenizer(&filestream);
    slm::Token token = slm::Token();
    size_t index = 0;
    do {
        try {
            token = tokenizer.next();
        } catch (std::string &error) {
            std::cerr << "!! " << error << std::endl;
            break;
        }
        std::cout << token << std::endl;
        index++;
    } while (!token.isEof() && index < 10);
    return 0;
}


int main(int argc, char **argv) {
    ProgramOptions progopts(argc, argv);
    return run(progopts);
}
