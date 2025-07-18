add_library(ontograph
    OntoGraph.cpp
    RDFParser.cpp
)

find_package(tinyxml2 REQUIRED)
target_link_libraries(ontograph PRIVATE tinyxml2::tinyxml2)

target_include_directories(ontograph PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)