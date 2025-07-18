#include "../include/ontograph/OntoGraph.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>

// Helper to extract local name from URI or is it already a local name?
static std::string extractLocalName(const std::string& uri) {
    size_t hash = uri.find_last_of('#');
    size_t slash = uri.find_last_of('/');
    size_t pos = std::string::npos;
    if (hash != std::string::npos && hash + 1 < uri.size()) {
        pos = hash + 1;
    } else if (slash != std::string::npos && slash + 1 < uri.size()) {
        pos = slash + 1;
    }
    if (pos != std::string::npos)
        return uri.substr(pos);
    return uri;
}

void OntoGraph::addNode(const std::string& name) {
    std::string local = extractLocalName(name);
    auto it = nodes.find(local);
    if (it == nodes.end()) {
        it = nodes.emplace(local, Node{local, {}}).first;
    }
}

void OntoGraph::addAttribute(const std::string& node, const std::string& key, const std::string& value) {
    nodes[extractLocalName(node)].attributes[extractLocalName(key)] = value;
}

void OntoGraph::addEdge(const std::string& from, const std::string& predicate, const std::string& to) {
    addNode(from);
    addNode(to);
    adjacency[extractLocalName(from)][extractLocalName(predicate)].push_back(extractLocalName(to));
}

const std::unordered_map<std::string, Node>& OntoGraph::getNodes() const {
    return nodes;
}

std::vector<std::pair<std::string, std::unordered_map<std::string, std::string>>> OntoGraph::dfs(const std::string& start) const {
    std::vector<std::pair<std::string, std::unordered_map<std::string, std::string>>> result;
    std::set<std::string> visited;
    std::stack<std::string> stack;
    stack.push(start);
    while (!stack.empty()) {
        std::string node = stack.top();
        stack.pop();
        if (visited.count(node)) continue;
        visited.insert(node);
        auto it = nodes.find(node);
        if (it != nodes.end()) {
            result.emplace_back(node, it->second.attributes);
        } else {
            result.emplace_back(node, std::unordered_map<std::string, std::string>{});
        }
        // Add all adjacent nodes (all predicates)
        auto adjIt = adjacency.find(node);
        if (adjIt != adjacency.end()) {
            for (const auto& predPair : adjIt->second) {
                for (const auto& neighbor : predPair.second) {
                    if (!visited.count(neighbor)) {
                        stack.push(neighbor);
                    }
                }
            }
        }
    }
    return result;
}

std::vector<std::string> OntoGraph::getChildren(const std::string& nodeName, const std::string& predicate) const {
    std::vector<std::string> children;
    auto nodeIt = adjacency.find(nodeName);
    if (nodeIt != adjacency.end()) {
        auto predIt = nodeIt->second.find(predicate);
        if (predIt != nodeIt->second.end()) {
            children = predIt->second;
        }
    }
    return children;
}

std::vector<std::pair<std::string, std::unordered_map<std::string, std::string>>> OntoGraph::dfsByPredicate(const std::string& start, const std::string& predicate) const {
    std::vector<std::pair<std::string, std::unordered_map<std::string, std::string>>> result;
    std::set<std::string> visited;
    std::stack<std::string> stack;
    stack.push(start);
    while (!stack.empty()) {
        std::string node = stack.top();
        stack.pop();
        if (visited.count(node)) continue;
        visited.insert(node);
        auto it = nodes.find(node);
        if (it != nodes.end()) {
            result.emplace_back(node, it->second.attributes);
        } else {
            result.emplace_back(node, std::unordered_map<std::string, std::string>{});
        }
        // Only traverse neighbors with the given predicate
        auto nodeIt = adjacency.find(node);
        if (nodeIt != adjacency.end()) {
            auto predIt = nodeIt->second.find(predicate);
            if (predIt != nodeIt->second.end()) {
                for (const auto& neighbor : predIt->second) {
                    if (!visited.count(neighbor)) {
                        stack.push(neighbor);
                    }
                }
            }
        }
    }
    return result;
}

std::vector<std::pair<std::string, std::unordered_map<std::string, std::string>>> OntoGraph::dfsExcludePredicate(const std::string& start, const std::vector<std::string>& excludePredicates) const {
    std::vector<std::pair<std::string, std::unordered_map<std::string, std::string>>> result;
    std::set<std::string> visited;
    std::stack<std::string> stack;
    stack.push(start);
    auto isExcluded = [&](const std::string& predicate) {
        return std::find(excludePredicates.begin(), excludePredicates.end(), predicate) != excludePredicates.end();
    };
    while (!stack.empty()) {
        std::string node = stack.top();
        stack.pop();
        if (visited.count(node)) continue;
        visited.insert(node);
        auto it = nodes.find(node);
        if (it != nodes.end()) {
            result.emplace_back(node, it->second.attributes);
        } else {
            result.emplace_back(node, std::unordered_map<std::string, std::string>{});
        }
        // Traverse all predicates except excluded
        auto nodeIt = adjacency.find(node);
        if (nodeIt != adjacency.end()) {
            for (const auto& predPair : nodeIt->second) {
                if (isExcluded(predPair.first)) continue;
                for (const auto& neighbor : predPair.second) {
                    if (!visited.count(neighbor)) {
                        stack.push(neighbor);
                    }
                }
            }
        }
    }
    return result;
}

void OntoGraph::clear() {
    nodes.clear();
    adjacency.clear();
}
