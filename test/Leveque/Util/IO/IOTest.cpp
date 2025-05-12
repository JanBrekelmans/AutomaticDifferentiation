#include <doctest/doctest.h>

#include <filesystem>
#include <string>
#include <vector>

#include <Leveque/Util/IO/FileReader.h>
#include <Leveque/Util/IO/FileWriter.h>

TEST_CASE("Input/output") {
	using namespace Jabre::Leveque;

	std::filesystem::path tempPath = std::filesystem::temp_directory_path();
    std::string fileName = "test.txt";
    std::filesystem::path path = tempPath / fileName;
	
	FileWriter writer(path);
    REQUIRE(writer.path() == path);
    writer.write("test");
    writer.flush();

	FileReader reader(path);
    REQUIRE(reader.path() == path);
    REQUIRE(reader.getLineNumber() == 1);
    REQUIRE(reader.getLine() == "test");
    REQUIRE(reader.getLineNumber() == 2);
    REQUIRE(reader.isEndOfFile());

    reader.reset();
    REQUIRE(reader.getLineNumber() == 1);
    REQUIRE(reader.getLine() == "test");
    REQUIRE(reader.getLineNumber() == 2);
    REQUIRE(reader.isEndOfFile());
}