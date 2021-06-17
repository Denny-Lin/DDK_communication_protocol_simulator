# DDK_communication_protocol_simulator
Simulate UART, I2C, ... , SPI via IPC(Inter-Process Communication) technique.
* It is an idea.
* It has two processes.
<br><br/>

## Features
* The first process communicate with the second process.
* Show some details when communication.
* One be master and the other be slave.
<br><br/>

## Platforms
* windows
<br><br/>

## Languages
* C, C++, C#
<br><br/>

## Techniques
* IPC(Inter-Process Communication)
* Share memory
* Knowledge of windows.h
<br><br/>

## Methods
1. File
2. Communications file
3. Signal; also Asynchronous System Trap
4. Socket
5. Unix domain socket
6. Message queue
7. Anonymous pipe
8. Named pipe
9. Shared memory
10. Message passing
11. Memory-mapped file
<br><br/>

### Pipe
![image](https://user-images.githubusercontent.com/67073582/122335449-e0830580-cf6d-11eb-82d1-d24c84095f44.png)

```c
       #include <unistd.h>
       
       /* On Alpha, IA-64, MIPS, SuperH, and SPARC/SPARC64; see NOTES */
       struct fd_pair {
           long fd[2];
       };
       struct fd_pair pipe();

       /* On all other architectures */
       int pipe(int pipefd[2]);

       #define _GNU_SOURCE             /* See feature_test_macros(7) */
       #include <fcntl.h>              /* Obtain O_* constant definitions */
       #include <unistd.h>

       int pipe2(int pipefd[2], int flags);
```

## References
* <https://en.wikipedia.org/wiki/Inter-process_communication>
* <https://pws.niu.edu.tw/~ttlee/os.101.1/night/sharedMemory/>
* https://zhuanlan.zhihu.com/p/58489873
* https://man7.org/linux/man-pages/man2/pipe.2.html
