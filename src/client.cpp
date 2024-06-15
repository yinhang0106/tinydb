#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

#include "utils.h"

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        die("socket()");
    }

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(1234);
    addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK);  // 127.0.0.1
    int rv = connect(fd, (const struct sockaddr*)&addr, sizeof(addr));
    if (rv < 0) {
        die("connect()");
    }

    char msg[] = "Hello";
    write(fd, msg, strlen(msg));

    char buf[64] = {};
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    if (n < 0) {
        die("read()");
    }
    printf("server says: %s\n", buf);

    close(fd);
}