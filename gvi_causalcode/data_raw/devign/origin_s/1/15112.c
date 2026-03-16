void qemu_aio_wait(void)

{

    sigset_t set;

    int nb_sigs;


    if (qemu_bh_poll())

        return;


    sigemptyset(&set);

    sigaddset(&set, aio_sig_num);

    sigwait(&set, &nb_sigs);

    qemu_aio_poll();

}
