static void ffm_seek1(AVFormatContext *s, int64_t pos1)

{

    FFMContext *ffm = s->priv_data;

    ByteIOContext *pb = s->pb;

    int64_t pos;



    pos = pos1 + ffm->write_index;

    if (pos >= ffm->file_size)

        pos -= (ffm->file_size - FFM_PACKET_SIZE);


    av_log(s, AV_LOG_DEBUG, "seek to %"PRIx64" -> %"PRIx64"\n", pos1, pos);


    url_fseek(pb, pos, SEEK_SET);

}
