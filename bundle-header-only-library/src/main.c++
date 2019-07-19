#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <stdexcept>
#include <string>





static void printUsage() {
	std::cerr << "Usage: bundle-header-only-library <resolve-base-directory> <input-root-header-file> <output-file>" << std::endl;
}



/**
 * @param fileAlreadyIncluded Set of already included files which can be skipped
 *     without being included again
 *
 * @warning Assumes all headers have include guards or similar! {@code #if}
 *     directives will not be evaluated
 *
 * @return true iff. the include could be resolved
 */
static bool preprocess(
			std::set<std::filesystem::path>& filesAlreadyIncluded,
			std::filesystem::path const& resolveBaseDirectory,
			std::filesystem::path const& relativeInclude,
			std::ofstream& output
		) {

	if (!relativeInclude.is_relative()) {
		throw std::invalid_argument{"Processing of absolute includes is not supported"};
	}
	std::filesystem::path const absoluteInclude = resolveBaseDirectory / relativeInclude;


	/* If include is not found, it is assumed to be in another include
	 * directory and should not be included in the bundle
	 */
	if (!std::filesystem::exists(absoluteInclude)) {
		return false;
	}


	/* Check whether the include was already processed before. If so, we
	 * tell the caller we did resolve the include without actually emitting
	 * any output
	 */
	if (filesAlreadyIncluded.contains(absoluteInclude)) {
		return true;
	}


	/* Add current include to the set of already resolved includes
	 */
	filesAlreadyIncluded.insert(absoluteInclude);


	/* Read include and echo to output
	 */
	std::ifstream include{absoluteInclude};

	std::size_t lineNumber{1};
	output << "#line " << lineNumber << " " << relativeInclude << "\n";

	for (std::string line; std::getline(include, line); ++lineNumber) {
		std::regex pattern{"^#include <(.+)>$"};
		std::smatch matches;

		/* Did not find another include, line can be forwareded to
		 * output without further processing
		 */
		if (!std::regex_search(line, matches, pattern)) {
			output << line << "\n";
			continue;
		}

		/* Found an include, now we have to try to resolve it
		 */
		std::filesystem::path foundInclude{matches[1].str()};

		bool resolved = preprocess(
			filesAlreadyIncluded,
			resolveBaseDirectory,
			foundInclude,
			output
		);

		/* If the include coundn't be resolved, it has to be emitted
		 * verbatim into the output
		 */
		if (!resolved) {
			output << line << "\n";

		/* Otherwise mark the next line
		 */
		} else {
			output << "#line " << (lineNumber + 1) << " " << relativeInclude << "\n";
		}
	}


	// TODO


	return true;
}





/**
 * Partially resolves {@code #include} directives in order to bundle truth as
 * a single header library.
 *
 * @warning This utility does not aim to be universally applicable!
 */
int main(int argc, char** argv) {
	using std::filesystem::exists;
	using std::filesystem::path;


	/* Parse arguments
	 */
	if (4 != argc) {
		printUsage();
		return EXIT_FAILURE;
	}

	path const resolveBaseDirectory{argv[1]};
	path const relativeInputRootHeaderFile{argv[2]};
	path const outputFile{argv[3]};

	if (!exists(resolveBaseDirectory) || !is_directory(resolveBaseDirectory)) {
		printUsage();
		std::cerr << "\tCannot find resolve base directory `" << resolveBaseDirectory << "'" << std::endl;
		return EXIT_FAILURE;
	}

	if (!resolveBaseDirectory.is_absolute()) {
		printUsage();
		std::cerr << "\tResolve base directory `" << resolveBaseDirectory << "' must be an absolute path" << std::endl;
		return EXIT_FAILURE;
	}

	if (!relativeInputRootHeaderFile.is_relative()) {
		printUsage();
		std::cerr << "\tInput root header file `" << relativeInputRootHeaderFile << "' must be specified relative to resolve base directory `" << resolveBaseDirectory << "'" << std::endl;
		return EXIT_FAILURE;
	}



	/* Preprocess {@code #include} directives starting from the root header
	 * file
	 */
	std::ofstream output{outputFile};
	std::set<path> includedFiles;

	preprocess(
		includedFiles,
		resolveBaseDirectory,
		relativeInputRootHeaderFile,
		output
	);



	return EXIT_SUCCESS;
}

