int ff_network_init(void)

{


    WSADATA wsaData;




    if (!ff_network_inited_globally)

        av_log(NULL, AV_LOG_WARNING, "Using network protocols without global "

                                     "network initialization. Please use "

                                     "avformat_network_init(), this will "

                                     "become mandatory later.\n");


    if (WSAStartup(MAKEWORD(1,1), &wsaData))

        return 0;


    return 1;

}
