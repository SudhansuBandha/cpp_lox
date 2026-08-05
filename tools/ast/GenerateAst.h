#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class GenerateAst
{
public:
    static void defineAst(
        const fs::path& outputDir,
        const std::string& baseName,
        const std::vector<std::string>& types);

private:
    static void defineVisitor(
        std::ofstream& writer,
        const std::string& baseName,
        const std::vector<std::string>& types);

    static void defineType(
        std::ofstream& writer,
        const std::string& baseName,
        const std::string& className,
        const std::string& fieldList);
};