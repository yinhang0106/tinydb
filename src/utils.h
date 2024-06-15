#pragma once

#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <cstdint>

static void msg(const char *msg) {
    fprintf(stderr, "%s\n", msg);
}

static void die(const char *msg) {
    int err = errno;
    fprintf(stderr, "[%d] %s\n", err, msg);
    abort();
}

static void do_something(int fd) {
    char read_buff[64] = {};
    ssize_t n = read(fd, read_buff, sizeof(read_buff) - 1);
    if (n < 0) {
        msg("read() error");
        return;
    }
    printf("client says: %s\n", read_buff);

    char write_buff[] = "world";
    write(fd, write_buff, strlen(write_buff));
}