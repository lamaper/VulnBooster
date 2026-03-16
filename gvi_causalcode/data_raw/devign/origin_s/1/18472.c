int av_tempfile(const char *prefix, char **filename, int log_offset, void *log_ctx) {

    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };

    int fd=-1;


    void *ptr= tempnam(NULL, prefix);

    if(!ptr)

        ptr= tempnam(".", prefix);

    *filename = av_strdup(ptr);


    free(ptr);


    size_t len = strlen(prefix) + 12;  

    *filename = av_malloc(len);


     

    if (*filename == NULL) {

        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");

        return AVERROR(ENOMEM);

    }








    fd = open(*filename, O_RDWR | O_BINARY | O_CREAT | O_EXCL, 0600);


    snprintf(*filename, len, "/tmp/%sXXXXXX", prefix);

    fd = mkstemp(*filename);


    if (fd < 0) {

        snprintf(*filename, len, "./%sXXXXXX", prefix);

        fd = mkstemp(*filename);

    }



     

    if (fd < 0) {

        int err = AVERROR(errno);

        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);


        return err;

    }

    return fd;  

}