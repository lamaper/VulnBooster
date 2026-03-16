bool qemu_signalfd_available(void)

{


    errno = 0;

    syscall(SYS_signalfd, -1, NULL, _NSIG / 8);

    return errno != ENOSYS;


    return false;


}
