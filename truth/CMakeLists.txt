# truth / truth
cmake_minimum_required(VERSION 3.5)


project("truth-truth" CXX)
add_library("${PROJECT_NAME}" STATIC "")
add_library("truth::truth" ALIAS "${PROJECT_NAME}")


target_sources(
	"${PROJECT_NAME}"
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/src/AssertionError.c++"
		"${CMAKE_CURRENT_LIST_DIR}/src/AssertionErrorFactory.c++"
		"${CMAKE_CURRENT_LIST_DIR}/src/BooleanSubject.c++"
		"${CMAKE_CURRENT_LIST_DIR}/src/Fact.c++"
		"${CMAKE_CURRENT_LIST_DIR}/src/FailureMetadata.c++"
		"${CMAKE_CURRENT_LIST_DIR}/src/FailureStrategy.c++"
		"${CMAKE_CURRENT_LIST_DIR}/src/LazyMessage.c++"
		"${CMAKE_CURRENT_LIST_DIR}/src/SimpleSubjectBuilder.c++"
		"${CMAKE_CURRENT_LIST_DIR}/src/StandardSubjectBuilder.c++"
		"${CMAKE_CURRENT_LIST_DIR}/src/StringSubject.c++"
		"${CMAKE_CURRENT_LIST_DIR}/src/Subject.c++"
		"${CMAKE_CURRENT_LIST_DIR}/src/SubjectFactory.c++"
		"${CMAKE_CURRENT_LIST_DIR}/src/ThrowAssertionErrorFailureStrategy.c++"
		"${CMAKE_CURRENT_LIST_DIR}/src/Truth.c++"
)


target_include_directories(
	"${PROJECT_NAME}"
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}/include"
)


target_link_libraries(
	"${PROJECT_NAME}"
	PRIVATE
		truth::defaults
)


add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/test/AboutTest")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/test/BooleanSubjectTest")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/test/SimpleTest")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/test/StringSubjectTest")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/test/WithMessageTest")

