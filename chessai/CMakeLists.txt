cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(chessai)

find_package(Torch REQUIRED)
include_directories("../src/elements/" "../src/elements/chess/")
link_directories("../src/elements/" "../src/elements/chess/")
link_libraries( "elements" "chesselements")
add_executable(chessai chessai.cpp)
target_link_libraries(chessai "${TORCH_LIBRARIES}")
set_property(TARGET chessai PROPERTY CXX_STANDARD 14)
# cmake -DCMAKE_PREFIX_PATH=$PWD/../libtorch .