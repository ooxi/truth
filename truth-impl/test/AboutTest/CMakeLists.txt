# truth / truth / test / AboutTest
cmake_minimum_required(VERSION 3.5)


project("${PROJECT_NAME}-AboutTest" CXX)
add_executable("${PROJECT_NAME}")


target_sources(
	"${PROJECT_NAME}"
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/AboutTest.c++"
)


target_link_libraries(
	"${PROJECT_NAME}"
	PUBLIC
		truth::truth
	PRIVATE
		truth::defaults
)


add_test(NAME "${PROJECT_NAME}" COMMAND "${PROJECT_NAME}")

