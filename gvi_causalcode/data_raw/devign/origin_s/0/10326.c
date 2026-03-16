static void qemu_cpu_kick_thread(CPUState *env)

{


    int err;



    err = pthread_kill(env->thread->thread, SIG_IPI);

    if (err) {

        fprintf(stderr, "qemu:%s: %s", __func__, strerror(err));

        exit(1);

    }


    if (!qemu_cpu_is_self(env)) {

        SuspendThread(env->thread->thread);

        cpu_signal(0);

        ResumeThread(env->thread->thread);

    }


}
