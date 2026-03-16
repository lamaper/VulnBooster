static int net_host_check_device(const char *device)

{

    int i;

    const char *valid_param_list[] = { "tap", "socket", "dump"


                                       , "bridge"



                                       ,"user"



                                       ,"vde"


    };

    for (i = 0; i < ARRAY_SIZE(valid_param_list); i++) {

        if (!strncmp(valid_param_list[i], device,

                     strlen(valid_param_list[i])))

            return 1;

    }



    return 0;

}
