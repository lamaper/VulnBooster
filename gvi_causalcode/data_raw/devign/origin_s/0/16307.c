_syscall3(int,sys_faccessat,int,dirfd,const char *,pathname,int,mode)



_syscall3(int,sys_fchmodat,int,dirfd,const char *,pathname, mode_t,mode)



_syscall5(int,sys_fchownat,int,dirfd,const char *,pathname,

          uid_t,owner,gid_t,group,int,flags)



        defined(__NR_fstatat64)

_syscall4(int,sys_fstatat64,int,dirfd,const char *,pathname,

          struct stat *,buf,int,flags)



_syscall3(int,sys_futimesat,int,dirfd,const char *,pathname,

         const struct timeval *,times)



        defined(__NR_newfstatat)

_syscall4(int,sys_newfstatat,int,dirfd,const char *,pathname,

          struct stat *,buf,int,flags)



_syscall5(int,sys_linkat,int,olddirfd,const char *,oldpath,

      int,newdirfd,const char *,newpath,int,flags)



_syscall3(int,sys_mkdirat,int,dirfd,const char *,pathname,mode_t,mode)



_syscall4(int,sys_mknodat,int,dirfd,const char *,pathname,

          mode_t,mode,dev_t,dev)



_syscall4(int,sys_openat,int,dirfd,const char *,pathname,int,flags,mode_t,mode)



_syscall4(int,sys_readlinkat,int,dirfd,const char *,pathname,

          char *,buf,size_t,bufsize)



_syscall4(int,sys_renameat,int,olddirfd,const char *,oldpath,

          int,newdirfd,const char *,newpath)



_syscall3(int,sys_symlinkat,const char *,oldpath,

          int,newdirfd,const char *,newpath)



_syscall3(int,sys_unlinkat,int,dirfd,const char *,pathname,int,flags)




static int sys_utimensat(int dirfd, const char *pathname,

    const struct timespec times[2], int flags)

{

    if (pathname == NULL)

        return futimens(dirfd, times);

    else

        return utimensat(dirfd, pathname, times, flags);

}
