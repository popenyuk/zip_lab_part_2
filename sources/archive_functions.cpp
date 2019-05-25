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
    vector<string> file_in_memory;
    struct archive *a;
    struct archive_entry *entry;
    int r;
    string word;
    a = archive_read_new();
    archive_read_support_format_all(a);
    if (archive_read_open_filename(a, filename.c_str(), 0))
        throw runtime_error("Archive has been corrupted");
    for (;;) {
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
            break;
        if (r < ARCHIVE_OK) {
            fprintf(stderr, "%s\n", archive_error_string(a));
        }
        if (r < ARCHIVE_WARN)
            throw runtime_error("Archive has been corrupted");
        if (find_extension(archive_entry_pathname(entry)) == "txt") {
            size_t size = archive_entry_size(entry);
            char data[size];
            r = archive_read_data(a, data, size * sizeof(char));

            if (r == ARCHIVE_EOF)
                break;
            if (r < ARCHIVE_OK) {
                fprintf(stderr, "%s\n", archive_error_string(a));
            }
            if (r < ARCHIVE_WARN)
                throw runtime_error("Archive has been corrupted");

            for(size_t i = 0; i < size; ++i){
                word.push_back(data[i]);
            }
            if (current != nullptr) {
                current->push_data(word);
            } else {
                file_in_memory.push_back(word);
            }
            word.clear();
        }
    }
    archive_read_close(a);
    archive_read_free(a);
    return file_in_memory;
}