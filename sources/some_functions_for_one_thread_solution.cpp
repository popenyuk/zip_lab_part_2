// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <iostream>
#include <archive.h>
#include <archive_entry.h>
#include "archive_functions.h"
#include "boost/filesystem.hpp"
#include "work_with_text_file.h"
#include "some_functions_for_one_thread_solution.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::exception;
using std::runtime_error;
using boost::filesystem::recursive_directory_iterator;

vector<string> read_archive_entries_one_thread(const string &path) {
    vector<string> entries;
    struct archive *a;
    struct archive_entry *entry;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);
    if (archive_read_open_filename(a, path.c_str(), 0) != ARCHIVE_OK)
        throw runtime_error("Archive has been corrupted");
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        entries.emplace_back(archive_entry_pathname(entry));
        archive_read_data_skip(a);
    }
    if (archive_read_free(a) != ARCHIVE_OK)
        throw runtime_error("Archive has been corrupted");

    return entries;
}

vector<string> read_txt_files_from_directory_one_thread(const string &folder) {
    vector<string> files;
    int count = 0;
    for (recursive_directory_iterator it(folder), end; it != end; ++it) {
        if (it->path().extension() == ".ZIP") {
            try {
                extract(it->path().string());
                for (auto &file:read_archive_entries_one_thread(it->path().string())) {
                    if(find_extension(file) == "txt"){
                        files.push_back(file);
                    }
                }
            } catch (const exception &e) {
                ++count;
            }
        }
        if (it->path().extension() == ".txt") {
            files.push_back(it->path().string());
        }
    }
    cout << "Number of corrupted files: " << count << endl;
    return files;
}