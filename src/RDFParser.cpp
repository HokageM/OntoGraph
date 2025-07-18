#include "../include/ontograph/RDFParser.hpp"
#include <tinyxml2.h>
#include <set>
using namespace tinyxml2;

bool RDFParser::parseRDFXML(const std::string& filename, OntoGraph& graph) {
    graph.clear();
    XMLDocument doc;
    if (doc.LoadFile(filename.c_str()) != XML_SUCCESS) return false;
    
    XMLElement* rdf = doc.RootElement();
    if (!rdf) return false;

    std::set<std::string> nodeNames;
    // First pass: collect all node names (subjects and objects with rdf:about or rdf:resource)
    for (XMLElement* desc = rdf->FirstChildElement(); desc; desc = desc->NextSiblingElement()) {
        const char* subject = desc->Attribute("rdf:about");
        if (!subject) subject = desc->Attribute("about");
        if (subject) nodeNames.insert(subject);
        for (XMLElement* pred = desc->FirstChildElement(); pred; pred = pred->NextSiblingElement()) {
            const char* object = pred->Attribute("rdf:resource");
            if (!object) object = pred->Attribute("resource");
            if (object) nodeNames.insert(object);
        }
    }
    
    // Second pass: build nodes, edges, and attributes
    for (XMLElement* desc = rdf->FirstChildElement(); desc; desc = desc->NextSiblingElement()) {
        const char* subject = desc->Attribute("rdf:about");
        if (!subject) subject = desc->Attribute("about");
        if (!subject) continue;
        graph.addNode(subject);
        for (XMLElement* pred = desc->FirstChildElement(); pred; pred = pred->NextSiblingElement()) {
            std::string predicate = pred->Name();
            const char* object = pred->Attribute("rdf:resource");
            if (!object) object = pred->Attribute("resource");
            if (object) {
                // If object is a node, add edge
                if (nodeNames.count(object)) {
                    graph.addEdge(subject, predicate, object);
                    // If predicate is SubClassOf, add inverse has_child edge
                    if (predicate == "rdfs:subClassOf" || predicate == "SubClassOf") {
                        graph.addEdge(object, "has_child", subject);
                    }
                } else {
                    // Otherwise, treat as attribute
                    graph.addAttribute(subject, predicate, object);
                }
            } else if (pred->GetText()) {
                graph.addAttribute(subject, predicate, pred->GetText());
            }
        }
    }
    return true;
}