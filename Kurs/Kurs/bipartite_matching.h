#define BIPARTITE_MATCHING_H

#include <vector>
#include <string>

class BipartiteMatching {
private:
    bool tryKuhn(int leftVertex);

    int leftSize = 0;
    int rightSize = 0;

    std::vector<std::vector<int>> adjacencyList;
    std::vector<int> matchedRight;
    std::vector<bool> used;
public:
    void loadFromFile(const std::string& filename);
    int findMaximumMatching();
    void saveToDotFile(const std::string& filename);
};
