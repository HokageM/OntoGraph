#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct Node {
    std::string name;
    std::unordered_map<std::string, std::string> attributes;
};

struct Edge {
    std::string from;
    std::string predicate;
    std::string to;
};

class OntoGraph {
public:
    void addNode(const std::string& name);
    void addAttribute(const std::string& node, const std::string& key, const std::string& value);
    void addEdge(const std::string& from, const std::string& predicate, const std::string& to);

    const std::unordered_map<std::string, Node>& getNodes() const;
    const std::vector<Edge>& getEdges() const;

    void clear();

    std::vector<std::pair<std::string, std::unordered_map<std::string, std::string>>> dfs(const std::string& start) const;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> dfsAttributes(const std::string& start) const;
    std::vector<std::string> getChildren(const std::string& nodeName, const std::string& predicate) const;
    std::vector<std::pair<std::string, std::unordered_map<std::string, std::string>>> dfsByPredicate(const std::string& start, const std::string& predicate) const;
    std::vector<std::pair<std::string, std::unordered_map<std::string, std::string>>> dfsExcludePredicate(const std::string& start, const std::vector<std::string>& excludePredicates) const;
private:
    std::unordered_map<std::string, Node> nodes;
    // Adjacency list: node -> predicate -> list of neighbors
    std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> adjacency;
};
