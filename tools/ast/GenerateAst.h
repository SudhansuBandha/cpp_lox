#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string_view>

namespace fs = std::filesystem;

struct Field{
    std::string_view type;
    std::string_view name;
};

static Field parseField(std::string_view field);

class GenerateAst
{
public:
    static void defineAst(
        const fs::path& outputDirHeader,
        const fs::path& outputDirSource,
        const std::string& baseName,
        const std::vector<std::string>& types);

private:
    static void generateHeader(
        std::ofstream& writer,
        const std::string& baseName,
        const std::vector<std::string>& types
    );

    static void generateSource(
        std::ofstream& writer,
        const std::string& baseName,
        const std::vector<std::string>& types
    );

    static void defineVisitor(
        std::ofstream& writer,
        const std::string& baseName,
        const std::vector<std::string>& types);
    
    static void defineBaseClass(
        std::ofstream& writer,
        const std::string& baseName);

    static void defineType(
        std::ofstream& writer,
        const std::string& baseName,
        const std::string& className,
        const std::string& fieldList);
    
    static void defineTypeImplementation(
        std::ofstream& writer,
        const std::string& baseName,
        const std::string& className,
        const std::string& fieldList
    ); 
       
   static std::string_view trim(const std::string_view& str);   
   
   struct FieldInfo
    {
        std::string_view type;
        std::string_view name;
    };

    static FieldInfo parseField(std::string_view field);
    
    static std::vector<FieldInfo> parseFields(
        std::string_view fieldList
    );


};