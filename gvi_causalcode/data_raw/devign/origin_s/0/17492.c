int show_filters(void *optctx, const char *opt, const char *arg)

{

    AVFilter av_unused(**filter) = NULL;



    printf("Filters:\n");


    while ((filter = av_filter_next(filter)) && *filter)

        printf("%-16s %s\n", (*filter)->name, (*filter)->description);


    return 0;

}
