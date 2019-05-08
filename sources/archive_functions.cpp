//
// Created by Yevhenii on 23/04/2019.
//
#include "../headers/archive_functions.h"

using std::string;
using std::vector;

int copy_data(struct archive *ar, struct archive *aw)
{
    int r;
    const void *buff;
    size_t size;
    la_int64_t offset;

    for (;;) {
        r = archive_read_data_block(ar, &buff, &size, &offset);
        if (r == ARCHIVE_EOF)
            return (ARCHIVE_OK);
        if (r < ARCHIVE_OK)
            return (r);
        r = static_cast<int>(archive_write_data_block(aw, buff, size, offset));
        if (r < ARCHIVE_OK) {
            fprintf(stderr, "%s\n", archive_error_string(aw));
            return (r);
        }
    }
}

void extract(const string& filename)
{
    struct archive *a;
    struct archive *ext;
    struct archive_entry *entry;
    int flags;
    int r;

    flags = ARCHIVE_EXTRACT_TIME;
    flags |= ARCHIVE_EXTRACT_PERM;
    flags |= ARCHIVE_EXTRACT_ACL;
    flags |= ARCHIVE_EXTRACT_FFLAGS;

    a = archive_read_new();
    archive_read_support_format_all(a);
    ext = archive_write_disk_new();
    archive_write_disk_set_options(ext, flags);
    archive_write_disk_set_standard_lookup(ext);
    if ((r = archive_read_open_filename(a, filename.c_str(), 0)))
        throw std::runtime_error("Archive has been corrupted");
    for (;;) {
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
            break;
        if (r < ARCHIVE_OK)
            fprintf(stderr, "%s\n", archive_error_string(a));
        if (r < ARCHIVE_WARN)
            throw std::runtime_error("Archive has been corrupted");
        r = archive_write_header(ext, entry);
        if (r < ARCHIVE_OK)
            fprintf(stderr, "%s\n", archive_error_string(ext));
        else if (archive_entry_size(entry) > 0) {
            r = copy_data(a, ext);
            if (r < ARCHIVE_OK)
                fprintf(stderr, "%s\n", archive_error_string(ext));
            if (r < ARCHIVE_WARN)
                throw std::runtime_error("Archive has been corrupted");
        }
        r = archive_write_finish_entry(ext);
        if (r < ARCHIVE_OK)
            fprintf(stderr, "%s\n", archive_error_string(ext));
        if (r < ARCHIVE_WARN)
            throw std::runtime_error("Archive has been corrupted");
    }
    archive_read_close(a);
    archive_read_free(a);
    archive_write_close(ext);
    archive_write_free(ext);
}

vector<string> read_archive_entries(const string& path){
    vector<string> entries;
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);
    r = archive_read_open_filename(a, path.c_str(), 0); // Note 1
    if (r != ARCHIVE_OK)
        throw std::runtime_error("Archive has been corrupted");
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        entries.emplace_back(archive_entry_pathname(entry));
        archive_read_data_skip(a);
    }
    r = archive_read_free(a);
    if (r != ARCHIVE_OK)
        throw std::runtime_error("Archive has been corrupted");

    return entries;
}