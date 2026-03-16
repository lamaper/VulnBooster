void kvm_init_cpu_signals(CPUState *cpu)

{

    int r;

    sigset_t set;

    struct sigaction sigact;



    memset(&sigact, 0, sizeof(sigact));

    sigact.sa_handler = dummy_signal;

    sigaction(SIG_IPI, &sigact, NULL);



    pthread_sigmask(SIG_BLOCK, NULL, &set);


    sigdelset(&set, SIGBUS);

    pthread_sigmask(SIG_SETMASK, &set, NULL);


    sigdelset(&set, SIG_IPI);

    r = kvm_set_signal_mask(cpu, &set);

    if (r) {

        fprintf(stderr, "kvm_set_signal_mask: %s\n", strerror(-r));

        exit(1);

    }

}
