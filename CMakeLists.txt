# truth
cmake_minimum_required(VERSION 3.5)


enable_testing()


add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/bundle-header-only-library")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/defaults")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/truth")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/truth-impl")

