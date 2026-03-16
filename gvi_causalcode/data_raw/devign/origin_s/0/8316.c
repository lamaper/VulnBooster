int ff_tempfile(const char *prefix, char **filename) {

    int fd=-1;


    *filename = tempnam(".", prefix);


    size_t len = strlen(prefix) + 12;  

    *filename = av_malloc(len);


     

    if (*filename == NULL) {

        av_log(NULL, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");

        return -1;

    }


    fd = avpriv_open(*filename, O_RDWR | O_BINARY | O_CREAT, 0444);


    snprintf(*filename, len, "/tmp/%sXXXXXX", prefix);

    fd = mkstemp(*filename);

    if (fd < 0) {

        snprintf(*filename, len, "./%sXXXXXX", prefix);

        fd = mkstemp(*filename);

    }


     

    if (fd < 0) {

        av_log(NULL, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);

        return -1;

    }

    return fd;  

}
