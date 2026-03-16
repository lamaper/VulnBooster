void ff_tls_init(void)

{

    avpriv_lock_avformat();


    if (!openssl_init) {

        SSL_library_init();

        SSL_load_error_strings();


        if (!CRYPTO_get_locking_callback()) {

            int i;

            openssl_mutexes = av_malloc_array(sizeof(pthread_mutex_t), CRYPTO_num_locks());

            for (i = 0; i < CRYPTO_num_locks(); i++)

                pthread_mutex_init(&openssl_mutexes[i], NULL);

            CRYPTO_set_locking_callback(openssl_lock);


            CRYPTO_set_id_callback(openssl_thread_id);


        }


    }

    openssl_init++;




    if (gcry_control(GCRYCTL_ANY_INITIALIZATION_P) == 0)

        gcry_control(GCRYCTL_SET_THREAD_CBS, &gcry_threads_pthread);


    gnutls_global_init();


    avpriv_unlock_avformat();

}
