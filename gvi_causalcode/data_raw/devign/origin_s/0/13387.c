int avformat_network_init(void)

{


    int ret;

    ff_network_inited_globally = 1;

    if ((ret = ff_network_init()) < 0)

        return ret;

    if ((ret = ff_tls_init()) < 0)

        return ret;


    return 0;

}
