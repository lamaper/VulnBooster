static int file_open_dir(URLContext *h)

{


    FileContext *c = h->priv_data;



    c->dir = opendir(h->filename);

    if (!c->dir)

        return AVERROR(errno);



    return 0;


    return AVERROR(ENOSYS);


}
