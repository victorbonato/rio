# rio
As taught in Computer Systems - A Programmers Perspective: The Rio package provides convenient, robust, and efficient I/O in applications such as network programs that are subject to short counts.

## Unbuffered functions

The `rio_readn` function transfers up to `n` bytes from the current file position of descriptor `fd` to memory location `usrbuf`. Similarly, the `rio_writen` function transfers `n` bytes from location `usrbuf` to descriptor `fd`. The `rio_readn` function can only return a short count if it encounters `EOF`. The `rio_writen` function never returns a short count. Calls to `rio_readn` and `rio_writen` can be interleaved arbitrarily on the same descriptor.

## Buffered functions

The `rio_readinitb` function is called once per open descriptor. It associates the descriptor `fd` with a read buffer of type `rio_t` at address `rp`.

The `rio_readlineb` function reads the next text line from file `rp` (including the terminating newline character), copies it to memory location `usrbuf`, and terminates the text line with the `NULL` (zero) character. The `rio_readlineb` function reads at most `maxlen-1` bytes, leaving room for the terminating `NULL` character. Text lines that exceed `maxlen-1` bytes are truncated and terminated with a `NULL` character.

The `rio_readnb` function reads up to `n` bytes from file `rp` to memory location `usrbuf`. Calls to r`io_readlineb` and `rio_readnb` can be interleaved arbitrarily on the same descriptor. However, calls to these buffered functions should not be interleaved with calls to the unbuffered `rio_readn` function.

The `rio_read` function is a buffered version of the Linux read function. When `rio_read` is called with a request to read `n` bytes, there are `rp->rio_cnt` unread bytes in the read buffer. If the buffer is empty, then it is replenished with a call to read. Receiving a short count from this invocation of read is not an error; it simply has the effect of partially filling the read buffer. Once the buffer is nonempty, `rio_read` copies the minimum of `n` and `rp->rio_cnt` bytes from the read buffer to the user buffer and returns the number of bytes copied. On error, it returns −1 and sets `errno` appropriately. On `EOF`, it returns 0. It returns a short count if the number of requested bytes exceeds the number of unread bytes in the read buffer.



