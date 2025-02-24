#include <string>                // strings

#include "cli_test.hpp"

#include "ibf.h"
#include "shared.h"

struct estimate_options_test : public cli_test {};

TEST_F(estimate_options_test, no_options)
{
    cli_test_result result = execute_app("needle estimate");
    std::string expected
    {
        "needle-estimate - Estimate expression value of transcript based on the Needle index.\n"
        "====================================================================================\n"
        "    Try -h or --help for more information.\n"
    };
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.out, expected);
    EXPECT_EQ(result.err, std::string{});
}

TEST_F(estimate_options_test, fail_no_argument)
{
    cli_test_result result = execute_app("needle estimate", "-m");
    std::string expected
    {
        "Error. Incorrect command line input for estimate. Not enough positional arguments provided "
        "(Need at least 1). See -h/--help for more information.\n"
    };
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.out, std::string{});
    EXPECT_EQ(result.err, expected);
}

TEST_F(estimate_options_test, with_argument)
{
    estimate_ibf_arguments ibf_args{};
    minimiser_arguments minimiser_args{};
    ibf_args.expression_thresholds = {1, 2};
    std::vector<double> fpr = {0.05};
    std::vector<std::filesystem::path> sequence_files = {data("exp_01.fasta")};
    ibf_args.path_out = "Test_";
    std::vector<uint8_t> cutoffs{};
    ibf(sequence_files, ibf_args, minimiser_args, fpr, cutoffs);

    cli_test_result result = execute_app("needle estimate -i ", "Test_", data("mini_gen.fasta"));
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.out, "");
    EXPECT_EQ(result.err, std::string{});
}

TEST_F(estimate_options_test, with_argument_normalization_method)
{
    estimate_ibf_arguments ibf_args{};
    minimiser_arguments minimiser_args{};
    ibf_args.expression_thresholds = {1, 2};
    std::vector<double> fpr = {0.05};
    std::vector<std::filesystem::path> sequence_files = {data("exp_01.fasta")};
    ibf_args.path_out = "Test_";
    std::vector<uint8_t> cutoffs{};
    ibf(sequence_files, ibf_args, minimiser_args, fpr, cutoffs);

    cli_test_result result = execute_app("needle estimate -m -i ", "Test_", data("mini_gen.fasta"));
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.out, "");
    EXPECT_EQ(result.err, std::string{});
}

TEST_F(estimate_options_test, with_argument_out)
{
    estimate_ibf_arguments ibf_args{};
    minimiser_arguments minimiser_args{};
    ibf_args.expression_thresholds = {1, 2};
    std::vector<double> fpr = {0.05};
    std::vector<std::filesystem::path> sequence_files = {data("exp_01.fasta")};
    ibf_args.path_out = "Test_";
    std::vector<uint8_t> cutoffs{};
    ibf(sequence_files, ibf_args, minimiser_args, fpr, cutoffs);

    cli_test_result result = execute_app("needle estimate -o ", "expressions.out","-i ", "Test_", data("mini_gen.fasta"));
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.out, "");
    EXPECT_EQ(result.err, std::string{});
}
