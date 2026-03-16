static int file_close_dir(URLContext *h)

{


    FileContext *c = h->priv_data;

    closedir(c->dir);

    return 0;


    return AVERROR(ENOSYS);


}
