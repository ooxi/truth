# truth / bundle-header-only-library / test / TruthTest
cmake_minimum_required(VERSION 3.5)


set("BUNDLE" "${PROJECT_NAME}")
set("INCLUDE" "${CMAKE_CURRENT_LIST_DIR}/../../../truth/include/truth/Truth.h++")


project("${PROJECT_NAME}-TruthTest" CXX)
add_executable("${PROJECT_NAME}")


# @see https://stackoverflow.com/a/32062884
add_custom_command(
	OUTPUT	"${CMAKE_CURRENT_BINARY_DIR}/always-rebuild"
	COMMAND "${CMAKE_COMMAND}" -E echo
)


add_custom_command(
	OUTPUT	"${INCLUDE}"
	COMMAND	"${BUNDLE}"
		"${CMAKE_CURRENT_LIST_DIR}/../../../truth-impl/include"
		"truth/Truth.h++"
		"${INCLUDE}"
	DEPENDS	"${CMAKE_CURRENT_BINARY_DIR}/always-rebuild"
)


target_compile_definitions(
	"${PROJECT_NAME}"
	PRIVATE
		BUNDLE_INCLUDE="${INCLUDE}"
)


target_sources(
	"${PROJECT_NAME}"
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/TruthTest.c++"

		# Necessary to trigger execution of custom command
		"${INCLUDE}"
)


target_link_libraries(
	"${PROJECT_NAME}"
	PRIVATE
		truth::defaults
)


add_test(NAME "${PROJECT_NAME}" COMMAND "${PROJECT_NAME}")

