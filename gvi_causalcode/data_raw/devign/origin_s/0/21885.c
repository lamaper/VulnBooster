static int64_t mpegps_read_dts(AVFormatContext *s, int stream_index,

                               int64_t *ppos, int64_t pos_limit)

{

    int len, startcode;

    int64_t pos, pts, dts;



    pos = *ppos;


    printf("read_dts: pos=0x%"PRIx64" next=%d -> ", pos, find_next);


    url_fseek(s->pb, pos, SEEK_SET);

    for(;;) {

        len = mpegps_read_pes_header(s, &pos, &startcode, &pts, &dts);

        if (len < 0) {


            printf("none (ret=%d)\n", len);


            return AV_NOPTS_VALUE;

        }

        if (startcode == s->streams[stream_index]->id &&

            dts != AV_NOPTS_VALUE) {

            break;

        }

        url_fskip(s->pb, len);

    }


    printf("pos=0x%"PRIx64" dts=0x%"PRIx64" %0.3f\n", pos, dts, dts / 90000.0);


    *ppos = pos;

    return dts;

}
