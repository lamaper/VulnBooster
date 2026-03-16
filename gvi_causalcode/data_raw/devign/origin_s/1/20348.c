static void cd_read_sector_cb(void *opaque, int ret)

{

    IDEState *s = opaque;



    block_acct_done(blk_get_stats(s->blk), &s->acct);


    printf("cd_read_sector_cb: lba=%d ret=%d\n", s->lba, ret);




    if (ret < 0) {

        ide_atapi_io_error(s, ret);

        return;

    }



    if (s->cd_sector_size == 2352) {

        cd_data_to_raw(s->io_buffer, s->lba);

    }



    s->lba++;

    s->io_buffer_index = 0;

    s->status &= ~BUSY_STAT;



    ide_atapi_cmd_reply_end(s);

}
