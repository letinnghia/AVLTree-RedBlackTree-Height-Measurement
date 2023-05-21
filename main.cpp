#include "AVLTree.hpp"
#include "RedBlackTree.hpp"
#include <iostream>
#include <random>
#include <vector>
#include <stddef.h>
#include <algorithm>

int main() 
{ 
    AVLTree avlTree;
    RedBlackTree rbTree;
    
    const uint64_t arraySize = 1000000;
    const uint64_t numArrays = 10;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<std::vector<uint64_t>> arrays(numArrays, std::vector<uint64_t>(arraySize));
    std::vector<uint64_t> avlTreeHeights, rbTreeHeights;

    for (uint64_t i = 0; i < numArrays; ++i) 
    {
        for (uint64_t j = 0; j < arraySize; ++j) 
            arrays[i][j] = j;
        
        std::shuffle(arrays[i].begin(), arrays[i].end(), gen);
    }

    for (std::vector<uint64_t> array: arrays) 
    {
        for (uint64_t key: array)
        {
            avlTree.insert(key);
            rbTree.insert(key);
        }

        avlTreeHeights.push_back(avlTree.getHeight());
        rbTreeHeights.push_back(rbTree.getHeight());

        avlTree.clear();
        rbTree.clear();
    }

    for (uint64_t height: avlTreeHeights)
    {
        std::cout << height << " ";
    }

    std::cout << std::endl;

    for (uint64_t height: rbTreeHeights)
    {
        std::cout << height << " ";
    }

    std::cout << std::endl;

    return 0;
}
