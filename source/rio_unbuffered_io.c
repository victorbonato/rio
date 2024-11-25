#include "rio.h"

ssize_t rio_readn(int fd, void* usrbuf, size_t n) {
    size_t nleft = n;
    ssize_t nread;
    char* bufp = usrbuf;

    while (nleft > 0) {
        if ((nread = read(fd, bufp, nleft)) < 0) {
            if (errno == EINTR) // interrupted by sig handler return
                nread = 0;
            else
                return -1; // errno set by read()
        }
        else if (nread == 0) // EOF
            break;

        nleft -= nread;
        bufp += nread;
    }

    return (n - nleft);
}

ssize_t rio_writen(int fd, void* usrbuf, size_t n) {
    size_t nleft = n;
    ssize_t nwritten;
    char* bufp = usrbuf;

    while (nleft > 0) {
        if ((nwritten = write(fd, bufp, nleft)) <= 0) {
            if (errno == EINTR) // interrupted by sig handler return
                nwritten = 0;
            else
                return -1; // errno set by write()
        }
        nleft -= nwritten;
        bufp += nwritten;
    }

    return n;
}