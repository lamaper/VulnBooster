void av_thread_message_queue_free(AVThreadMessageQueue **mq)

{


    if (*mq) {

        av_thread_message_flush(*mq);

        av_fifo_freep(&(*mq)->fifo);

        pthread_cond_destroy(&(*mq)->cond);

        pthread_mutex_destroy(&(*mq)->lock);

        av_freep(mq);

    }


}
