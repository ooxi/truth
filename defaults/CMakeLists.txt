# truth / defaults
cmake_minimum_required(VERSION 3.5)


project("truth-defaults" CXX)
add_library("${PROJECT_NAME}" INTERFACE)
add_library("truth::defaults" ALIAS "${PROJECT_NAME}")


target_compile_options(
	"${PROJECT_NAME}"
	INTERFACE
		-std=c++2a
		-Wall
		-Wextra
		-Werror
		-pedantic
)

