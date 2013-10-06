#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>


#define UNUSED_PARAM(expr) do { (void)(expr); } while (0)



#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif
    

__attribute__((weak))
int write_stdout(const unsigned char *ptr, unsigned int len)
{
    UNUSED_PARAM(ptr);
    UNUSED_PARAM(len);
    return 0;
}


__attribute__((weak))
int write_stderr(const unsigned char *ptr, unsigned int len)
{
    UNUSED_PARAM(ptr);
    UNUSED_PARAM(len);
    return 0;
}

__attribute__((weak))
ssize_t read_stdin(unsigned char *ptr, unsigned int count)
{
    UNUSED_PARAM(ptr);
    UNUSED_PARAM(count);
    return 0;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    fwrite(STDERR_FILENO, "assert failed | file : '%s:%d'\r\n", file, line);
  /* Infinite loop */
  while (1)
  {
  }
}
#endif	

/*
 environ
 A pointer to a list of environment variables and their values.
 For a minimal environment, this empty list is adequate:
 */
char *__env[1] = { 0 };
char **environ = __env;


/*
 execve
 Transfer control to a new process. Minimal implementation (for a system without processes):
 */
 __attribute__((weak))
int _execve(char *name, char **argv, char **env)
{
	UNUSED_PARAM(name);
	UNUSED_PARAM(argv);
	UNUSED_PARAM(env);

    errno = ENOMEM;
    return -1;
}

/*
 fork
 Create a new process. Minimal implementation (for a system without processes):
 */
__attribute__((weak))
int _fork()
{
    errno = EAGAIN;
    return -1;
}

/*
 fstat
 Status of an open file. For consistency with other minimal implementations in these examples,
 all files are regarded as character special devices.
 The `sys/stat.h' header file required is distributed in the `include' subdirectory for this C library.
 */
 __attribute__((weak))
int _fstat(int file, struct stat *st)
{
	UNUSED_PARAM(file);
    st->st_mode = S_IFCHR;
    return 0;
}


/*
 kill
 Send a signal. Minimal implementation:
 */
__attribute__((weak))
int _kill(int pid, int sig)
{
	UNUSED_PARAM(pid);
	UNUSED_PARAM(sig);
    errno = EINVAL;
    return (-1);
}

/*
 getpid
 Process-ID; this is sometimes used to generate strings unlikely to conflict with other processes. Minimal implementation, for a system without processes:
 */
__attribute__((weak))
pid_t _getpid(void)
{
	return 1;
}

/*
 stat
 Status of a file (by name). Minimal implementation:
 int    _EXFUN(stat,( const char *__path, struct stat *__sbuf ));
 */
__attribute__((weak))
int _stat(const char *filepath, struct stat *st)
{
	UNUSED_PARAM(filepath);
    st->st_mode = S_IFCHR;
    return 0;
}

/*
 times
 Timing information for current process. Minimal implementation:
 */
__attribute__((weak))
clock_t _times(struct tms *buf)
{
	UNUSED_PARAM(buf);
    return -1;
}

/*
 unlink
 Remove a file's directory entry. Minimal implementation:
 */
 __attribute__((weak))
int _unlink(char *name)
{
	UNUSED_PARAM(name);
    errno = ENOENT;
    return -1;
}

/*
 wait
 Wait for a child process. Minimal implementation:
 */
 __attribute__((weak))
int _wait(int *status)
{
	UNUSED_PARAM(status);
    errno = ECHILD;
    return -1;
}


/*
 write
 Write a character to a file. `libc' subroutines will use this system routine for output to all files, including stdout
 Returns -1 on error or number of bytes sent
 */
int _write(int file, char *ptr, int len)
{
    switch (file)
    {
    case STDOUT_FILENO: /*stdout*/
        return write_stdout((const unsigned char*)ptr, (unsigned int)len);
        break;
    case STDERR_FILENO: /* stderr */
        return write_stderr((const unsigned char*)ptr, (unsigned int)len);
        break;
    default:
        errno = EBADF;
        return -1;
    }
    return 0;
}


/*
 lseek
 Set position in a file. Minimal implementation:
 */
__attribute__((weak))
int _lseek(int file, int ptr, int dir)
{
	UNUSED_PARAM(file);
	UNUSED_PARAM(ptr);
	UNUSED_PARAM(dir);
    return 0;
}

/*
 isatty
 Query whether output stream is a terminal. For consistency with the other minimal implementations,
 */
__attribute__((weak))
int _isatty(int file)
{
	switch (file)
	{
		case STDOUT_FILENO:
		case STDERR_FILENO:
		case STDIN_FILENO:
        	return 1;


        default:
        errno = EBADF;
        return 0;
    }
}


/*
 link
 Establish a new name for an existing file. Minimal implementation:
 */
__attribute__((weak))
int _link(char *old, char *new)
{
	UNUSED_PARAM(old);
	UNUSED_PARAM(new);
    errno = EMLINK;
    return -1;
}

__attribute__((weak))
int _open(const char *pathname, int flags, mode_t mode)
{
	UNUSED_PARAM(pathname);
	UNUSED_PARAM(flags);
	UNUSED_PARAM(mode);

	return -1;
}

__attribute__((weak))
int _close(int file)
{
	UNUSED_PARAM(file);
	return -1;
}

__attribute__((weak))
void _exit(int code)
{
	UNUSED_PARAM(code);
	while(1)
	{
	}
}

/*appropriate definition of _heap and _heap_end has to be done in the linker script*/ 
extern int _heap;
extern int _heap_end;
 
caddr_t  _sbrk ( int incr )
{
    static unsigned char *heap = NULL;
    void *prev_heap;
    void *heap_end = &_heap_end;

    if (heap == NULL)
        heap = (unsigned char *)&_heap;
    
    prev_heap = heap;
    if ((prev_heap + incr) < heap_end)
    {
      	prev_heap = heap;
      	heap += incr;
    }
    else
        return (caddr_t)-1;

    return (caddr_t) prev_heap;
}


/*
 read
 Read a character to a file. `libc' subroutines will use this system routine for input from all files, including stdin
 Returns -1 on error or blocks until the number of characters have been read.
 */
 __attribute__((weak))
ssize_t _read(int file, char *ptr, size_t count)
{
    switch (file)
    {
    case STDIN_FILENO:
        return read_stdin((unsigned char*)ptr, (unsigned int)count);
        break;
    default:
        errno = EBADF;
        return -1;
    }
}


#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
