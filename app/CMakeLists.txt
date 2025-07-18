add_executable(ontograph_cli main.cpp)

find_package(tinyxml2 REQUIRED)

target_link_libraries(ontograph_cli PRIVATE tinyxml2::tinyxml2)
target_link_libraries(ontograph_cli PRIVATE ontograph)

target_include_directories(ontograph_cli PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)