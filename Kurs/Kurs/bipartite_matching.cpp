#include "bipartite_matching.h"
#include <fstream>
#include <iostream>

void BipartiteMatching::loadFromFile(const std::string& filename) {
    std::ifstream input(filename);
    if (!input) {
        throw std::runtime_error("Error");
    }

    input >> leftSize >> rightSize;

    adjacencyList.assign(leftSize, {});
    matchedRight.assign(rightSize, -1);

    int u, v;
    while (input >> u >> v) {
        adjacencyList[u].push_back(v);
    }
}

bool BipartiteMatching::tryKuhn(int leftVertex) {
    if (used[leftVertex]) {
        return false;
    }

    used[leftVertex] = true;

    for (int rightVertex : adjacencyList[leftVertex]) {
        if (matchedRight[rightVertex] == -1 || tryKuhn(matchedRight[rightVertex])) {
            matchedRight[rightVertex] = leftVertex;
            return true;
        }
    }

    return false;
}

int BipartiteMatching::findMaximumMatching() {
    int matchingSize = 0;

    for (int i = 0; i < leftSize; ++i) {
        used.assign(leftSize, false);
        if (tryKuhn(i)) {
            ++matchingSize;
        }
    }

    return matchingSize;
}

void BipartiteMatching::saveToDotFile(const std::string& filename) {
    std::ofstream output(filename);
    if (!output) {
        throw std::runtime_error("Error");
    }

    output << "graph G {\n";
    output << "  rankdir=LR;\n\n";

    for (int i = 0; i < leftSize; ++i) {
        output << "  L" << i << " [shape=circle];\n";
    }

    for (int i = 0; i < rightSize; ++i) {
        output << "  R" << i << " [shape=box];\n";
    }

    output << "\n";

    for (int rightVertex = 0; rightVertex < rightSize; ++rightVertex) {
        if (matchedRight[rightVertex] != -1) {
            output << "  L" << matchedRight[rightVertex]
                << " -- R" << rightVertex
                << " [color=red, penwidth=2];\n";
        }
    }

    output << "}\n";
}
