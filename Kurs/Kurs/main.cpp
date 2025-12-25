#include "bipartite_matching.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        return 1;
    }

    try {
        BipartiteMatching graph;

        graph.loadFromFile(argv[1]);
        int matchingSize = graph.findMaximumMatching();
        graph.saveToDotFile(argv[2]);

        std::cout << "Maximum matching size: " << matchingSize << std::endl;
    }
    catch (const std::exception& exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
        return 1;
    }

    return 0;
}
