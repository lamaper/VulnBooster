static void qemu_thread_set_name(QemuThread *thread, const char *name)

{


    pthread_setname_np(thread->thread, name);


}
