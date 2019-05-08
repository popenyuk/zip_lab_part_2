#include <algorithm>
#include "configuration.h"
#include "time_functions.h"
#include "archive_functions.h"
#include "work_with_text_file.h"

int main(int argc, char *argv[]) {
    boost::locale::generator gen;
    std::locale loc = gen.generate("en_US.UTF-8");
    std::locale::global(loc);
    std::cout.imbue(loc);

    std::string conf_file;
    if (argc < 2) {
        conf_file = "../config.dat";
    } else if (argc > 2) {
        std::cerr << "Wrong number of arguments. Usage: <config_filename>";
        exit(-1);
    } else {
        conf_file = argv[1];
    }

    std::string in_file;
    config conf;
    try {
        conf = read_config(conf_file);
    } catch (std::invalid_argument &e) {
        std::cerr << "Invalid argument." << std::endl;
        exit(-3);
    }

    auto time_all_start = get_current_time_fenced();
    auto time_reading_start = get_current_time_fenced();
//--------------------------------   Reading file in memory
    auto extension = find_extension(conf.in_file);
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    if (extension == "zip") {
        extract(conf.in_file);
        read_file_into_string(read_archive_entries(conf.in_file)[0], in_file);
    } else if (extension == "txt") {
        read_file_into_string(conf.in_file, in_file);
    } else {
        std::cerr << "Wrong file extension." << std::endl;
        exit(-2);
    }
    std::vector<std::string> words;
    separate_by_words(in_file, words);
//--------------------------------
    auto time_reading_end = get_current_time_fenced();
    auto time_reading_total = time_reading_end - time_reading_start;

    auto time_counting_words_start = get_current_time_fenced();
//--------------------------------   Counting words
    std::unordered_map<std::string, size_t> words_map;
    run_multi_thread(conf.threads, words, words_map);
//--------------------------------
    auto time_counting_words_end = get_current_time_fenced();
    auto time_counting_words_total = time_counting_words_end - time_counting_words_start;

    auto time_sorting_start = get_current_time_fenced();
//--------------------------------   Sorting
    auto by_numbers = sort_words(words_map);
    auto by_words = sort_words(words_map, false);
//--------------------------------
    auto time_sorting_end = get_current_time_fenced();
    auto time_sorting_total = time_sorting_end - time_sorting_start;

//--------------------------------   Writing to the file
    write_to_file(conf.out_by_number, by_numbers);
    write_to_file(conf.out_by_name, by_words);
//--------------------------------
    auto time_all_end = get_current_time_fenced();
    auto time_all_total = time_all_end - time_all_start;

    std::cout << "Reading time: " << to_us(time_reading_total) << std::endl;
    std::cout << "Counting words time: " << to_us(time_counting_words_total) << std::endl;
    std::cout << "Sorting time: " << to_us(time_sorting_total) << std::endl;
    std::cout << "Total time: " << to_us(time_all_total) << std::endl;

    return 0;
}