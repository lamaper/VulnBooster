static void term_handle_command(char *cmdline)

{

    char *p, *pstart;

    int argc;

    const char *args[MAX_ARGS + 1];

    term_cmd_t *cmd;


    term_printf("command='%s'\n", cmdline);


    

     

    argc = 0;

    p = cmdline;

    for(;;) {

        while (isspace(*p))

            p++;

        if (*p == '\0')

            break;

        pstart = p;

        while (*p != '\0' && !isspace(*p))

            p++;

        args[argc] = pstart;

        argc++;

        if (argc >= MAX_ARGS)

            break;

        if (*p == '\0')

            break;

        *p++ = '\0';

    }

    args[argc] = NULL;


    for(i=0;i<argc;i++) {

        term_printf(" '%s'", args[i]);

    }

    term_printf("\n");


    if (argc <= 0)

        return;

    for(cmd = term_cmds; cmd->name != NULL; cmd++) {

        if (compare_cmd(args[0], cmd->name)) 

            goto found;

    }

    term_printf("unknown command: '%s'\n", args[0]);

    return;

 found:

    cmd->handler(argc, args);

}
