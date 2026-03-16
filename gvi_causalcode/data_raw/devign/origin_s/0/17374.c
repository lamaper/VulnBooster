static int av_encode(AVFormatContext **output_files,

                     int nb_output_files,

                     AVFormatContext **input_files,

                     int nb_input_files,

                     AVStreamMap *stream_maps, int nb_stream_maps)

{

    int ret, i, j, k, n, nb_istreams = 0, nb_ostreams = 0;

    AVFormatContext *is, *os;

    AVCodecContext *codec, *icodec;

    AVOutputStream *ost, **ost_table = NULL;

    AVInputStream *ist, **ist_table = NULL;

    AVInputFile *file_table;

    AVFormatContext *stream_no_data;

    int key;



    file_table= (AVInputFile*) av_mallocz(nb_input_files * sizeof(AVInputFile));

    if (!file_table)

        goto fail;



     

    j = 0;

    for(i=0;i<nb_input_files;i++) {

        is = input_files[i];

        file_table[i].ist_index = j;

        file_table[i].nb_streams = is->nb_streams;

        j += is->nb_streams;

    }

    nb_istreams = j;



    ist_table = av_mallocz(nb_istreams * sizeof(AVInputStream *));

    if (!ist_table)

        goto fail;

    

    for(i=0;i<nb_istreams;i++) {

        ist = av_mallocz(sizeof(AVInputStream));

        if (!ist)

            goto fail;

        ist_table[i] = ist;

    }

    j = 0;

    for(i=0;i<nb_input_files;i++) {

        is = input_files[i];

        for(k=0;k<is->nb_streams;k++) {

            ist = ist_table[j++];

            ist->st = is->streams[k];

            ist->file_index = i;

            ist->index = k;

            ist->discard = 1;  



            if (ist->st->codec.rate_emu) {

                ist->start = av_gettime();

                ist->frame = 0;

            }

        }

    }



     

    nb_ostreams = 0;

    for(i=0;i<nb_output_files;i++) {

        os = output_files[i];

        nb_ostreams += os->nb_streams;

    }

    if (nb_stream_maps > 0 && nb_stream_maps != nb_ostreams) {

        fprintf(stderr, "Number of stream maps must match number of output streams\n");

        exit(1);

    }



     

    for(i=0;i<nb_stream_maps;i++) {

        int fi = stream_maps[i].file_index;

        int si = stream_maps[i].stream_index;

        

        if (fi < 0 || fi > nb_input_files - 1 ||

            si < 0 || si > file_table[fi].nb_streams - 1) {

            fprintf(stderr,"Could not find input stream #%d.%d\n", fi, si);

            exit(1);

        }

    }

    

    ost_table = av_mallocz(sizeof(AVOutputStream *) * nb_ostreams);

    if (!ost_table)

        goto fail;

    for(i=0;i<nb_ostreams;i++) {

        ost = av_mallocz(sizeof(AVOutputStream));

        if (!ost)

            goto fail;

        ost_table[i] = ost;

    }

    

    n = 0;

    for(k=0;k<nb_output_files;k++) {

        os = output_files[k];

        for(i=0;i<os->nb_streams;i++) {

            int found;

            ost = ost_table[n++];

            ost->file_index = k;

            ost->index = i;

            ost->st = os->streams[i];

            if (nb_stream_maps > 0) {

                ost->source_index = file_table[stream_maps[n-1].file_index].ist_index + 

                    stream_maps[n-1].stream_index;

                    

                 

                if (ist_table[ost->source_index]->st->codec.codec_type != ost->st->codec.codec_type) {

                    fprintf(stderr, "Codec type mismatch for mapping #%d.%d -> #%d.%d\n",

                        stream_maps[n-1].file_index, stream_maps[n-1].stream_index,

                        ost->file_index, ost->index);

                    exit(1);

                }

                

            } else {

                 

                found = 0;

                for(j=0;j<nb_istreams;j++) {

                    ist = ist_table[j];

                    if (ist->discard && 

                        ist->st->codec.codec_type == ost->st->codec.codec_type) {

                        ost->source_index = j;

                        found = 1;

                    }

                }

                

                if (!found) {

                     

                    for(j=0;j<nb_istreams;j++) {

                        ist = ist_table[j];

                        if (ist->st->codec.codec_type == ost->st->codec.codec_type) {

                            ost->source_index = j;

                            found = 1;

                        }

                    }

                    if (!found) {

                        fprintf(stderr, "Could not find input stream matching output stream #%d.%d\n",

                                ost->file_index, ost->index);

                        exit(1);

                    }

                }

            }

            ist = ist_table[ost->source_index];

            ist->discard = 0;

        }

    }



     

    for(i=0;i<nb_ostreams;i++) {

        ost = ost_table[i];

        ist = ist_table[ost->source_index];



        codec = &ost->st->codec;

        icodec = &ist->st->codec;



        if (ost->st->stream_copy) {

             

            codec->codec_id = icodec->codec_id;

            codec->codec_type = icodec->codec_type;

            codec->codec_tag = icodec->codec_tag;

            codec->bit_rate = icodec->bit_rate;

            switch(codec->codec_type) {

            case CODEC_TYPE_AUDIO:

                codec->sample_rate = icodec->sample_rate;

                codec->channels = icodec->channels;

                break;

            case CODEC_TYPE_VIDEO:

                codec->frame_rate = icodec->frame_rate;

                codec->frame_rate_base = icodec->frame_rate_base;

                codec->width = icodec->width;

                codec->height = icodec->height;

                break;

            default:

                av_abort();

            }

        } else {

            switch(codec->codec_type) {

            case CODEC_TYPE_AUDIO:

                if (fifo_init(&ost->fifo, 2 * MAX_AUDIO_PACKET_SIZE))

                    goto fail;

                

                if (codec->channels == icodec->channels &&

                    codec->sample_rate == icodec->sample_rate) {

                    ost->audio_resample = 0;

                } else {

                    if (codec->channels != icodec->channels &&

                        icodec->codec_id == CODEC_ID_AC3) {

                         

                         

                         

                        icodec->channels = codec->channels;

                        if (codec->sample_rate == icodec->sample_rate)

                            ost->audio_resample = 0;

                        else {

                            ost->audio_resample = 1;

                            ost->resample = audio_resample_init(codec->channels, icodec->channels,

                                                        codec->sample_rate, 

                                                        icodec->sample_rate);

			    if(!ost->resample)

			      {

				printf("Can't resample.  Aborting.\n");

				av_abort();

			      }

                        }

                         

                        icodec->channels = codec->channels;

                    } else {

                        ost->audio_resample = 1; 

                        ost->resample = audio_resample_init(codec->channels, icodec->channels,

                                                        codec->sample_rate, 

                                                        icodec->sample_rate);

			if(!ost->resample)

			  {

			    printf("Can't resample.  Aborting.\n");

			    av_abort();

			  }

                    }

                }

                ist->decoding_needed = 1;

                ost->encoding_needed = 1;

                break;

            case CODEC_TYPE_VIDEO:

                if (codec->width == icodec->width &&

                    codec->height == icodec->height &&

                    frame_topBand == 0 &&

                    frame_bottomBand == 0 &&

                    frame_leftBand == 0 &&

                    frame_rightBand == 0)

                {

                    ost->video_resample = 0;

                    ost->video_crop = 0;

                } else if ((codec->width == icodec->width -

                                (frame_leftBand + frame_rightBand)) &&

                        (codec->height == icodec->height -

                                (frame_topBand  + frame_bottomBand)))

                {

                    ost->video_resample = 0;

                    ost->video_crop = 1;

                    ost->topBand = frame_topBand;

                    ost->leftBand = frame_leftBand;

                } else {

                    ost->video_resample = 1;

                    ost->video_crop = 0;  

                    if( avpicture_alloc( &ost->pict_tmp, PIX_FMT_YUV420P,

                                         codec->width, codec->height ) )

                        goto fail;



                    ost->img_resample_ctx = img_resample_full_init( 

                                      ost->st->codec.width, ost->st->codec.height,

                                      ist->st->codec.width, ist->st->codec.height,

                                      frame_topBand, frame_bottomBand,

                                      frame_leftBand, frame_rightBand);

                }

                ost->encoding_needed = 1;

                ist->decoding_needed = 1;

                break;

            default:

                av_abort();

            }

             

            if (ost->encoding_needed && 

                (codec->flags & (CODEC_FLAG_PASS1 | CODEC_FLAG_PASS2))) {

                char logfilename[1024];

                FILE *f;

                int size;

                char *logbuffer;

                

                snprintf(logfilename, sizeof(logfilename), "%s-%d.log", 

                         pass_logfilename ? 

                         pass_logfilename : DEFAULT_PASS_LOGFILENAME, i);

                if (codec->flags & CODEC_FLAG_PASS1) {

                    f = fopen(logfilename, "w");

                    if (!f) {

                        perror(logfilename);

                        exit(1);

                    }

                    ost->logfile = f;

                } else {

                     

                    f = fopen(logfilename, "r");

                    if (!f) {

                        perror(logfilename);

                        exit(1);

                    }

                    fseek(f, 0, SEEK_END);

                    size = ftell(f);

                    fseek(f, 0, SEEK_SET);

                    logbuffer = av_malloc(size + 1);

                    if (!logbuffer) {

                        fprintf(stderr, "Could not allocate log buffer\n");

                        exit(1);

                    }

                    size = fread(logbuffer, 1, size, f);

                    fclose(f);

                    logbuffer[size] = '\0';

                    codec->stats_in = logbuffer;

                }

            }

        }

    }



     

    for(i=0;i<nb_output_files;i++) {

        dump_format(output_files[i], i, output_files[i]->filename, 1);

    }



     

    fprintf(stderr, "Stream mapping:\n");

    for(i=0;i<nb_ostreams;i++) {

        ost = ost_table[i];

        fprintf(stderr, "  Stream #%d.%d -> #%d.%d\n",

                ist_table[ost->source_index]->file_index,

                ist_table[ost->source_index]->index,

                ost->file_index, 

                ost->index);

    }



     

    for(i=0;i<nb_ostreams;i++) {

        ost = ost_table[i];

        if (ost->encoding_needed) {

            AVCodec *codec;

            codec = avcodec_find_encoder(ost->st->codec.codec_id);

            if (!codec) {

                fprintf(stderr, "Unsupported codec for output stream #%d.%d\n", 

                        ost->file_index, ost->index);

                exit(1);

            }

            if (avcodec_open(&ost->st->codec, codec) < 0) {

                fprintf(stderr, "Error while opening codec for stream #%d.%d - maybe incorrect parameters such as bit_rate, rate, width or height\n", 

                        ost->file_index, ost->index);

                exit(1);

            }

        }

    }



     

    for(i=0;i<nb_istreams;i++) {

        ist = ist_table[i];

        if (ist->decoding_needed) {

            AVCodec *codec;

            codec = avcodec_find_decoder(ist->st->codec.codec_id);

            if (!codec) {

                fprintf(stderr, "Unsupported codec (id=%d) for input stream #%d.%d\n", 

                        ist->st->codec.codec_id, ist->file_index, ist->index);

                exit(1);

            }

            if (avcodec_open(&ist->st->codec, codec) < 0) {

                fprintf(stderr, "Error while opening codec for input stream #%d.%d\n", 

                        ist->file_index, ist->index);

                exit(1);

            }

             

             

        }

    }



     

    for(i=0;i<nb_istreams;i++) {

        ist = ist_table[i];

	is = input_files[ist->file_index];

        ist->pts = 0;

        ist->next_pts = 0;

    }

    

     

    for(i=0;i<nb_input_files;i++) {

        file_table[i].buffer_size_max = 2048;

    }



     

    for(i=0;i<nb_output_files;i++) {

        os = output_files[i];

        if (av_write_header(os) < 0) {

            fprintf(stderr, "Could not write header for output file #%d (incorrect codec paramters ?)\n", i);

            ret = -EINVAL;

            goto fail;

        }

    }


    if ( !using_stdin )

        fprintf(stderr, "Press [q] to stop encoding\n");


    term_init();



    stream_no_data = 0;

    key = -1;



    for(; received_sigterm == 0;) {

        int file_index, ist_index;

        AVPacket pkt;

        double pts_min;

        

    redo:

         

        if (!using_stdin) {

             

            key = read_key();

            if (key == 'q')

                break;

        }



         

        file_index = -1;

        pts_min = 1e10;

        for(i=0;i<nb_ostreams;i++) {

            double pts;

            ost = ost_table[i];

            os = output_files[ost->file_index];

            ist = ist_table[ost->source_index];

            pts = (double)ost->st->pts.val * os->pts_num / os->pts_den;

            if (!file_table[ist->file_index].eof_reached && 

                pts < pts_min) {

                pts_min = pts;

                file_index = ist->file_index;

            }

        }

         

        if (file_index < 0) {

            break;

        }



         

        if (recording_time > 0 && pts_min >= (recording_time / 1000000.0))

            break;



         

        is = input_files[file_index];

        if (av_read_frame(is, &pkt) < 0) {

            file_table[file_index].eof_reached = 1;

            continue;

        }



        if (!pkt.size) {

            stream_no_data = is;

        } else {

            stream_no_data = 0;

        }

        if (do_pkt_dump) {

            av_pkt_dump(stdout, &pkt, do_hex_dump);

        }

         

        if (pkt.stream_index >= file_table[file_index].nb_streams)

            goto discard_packet;

        ist_index = file_table[file_index].ist_index + pkt.stream_index;

        ist = ist_table[ist_index];

        if (ist->discard)

            goto discard_packet;



         

        if (output_packet(ist, ist_index, ost_table, nb_ostreams, &pkt) < 0) {

            fprintf(stderr, "Error while decoding stream #%d.%d\n",

                    ist->file_index, ist->index);

            av_free_packet(&pkt);

            goto redo;

        }

        

    discard_packet:

        av_free_packet(&pkt);

        

         

        print_report(output_files, ost_table, nb_ostreams, 0);

    }



     

    for(i=0;i<nb_istreams;i++) {

        ist = ist_table[i];

        if (ist->decoding_needed) {

            output_packet(ist, i, ost_table, nb_ostreams, NULL);

        }

    }



    term_exit();



     

    print_report(output_files, ost_table, nb_ostreams, 1);



     

    for(i=0;i<nb_output_files;i++) {

        os = output_files[i];

        av_write_trailer(os);

    }



     

    for(i=0;i<nb_ostreams;i++) {

        ost = ost_table[i];

        if (ost->encoding_needed) {

            av_freep(&ost->st->codec.stats_in);

            avcodec_close(&ost->st->codec);

        }

    }

    

     

    for(i=0;i<nb_istreams;i++) {

        ist = ist_table[i];

        if (ist->decoding_needed) {

            avcodec_close(&ist->st->codec);

        }

    }



     

    

    ret = 0;

 fail1:

    av_free(file_table);



    if (ist_table) {

        for(i=0;i<nb_istreams;i++) {

            ist = ist_table[i];

            av_free(ist);

        }

        av_free(ist_table);

    }

    if (ost_table) {

        for(i=0;i<nb_ostreams;i++) {

            ost = ost_table[i];

            if (ost) {

                if (ost->logfile) {

                    fclose(ost->logfile);

                    ost->logfile = NULL;

                }

                fifo_free(&ost->fifo);  

                av_free(ost->pict_tmp.data[0]);

                if (ost->video_resample)

                    img_resample_close(ost->img_resample_ctx);

                if (ost->audio_resample)

                    audio_resample_close(ost->resample);

                av_free(ost);

            }

        }

        av_free(ost_table);

    }

    return ret;

 fail:

    ret = -ENOMEM;

    goto fail1;

}
