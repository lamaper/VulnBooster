int avformat_network_deinit(void)

{


    ff_network_close();

    ff_tls_deinit();

    ff_network_inited_globally = 0;


    return 0;

}
