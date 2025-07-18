#include "../include/ontograph/OntoGraph.hpp"
#include "../include/ontograph/RDFParser.hpp"
#include <iostream>

int main() {
    OntoGraph graph;
    if (!RDFParser::parseRDFXML("/home/mike/projects/Ontology/Ontology.rdf", graph)) {
        std::cerr << "Failed to parse RDF file." << std::endl;
        return 1;
    }

    for(int i = 0; i < 100; i++) {    
    auto dfs_result = graph.dfsExcludePredicate("centrifuging", {"SubClassOf", "rdfs:subClassOf"});
    //std::cout << "\nDFS from 'centrifuge' (excluding SubClassOf):" << std::endl;
    for (const auto& [name, attributes] : dfs_result) {
        //std::cout << "  " << name << std::endl;
        if (!attributes.empty()) {
            //std::cout << "    class: " << name << " has properties: ";
            bool first = true;
            for (const auto& [attr, value] : attributes) {
                //if (!first) std::cout << ", ";
                //std::cout << attr << "=" << value;
                first = false;
            }
            //std::cout << std::endl;
        }
    }
    return 0;
}