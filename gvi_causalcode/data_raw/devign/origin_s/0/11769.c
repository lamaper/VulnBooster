int event_notifier_init(EventNotifier *e, int active)

{


    int fd = eventfd(!!active, EFD_NONBLOCK | EFD_CLOEXEC);

    if (fd < 0)

        return -errno;

    e->fd = fd;

    return 0;


    return -ENOSYS;


}
