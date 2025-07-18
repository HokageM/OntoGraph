# OntoGraph

OntoGraph is a C++ tool that converts RDF/XML ontologies into graph structures, enabling traversal and search using standard graph algorithms. It is designed for researchers and developers working with ontologies who need to analyze, traverse, or manipulate ontology data as graphs.

## Features

- **RDF/XML Parsing:** Converts RDF/XML files into an in-memory graph.
- **Graph Representation:** Nodes, edges, and attributes are extracted from ontology data.
- **Graph Algorithms:** Supports depth-first search (DFS), predicate-based traversal, and exclusion of predicates.
- **Attribute Access:** Retrieve node attributes and relationships for advanced analysis.

## Installation

### Prerequisites

- C++20 compatible compiler
- [CMake](https://cmake.org/) >= 3.22
- [Conan](https://conan.io/) (for dependency management)
- [tinyxml2](https://github.com/leethomason/tinyxml2) (handled via Conan)

### Build Steps

1. **Clone the repository:**
   ```bash
   git clone <repo-url>
   cd OntoGraph
   ```

2. **Install dependencies with Conan:**
   ```bash
   conan install . --output-folder=build --build=missing
   ```

3. **Build the project with CMake:**
   ```bash
   cmake -S . -B build
   cmake --build build
   ```

This will produce the `ontograph_cli` executable in the `build/app` directory.

## Usage

### Command-Line Example

Need to be implemented ...
Currently: 
Edit `app/main.cpp` to point to your RDF/XML file and adjust traversal as needed.


### Running the CLI

After building, run:
```bash
./build/app/ontograph_cli
```

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.
