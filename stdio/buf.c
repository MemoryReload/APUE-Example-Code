#include "apue.h"
#include <stdio.h>

void  pr_stdio(char* filename, FILE* file);
int   is_unbuffered(FILE* file);
int   is_linebuffered(FILE* file);
int   buffer_size(FILE* file);

int main() {
    fputs("enter any character\n",stdout);
    if (getchar() == EOF)
        err_sys("getchar error");
    fputs("one line to standard error\n",stderr);

    pr_stdio("stdin",stdin);
    pr_stdio("stdout",stdout);
    pr_stdio("stderr",stderr);

    FILE * fp = fopen("/etc/passwd", "r");
    if (NULL == fp) err_sys("fopen errror");
    if (getc(fp) == EOF) err_sys("getc error");
    pr_stdio("/etc/passwd",fp);
    exit(0);
}

void pr_stdio(char* filename, FILE* file){
    printf("stream = %s, ",filename);
    if (is_unbuffered(file)) {
        printf("unbuffered");
    } else if (is_linebuffered(file)){
        printf("line buffered");
    } else{
        printf("fully buffered");
    }
    printf(",buffer size = %d\n",buffer_size(file));
}

#if defined(_IO_UNBUFFERED)
int   is_unbuffered(FILE* file)
{
    return(file->_flags & _IO_UNBUFFERED);
}

int   is_linebuffered(FILE* file)
{
    return(file->_flags & _IO_LINE_BUF);
}
int   buffer_size(FILE* file)
{
    return(file->_IO_buf_end - file->_IO_buf_base);
}
#elif defined(__SNBF)
int   is_unbuffered(FILE* file)
{
    return (file->_flags & __SNBF);
}
int   is_linebuffered(FILE* file)
{
    return (file->_flags & __SLBF);
}
int   buffer_size(FILE* file)
{
    return (file->_bf._size);
}

#elif defined(_IONBF)

#ifdef _LP64
#define _flag __pad[4]
#define _ptr __pad[1]
#define _base __pad[2]
#endif

int
is_unbuffered(FILE *fp)
{
	return(fp->_flag & _IONBF);
}

int
is_linebuffered(FILE *fp)
{
	return(fp->_flag & _IOLBF);
}

int
buffer_size(FILE *fp)
{
#ifdef _LP64
	return(fp->_base - fp->_ptr);
#else
	return(BUFSIZ);	/* just a guess */
#endif
}

#else

#error unknown stdio implementation!

#endif