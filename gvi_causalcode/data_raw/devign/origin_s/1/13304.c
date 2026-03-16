void qemu_sem_wait(QemuSemaphore *sem)

{


    pthread_mutex_lock(&sem->lock);

    --sem->count;

    while (sem->count < 0) {

        pthread_cond_wait(&sem->cond, &sem->lock);

    }

    pthread_mutex_unlock(&sem->lock);


    int rc;



    do {

        rc = sem_wait(&sem->sem);

    } while (rc == -1 && errno == EINTR);

    if (rc < 0) {

        error_exit(errno, __func__);

    }


}
