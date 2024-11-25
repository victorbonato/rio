#include <stdio.h>
#include <errno.h>

#define RIO_BUFSIZE 8192

typedef struct {
    int rio_fd; // Descriptor for this internal buf
    int rio_cnt; // Unread bytes in internal buf
    char* rio_bufptr; // Next unread byte in internal buf
    char rio_buf[RIO_BUFSIZE];
} rio_t;

// Unbuffered I/O
ssize_t rio_readn(int fd, void* usrbuf, size_t n);
ssize_t rio_writen(int fd, void* usrbuf, size_t n);

// Buffered I/O
void rio_readinitb(rio_t* rp, int fd);
ssize_t rio_readlineb(rio_t* rp, void* usrbuf, size_t maxlen);
ssize_t rio_readnb(rio_t* rp, void* usrbuf, size_t n);

