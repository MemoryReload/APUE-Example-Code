//
// Created by 何平 on 2020/4/28.
//
#include <apue.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>

typedef  int TraverseFunc (const char* filepath, const struct stat *filestat, int filetype);
static int ftw(const char* path, TraverseFunc func);
static int doPath(TraverseFunc func);
static TraverseFunc myfunc;

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char *argv[]){
    size_t dirLen = PATH_MAX;
    char dir[1024];
    if (argc<2){
        if (getcwd(dir,dirLen) == NULL)
            err_quit("get cwd error");
    } else{
        strcpy(dir,argv[1]);
    }
    int ret = ftw(dir,myfunc);
    ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
    if (0 == ntot) ntot = 1;
    printf("regular files   = %7ld, %5.2f%%\n",nreg,nreg*100.0/ntot);
    printf("directories     = %7ld, %5.2f%%\n",ndir,ndir*100.0/ntot);
    printf("block special   = %7ld, %5.2f%%\n",nblk,nblk*100.0/ntot);
    printf("char special    = %7ld, %5.2f%%\n",nchr,nchr*100.0/ntot);
    printf("FIFOs           = %7ld, %5.2f%%\n",nfifo,nfifo*100.0/ntot);
    printf("symbolic links  = %7ld, %5.2f%%\n",nslink,nslink*100.0/ntot);
    printf("sockets         = %7ld, %5.2f%%\n",nsock,nsock*100.0/ntot);
    return ret;
};

#define FTW_F    1   //file
#define FTW_D    2   //directory
#define FTW_DNR  3   //directory cannot read
#define FTW_NS   4   //file cannot stat

static char *fullpath;
static size_t pathlen;

static int ftw(const char* path, TraverseFunc func) {
    fullpath = path_alloc(&pathlen);
    if (pathlen<strlen(path)){
        pathlen = 2*strlen(path);
        if (NULL == (fullpath = realloc(fullpath,pathlen)))
            err_sys("realloc failed");
    }
    strcpy(fullpath,path);
    return doPath(myfunc);
};

static int doPath(TraverseFunc func)
{
    struct stat statBuf;
    DIR  *dir;
    struct dirent *dirent;
    int n, ret;
    //reveal self
    if (lstat(fullpath,&statBuf)<0)
        return myfunc(fullpath,&statBuf,FTW_NS);
    if (0 == S_ISDIR(statBuf.st_mode))
        return myfunc(fullpath,&statBuf,FTW_F);
    //extend the full path memory
    n = strlen(fullpath);
    if (n+NAME_MAX+2>pathlen){
        pathlen *=2;
        if ((fullpath = realloc(fullpath,pathlen))==NULL)
            err_sys("realloc failed");
    }
    *(fullpath+n)='/';
    *(fullpath+n+1) = '\0';
    if ((dir = opendir(fullpath)) == NULL){
        return myfunc(fullpath,&statBuf,FTW_DNR);
    }
    ret =  myfunc(fullpath,&statBuf,FTW_D);
    while ((dirent = readdir(dir)) != NULL){
        if (strcmp(dirent->d_name,".") == 0 || strcmp(dirent->d_name,"..") ==0 )
            continue;
//        strcat(fullpath,dirent->d_name);
//        ret = doPath(myfunc);
//        *(fullpath+n+1) = '\0';
//        if (ret!=0)
//            break;
// as code above, if we use strcat, we should recove the fullpath after appending. So we just use strcpy instead.
        strcpy(fullpath+n+1,dirent->d_name);
        if ((ret = doPath(myfunc))!=0)
            break;
    }
    //restore the fullpath
    *(fullpath+n) = '\0';
    if (closedir(dir)<0)
        err_ret("can’t close directory %s", fullpath);
    return ret;
};

static int myfunc (const char* filepath, const struct stat *filestat, int filetype)
{
    switch (filetype) {
        case FTW_F:
            switch (filestat->st_mode & S_IFMT) {
                case S_IFREG:
                    nreg++; break;
                case S_IFBLK:
                    nblk++; break;
                case S_IFCHR:
                    nchr++; break;
                case S_IFIFO:
                    nfifo++; break;
                case S_IFLNK:
                    nslink++; break;
                case S_IFSOCK:
                    nsock++; break;
            }
            break;
        case FTW_D: ndir++;
            break;
        case FTW_DNR:
            err_ret("can’t read directory %s", filepath);
            break;
        case FTW_NS:
            err_ret("stat error for %s", filepath);
            break;
        default:
            err_dump("unknown type %d for pathname %s", filetype, filepath); }
    return(0);
};
