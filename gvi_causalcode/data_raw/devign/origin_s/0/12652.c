void list_cpus(FILE *f, int (*cpu_fprintf)(FILE *f, const char *fmt, ...),

               const char *optarg)

{


    cpu_list_id(f, cpu_fprintf, optarg);


    cpu_list(f, cpu_fprintf);  


}
