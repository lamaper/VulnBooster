static void handle_arg_cpu(const char *arg)

{

    cpu_model = strdup(arg);

    if (cpu_model == NULL || strcmp(cpu_model, "?") == 0) {


        cpu_list_id(stdout, &fprintf, "");


        cpu_list(stdout, &fprintf);  


        exit(1);

    }

}
