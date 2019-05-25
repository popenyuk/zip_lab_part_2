// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <iostream>
#include <archive.h>
#include <archive_entry.h>
#include "archive_functions.h"
#include "work_with_text_file.h"

using std::string;
using std::vector;
using std::runtime_error;

vector<string> extract_in_memory(const string &filename, dispatcher *current) {
    vector<string> files_in_memory;
    struct archive *a;
    struct archive_entry *entry;
    int r;
    string sentence;
    a = archive_read_new();
    archive_read_support_format_all(a);
    if (archive_read_open_filename(a, filename.c_str(), 0)) {
        throw runtime_error("Archive has been corrupted");
    }
    size_t size;
    char data[1];
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        if (find_extension(archive_entry_pathname(entry)) == "txt") {
            size = archive_entry_size(entry);
            if (size < 0) {
                break;
            }
            for (size_t index = 0; index < size; ++index) {
                r = archive_read_data(a, data, sizeof(char));
                if (r != sizeof(char)) {
                    break;
                }
                sentence.push_back(data[0]);
            }
            if (current != nullptr) {
                current->push_data(sentence);
            } else {
                files_in_memory.push_back(sentence);
            }
            sentence.clear();
        } else {
            archive_read_data_skip(a);
        }
    }
    archive_read_close(a);
    archive_read_free(a);
    return files_in_memory;
}