#pragma once
#include <string>
#include "OntoGraph.hpp"

class RDFParser {
public:
    static bool parseRDFXML(const std::string& filename, OntoGraph& graph);
};