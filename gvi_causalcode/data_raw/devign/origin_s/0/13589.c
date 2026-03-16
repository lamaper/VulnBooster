_syscall4(int,sys_utimensat,int,dirfd,const char *,pathname,

          const struct timespec *,tsp,int,flags)






static int sys_inotify_init(void)

{

  return (inotify_init());

}
