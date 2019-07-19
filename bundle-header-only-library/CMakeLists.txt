# truth / bundle-header-only-library
cmake_minimum_required(VERSION 3.5)


project("truth-bundle-header-only-library" CXX)
add_executable("${PROJECT_NAME}")


target_sources(
	"${PROJECT_NAME}"
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/src/main.c++"
)


target_link_libraries(
	"${PROJECT_NAME}"
	PRIVATE
		truth::defaults
)


add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/test/BasicTest")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/test/TruthTest")

