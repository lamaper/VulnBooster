static void set_options(URLContext *h, const char *uri)

{

    TLSContext *c = h->priv_data;

    char buf[1024], key[1024];

    int has_cert, has_key;


    int ret;


    const char *p = strchr(uri, '?');

    if (!p)

        return;



    if (av_find_info_tag(buf, sizeof(buf), "cafile", p)) {


        ret = gnutls_certificate_set_x509_trust_file(c->cred, buf, GNUTLS_X509_FMT_PEM);

        if (ret < 0)

            av_log(h, AV_LOG_ERROR, "%s\n", gnutls_strerror(ret));


        if (!SSL_CTX_load_verify_locations(c->ctx, buf, NULL))

            av_log(h, AV_LOG_ERROR, "SSL_CTX_load_verify_locations %s\n", ERR_error_string(ERR_get_error(), NULL));


    }



    has_cert = av_find_info_tag(buf, sizeof(buf), "cert", p);

    has_key  = av_find_info_tag(key, sizeof(key), "key", p);


    if (has_cert && has_key) {

        ret = gnutls_certificate_set_x509_key_file(c->cred, buf, key, GNUTLS_X509_FMT_PEM);

        if (ret < 0)

            av_log(h, AV_LOG_ERROR, "%s\n", gnutls_strerror(ret));

    } else if (has_cert ^ has_key) {

        av_log(h, AV_LOG_ERROR, "cert and key required\n");

    }


    if (has_cert && !SSL_CTX_use_certificate_chain_file(c->ctx, buf))

        av_log(h, AV_LOG_ERROR, "SSL_CTX_use_certificate_chain_file %s\n", ERR_error_string(ERR_get_error(), NULL));

    if (has_key && !SSL_CTX_use_PrivateKey_file(c->ctx, key, SSL_FILETYPE_PEM))

        av_log(h, AV_LOG_ERROR, "SSL_CTX_use_PrivateKey_file %s\n", ERR_error_string(ERR_get_error(), NULL));


}
