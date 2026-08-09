#include <cctype>
#include <gtest/gtest.h>

#include "../fixtures/ParserTestCases.h"
#include "../helpers/ParserTestHelper.h"

class ParserTest
    : public ::testing::TestWithParam<ParserTestCase> {
};

TEST_P(ParserTest, ProducesExpectedAst)
{
    const auto& testCase = GetParam();

    EXPECT_EQ(
        parseToAst(testCase.source),
        testCase.expectedAst
    );
}

INSTANTIATE_TEST_SUITE_P(
    ParserExpressions,
    ParserTest,
    ::testing::ValuesIn(parserTestCases),
    [](const testing::TestParamInfo<ParserTestCase>& info) {

        std::string name = info.param.name;

        for (char& c : name) {
            if (!std::isalnum(static_cast<unsigned char>(c))) {
                c = '_';
            }
        }

        return name;
    }
);