# truth / truth
cmake_minimum_required(VERSION 3.5)


project("truth-truth" CXX)
add_library("${PROJECT_NAME}" INTERFACE)
add_library("truth::truth" ALIAS "${PROJECT_NAME}")


target_include_directories(
	"${PROJECT_NAME}"
	INTERFACE
		"${CMAKE_CURRENT_LIST_DIR}/include"
)

