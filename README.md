# PIPEX
	Discover a UNIX mechanism in detail
---

## 0. Pipe
Pipe, a unidirectional data channel that can be used for interprocess communication. This communication could involve a process letting another process know that some event has occurred or the transferring of data from one process to another.

The communication is achieved by one process writing into the pipe and other reading from the pipe. To achieve the pipe system call, create two files, one to write into and another to read from the file.

## 1. Redirections
Before a commnad is executed, its input and output may be *redirected* using a special notation interpreted by the shell. Redirection allows command's file handles to be duplicated, opened, closed, made to refer to different files, and can change the files the command reads from and writes to.

If the file descriptor is omitted, 
- `>`
- `<`

- `>>`
- `<<`

## 2. External functs



## 3. Execution Steps
```
1. Create a pipe.
2. Create a child process.
3. Parent process writes to the pipe.
4. Child proess retrieves the message from the pipe and writes it to the standard output.
```


## Reference
- [pipe(2)-Linux manual page](https://man7.org/linux/man-pages/man2/pipe.2.html) <br>
- [Redirections (Bash Reference Manual) - GNU.org](https://www.gnu.org/software/bash/manual/html_node/Redirections.html)
---

