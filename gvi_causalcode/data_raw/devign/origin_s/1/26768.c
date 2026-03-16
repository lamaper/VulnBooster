int avformat_network_init(void)

{


    int ret;

    ff_network_inited_globally = 1;

    if ((ret = ff_network_init()) < 0)

        return ret;

    ff_tls_init();


    return 0;

}
