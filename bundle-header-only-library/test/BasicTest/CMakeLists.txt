# truth / bundle-header-only-library / test / BasicTest
cmake_minimum_required(VERSION 3.5)


set("BUNDLE" "${PROJECT_NAME}")
set("INCLUDE" "${CMAKE_CURRENT_BINARY_DIR}/bundle.h++")


project("${PROJECT_NAME}-BasicTest" CXX)
add_executable("${PROJECT_NAME}")


add_custom_command(
	OUTPUT	"${INCLUDE}"
	COMMAND	"${BUNDLE}"
		"${CMAKE_CURRENT_LIST_DIR}/include"
		"root.h++"
		"${INCLUDE}"
)


target_compile_definitions(
	"${PROJECT_NAME}"
	PRIVATE
		BUNDLE_INCLUDE="${INCLUDE}"
)


target_sources(
	"${PROJECT_NAME}"
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/BasicTest.c++"

		# Necessary to trigger execution of custom command
		"${INCLUDE}"
)


target_link_libraries(
	"${PROJECT_NAME}"
	PRIVATE
		truth::defaults
)


add_test(NAME "${PROJECT_NAME}" COMMAND "${PROJECT_NAME}")

