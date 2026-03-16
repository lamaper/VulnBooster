int qcrypto_init(Error **errp)

{

    int ret;

    ret = gnutls_global_init();

    if (ret < 0) {

        error_setg(errp,

                   "Unable to initialize GNUTLS library: %s",

                   gnutls_strerror(ret));

        return -1;

    }


    gnutls_global_set_log_level(10);

    gnutls_global_set_log_function(qcrypto_gnutls_log);



    if (!gcry_check_version(GCRYPT_VERSION)) {

        error_setg(errp, "Unable to initialize gcrypt");

        return -1;

    }


    gcry_control(GCRYCTL_SET_THREAD_CBS, &qcrypto_gcrypt_thread_impl);


    gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);




    return 0;

}
