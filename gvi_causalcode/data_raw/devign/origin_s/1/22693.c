void trace_init_file(const char *file)

{


    st_set_trace_file(file);


     

    if (file) {

        qemu_set_log_filename(file);

    }


    if (file) {

        fprintf(stderr, "error: -trace file=...: "

                "option not supported by the selected tracing backends\n");

        exit(1);

    }


}
