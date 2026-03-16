int qemu_get_thread_id(void)

{


    return syscall(SYS_gettid);


    return getpid();


}
