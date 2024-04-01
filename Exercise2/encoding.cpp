#include "encoding.h"
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <queue>
#include <bits/stdc++.h>

std::vector<char> encoding::sentence;

std::map<char, std::string> dictionary;
std::priority_queue<branch*, std::vector<branch*>, compare> queue;

bool encoding::read(const std::string& nameOfFile) {
    std::ifstream inputFile(nameOfFile);

    if (!inputFile) {
        std::cerr << "Nie można otworzyć pliku." << std::endl;
        return false;
    }

    char character;

    while (inputFile.get(character)) {
        sentence.push_back(character);
    }

    inputFile.close();

    return true;
}

void encoding::writeOnConsole() {
    for(char i : sentence) {
        std::cout << i;
    }
    std::cout << std::endl;
    std::cout << "Wystapienia znakow:" << std::endl;
    for (const auto& pair : dictionary) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

branch * encoding::createNode(char letter, unsigned freq, branch * left, branch * right) {
    auto * newNode = new branch;
    newNode->letter = letter;
    newNode->freq = freq;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

void encoding::generate(branch* root, const std::string& text) {
    if(root == nullptr)
        return;
    if(!root->left && !root->right)
        dictionary[root->letter] = text;

    generate(root->left, text + "0");
    generate(root->right, text + "1");
}

void encoding::huffmanTree(std::string text) {
    std::unordered_map<char, int> freq;
    for(char ch : text) {
        freq[ch]++;
    }
    for(auto it : freq) {
        queue.push(createNode(it.first, it.second, nullptr, nullptr));
    }
    while(queue.size() != 1) {
        branch *left = queue.top();
        queue.pop();
        branch *right = queue.top();
        queue.pop();

        int add = left->freq + right->freq;
        queue.push(createNode('\0', add, left, right));
    }

    generate(queue.top(), "");
}

std::string encoding::encodingMethod(std::string message) {
    std::string encoded_message;
    std::vector<std::vector <char>> pom;
    std::vector<char> pom1;
    std::vector<char> letter;
    for(const auto &it : dictionary) {
        int n = it.second.length();
        char char_array[n+1];
        std::strcpy(char_array, it.second.c_str());
        for(int i = 0; i < n; i++) {
            pom1.push_back(char_array[i]);
        }
        letter.push_back(it.first);
        pom.push_back(pom1);
        pom1.clear();
    }
    bool flag = false;
    for(int i = 0; i <message.size(); i++) {
        for(int j = 0; j < pom.size(); j++) {
            for(int k = 0; k < pom[j].size(); k++) {
                if(message[i] == pom[j][k]) {
                    if(k == pom[j].size() - 1) {
                        encoded_message += letter[j];
                        flag = true;
                        break;
                    }
                    i++;
                } else {
                    i -= k;
                    break;
                }
            }
            if (flag) break;
        }
        flag = false;
    }
    return encoded_message;
}



