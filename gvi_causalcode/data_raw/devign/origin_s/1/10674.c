static GThread *trace_thread_create(GThreadFunc fn)

{

    GThread *thread;


    sigset_t set, oldset;



    sigfillset(&set);

    pthread_sigmask(SIG_SETMASK, &set, &oldset);


    thread = g_thread_create(writeout_thread, NULL, FALSE, NULL);


    pthread_sigmask(SIG_SETMASK, &oldset, NULL);




    return thread;

}
