static void curl_multi_timeout_do(void *arg)

{


    BDRVCURLState *s = (BDRVCURLState *)arg;

    int running;



    if (!s->multi) {

        return;

    }



    aio_context_acquire(s->aio_context);

    curl_multi_socket_action(s->multi, CURL_SOCKET_TIMEOUT, 0, &running);



    curl_multi_check_completion(s);

    aio_context_release(s->aio_context);


    abort();


}
