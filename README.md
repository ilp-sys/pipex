# PIPEX
	Discover a UNIX mechanism in detail
---

### 0. Pipe
Pipe, a unidirectional data channel that can be used for interprocess communication. This communication could involve a process letting another process know that some event has occurred or the transferring of data from one process to another.

The communication is achieved by one process writing into the pipe and other reading from the pipe. To achieve the pipe system call, create two files, one to write into and another to read from the file.

### Reference
[pipe(2)-Linux manual page](https://man7.org/linux/man-pages/man2/pipe.2.html) <br>
[tutorialspoint | Inter Process Communication - Pipes](https://www.tutorialspoint.com/inter_process_communication/inter_process_communication_pipes.htm) <br>
---

