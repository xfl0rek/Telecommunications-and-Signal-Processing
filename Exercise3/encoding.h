#ifndef ENCODING_H
#define ENCODING_H

#include <vector>
#include <string>

struct branch {
    char letter;

    unsigned freq;

    branch *left, *right;
};

struct compare
{
    bool operator()(branch* a, branch* b)
    {
        return (a->freq > b->freq);
    }
};

class encoding {
    static std::vector<char> sentence;
    static std::vector<int> frequently;

public:
    static bool read(const std::string& nameOfFile);
    static void writeOnConsole();
    static branch * createNode(char, unsigned, branch*, branch*);
    static void generate(branch*, const std::string&);
    static void huffmanTree(std::string);
    static std::string encodingMethod(std::string);
};



#endif //ENCODING_H