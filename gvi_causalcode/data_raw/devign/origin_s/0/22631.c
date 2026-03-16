static int mov_read_stsd(MOVContext *c, ByteIOContext *pb, MOV_atom_t atom)

{

    AVStream *st = c->fc->streams[c->fc->nb_streams-1];

    MOVStreamContext *sc = st->priv_data;

    int j, entries, pseudo_stream_id;



    get_byte(pb);  

    get_be24(pb);  



    entries = get_be32(pb);



    for(pseudo_stream_id=0; pseudo_stream_id<entries; pseudo_stream_id++) {

         

        enum CodecID id;

        int dref_id;

        MOV_atom_t a = { 0, 0, 0 };

        offset_t start_pos = url_ftell(pb);

        int size = get_be32(pb);  

        uint32_t format = get_le32(pb);  



        get_be32(pb);  

        get_be16(pb);  

        dref_id = get_be16(pb);



        if (st->codec->codec_tag &&

            st->codec->codec_tag != format &&

            (c->fc->video_codec_id ? codec_get_id(codec_movvideo_tags, format) != c->fc->video_codec_id

                                   : st->codec->codec_tag != MKTAG('j','p','e','g'))

           ){

             

            av_log(c->fc, AV_LOG_WARNING, "multiple fourcc not supported\n");

            url_fskip(pb, size - (url_ftell(pb) - start_pos));

            continue;

        }

        sc->pseudo_stream_id = st->codec->codec_tag ? -1 : pseudo_stream_id;

        sc->dref_id= dref_id;



        st->codec->codec_tag = format;

        id = codec_get_id(codec_movaudio_tags, format);

        if (id<=0 && (format&0xFFFF) == 'm'+('s'<<8))

            id = codec_get_id(codec_wav_tags, bswap_32(format)&0xFFFF);



        if (st->codec->codec_type != CODEC_TYPE_VIDEO && id > 0) {

            st->codec->codec_type = CODEC_TYPE_AUDIO;

        } else if (st->codec->codec_type != CODEC_TYPE_AUDIO &&  

                   format && format != MKTAG('m','p','4','s')) {  

            id = codec_get_id(codec_movvideo_tags, format);

            if (id <= 0)

                id = codec_get_id(codec_bmp_tags, format);

            if (id > 0)

                st->codec->codec_type = CODEC_TYPE_VIDEO;

            else if(st->codec->codec_type == CODEC_TYPE_DATA){

                id = codec_get_id(ff_codec_movsubtitle_tags, format);

                if(id > 0)

                    st->codec->codec_type = CODEC_TYPE_SUBTITLE;

            }

        }



        dprintf(c->fc, "size=%d 4CC= %c%c%c%c codec_type=%d\n", size,

                (format >> 0) & 0xff, (format >> 8) & 0xff, (format >> 16) & 0xff,

                (format >> 24) & 0xff, st->codec->codec_type);



        if(st->codec->codec_type==CODEC_TYPE_VIDEO) {

            uint8_t codec_name[32];

            unsigned int color_depth;

            int color_greyscale;



            st->codec->codec_id = id;

            get_be16(pb);  

            get_be16(pb);  

            get_be32(pb);  

            get_be32(pb);  

            get_be32(pb);  



            st->codec->width = get_be16(pb);  

            st->codec->height = get_be16(pb);  



            get_be32(pb);  

            get_be32(pb);  

            get_be32(pb);  

            get_be16(pb);  



            get_buffer(pb, codec_name, 32);  

            if (codec_name[0] <= 31) {

                memcpy(st->codec->codec_name, &codec_name[1],codec_name[0]);

                st->codec->codec_name[codec_name[0]] = 0;

            }



            st->codec->bits_per_coded_sample = get_be16(pb);  

            st->codec->color_table_id = get_be16(pb);  

            dprintf(c->fc, "depth %d, ctab id %d\n",

                   st->codec->bits_per_coded_sample, st->codec->color_table_id);

             

            color_depth = st->codec->bits_per_coded_sample & 0x1F;

            color_greyscale = st->codec->bits_per_coded_sample & 0x20;



             

            if ((color_depth == 2) || (color_depth == 4) ||

                (color_depth == 8)) {

                 

                unsigned int color_start, color_count, color_end;

                unsigned char r, g, b;



                if (color_greyscale) {

                    int color_index, color_dec;

                     

                    st->codec->bits_per_coded_sample = color_depth;

                    color_count = 1 << color_depth;

                    color_index = 255;

                    color_dec = 256 / (color_count - 1);

                    for (j = 0; j < color_count; j++) {

                        r = g = b = color_index;

                        c->palette_control.palette[j] =

                            (r << 16) | (g << 8) | (b);

                        color_index -= color_dec;

                        if (color_index < 0)

                            color_index = 0;

                    }

                } else if (st->codec->color_table_id) {

                    const uint8_t *color_table;

                     

                    color_count = 1 << color_depth;

                    if (color_depth == 2)

                        color_table = ff_qt_default_palette_4;

                    else if (color_depth == 4)

                        color_table = ff_qt_default_palette_16;

                    else

                        color_table = ff_qt_default_palette_256;



                    for (j = 0; j < color_count; j++) {

                        r = color_table[j * 4 + 0];

                        g = color_table[j * 4 + 1];

                        b = color_table[j * 4 + 2];

                        c->palette_control.palette[j] =

                            (r << 16) | (g << 8) | (b);

                    }

                } else {

                     

                    color_start = get_be32(pb);

                    color_count = get_be16(pb);

                    color_end = get_be16(pb);

                    if ((color_start <= 255) &&

                        (color_end <= 255)) {

                        for (j = color_start; j <= color_end; j++) {

                             

                            get_byte(pb);

                            get_byte(pb);

                            r = get_byte(pb);

                            get_byte(pb);

                            g = get_byte(pb);

                            get_byte(pb);

                            b = get_byte(pb);

                            get_byte(pb);

                            c->palette_control.palette[j] =

                                (r << 16) | (g << 8) | (b);

                        }

                    }

                }

                st->codec->palctrl = &c->palette_control;

                st->codec->palctrl->palette_changed = 1;

            } else

                st->codec->palctrl = NULL;

        } else if(st->codec->codec_type==CODEC_TYPE_AUDIO) {

            int bits_per_sample, flags;

            uint16_t version = get_be16(pb);



            st->codec->codec_id = id;

            get_be16(pb);  

            get_be32(pb);  



            st->codec->channels = get_be16(pb);              

            dprintf(c->fc, "audio channels %d\n", st->codec->channels);

            st->codec->bits_per_coded_sample = get_be16(pb);       



            sc->audio_cid = get_be16(pb);

            get_be16(pb);  



            st->codec->sample_rate = ((get_be32(pb) >> 16));



             

            dprintf(c->fc, "version =%d, isom =%d\n",version,c->isom);

            if(!c->isom) {

                if(version==1) {

                    sc->samples_per_frame = get_be32(pb);

                    get_be32(pb);  

                    sc->bytes_per_frame = get_be32(pb);

                    get_be32(pb);  

                } else if(version==2) {

                    get_be32(pb);  

                    st->codec->sample_rate = av_int2dbl(get_be64(pb));  

                    st->codec->channels = get_be32(pb);

                    get_be32(pb);  

                    st->codec->bits_per_coded_sample = get_be32(pb);  

                    flags = get_be32(pb);  

                    sc->bytes_per_frame = get_be32(pb);  

                    sc->samples_per_frame = get_be32(pb);  

                    if (format == MKTAG('l','p','c','m'))

                        st->codec->codec_id = mov_get_lpcm_codec_id(st->codec->bits_per_coded_sample, flags);

                }

            }



            switch (st->codec->codec_id) {

            case CODEC_ID_PCM_S8:

            case CODEC_ID_PCM_U8:

                if (st->codec->bits_per_coded_sample == 16)

                    st->codec->codec_id = CODEC_ID_PCM_S16BE;

                break;

            case CODEC_ID_PCM_S16LE:

            case CODEC_ID_PCM_S16BE:

                if (st->codec->bits_per_coded_sample == 8)

                    st->codec->codec_id = CODEC_ID_PCM_S8;

                else if (st->codec->bits_per_coded_sample == 24)

                    st->codec->codec_id =

                        st->codec->codec_id == CODEC_ID_PCM_S16BE ?

                        CODEC_ID_PCM_S24BE : CODEC_ID_PCM_S24LE;

                break;

             

            case CODEC_ID_MACE3:

                sc->samples_per_frame = 6;

                sc->bytes_per_frame = 2*st->codec->channels;

                break;

            case CODEC_ID_MACE6:

                sc->samples_per_frame = 6;

                sc->bytes_per_frame = 1*st->codec->channels;

                break;

            case CODEC_ID_ADPCM_IMA_QT:

                sc->samples_per_frame = 64;

                sc->bytes_per_frame = 34*st->codec->channels;

                break;

            case CODEC_ID_GSM:

                sc->samples_per_frame = 160;

                sc->bytes_per_frame = 33;

                break;

            default:

                break;

            }



            bits_per_sample = av_get_bits_per_sample(st->codec->codec_id);

            if (bits_per_sample) {

                st->codec->bits_per_coded_sample = bits_per_sample;

                sc->sample_size = (bits_per_sample >> 3) * st->codec->channels;

            }

        } else if(st->codec->codec_type==CODEC_TYPE_SUBTITLE){

            st->codec->codec_id= id;

        } else {

             

            url_fskip(pb, size - (url_ftell(pb) - start_pos));

        }

         

        a.size = size - (url_ftell(pb) - start_pos);

        if (a.size > 8) {

            if (mov_read_default(c, pb, a) < 0)

                return -1;

        } else if (a.size > 0)

            url_fskip(pb, a.size);

    }



    if(st->codec->codec_type==CODEC_TYPE_AUDIO && st->codec->sample_rate==0 && sc->time_scale>1)

        st->codec->sample_rate= sc->time_scale;



     

    switch (st->codec->codec_id) {


    case CODEC_ID_DVAUDIO:

        c->dv_fctx = av_alloc_format_context();

        c->dv_demux = dv_init_demux(c->dv_fctx);

        if (!c->dv_demux) {

            av_log(c->fc, AV_LOG_ERROR, "dv demux context init error\n");

            return -1;

        }

        sc->dv_audio_container = 1;

        st->codec->codec_id = CODEC_ID_PCM_S16LE;

        break;


     

    case CODEC_ID_AMR_WB:

        st->codec->sample_rate= 16000;

        st->codec->channels= 1;  

        break;

    case CODEC_ID_QCELP:

    case CODEC_ID_AMR_NB:

        st->codec->frame_size= sc->samples_per_frame;

        st->codec->sample_rate= 8000;

        st->codec->channels= 1;  

        break;

    case CODEC_ID_MP2:

    case CODEC_ID_MP3:

        st->codec->codec_type = CODEC_TYPE_AUDIO;  

        st->need_parsing = AVSTREAM_PARSE_FULL;

        break;

    case CODEC_ID_GSM:

    case CODEC_ID_ADPCM_MS:

    case CODEC_ID_ADPCM_IMA_WAV:

        st->codec->block_align = sc->bytes_per_frame;

        break;

    case CODEC_ID_ALAC:

        if (st->codec->extradata_size == 36)

            st->codec->frame_size = AV_RB32((st->codec->extradata+12));

        break;

    default:

        break;

    }



    return 0;

}
