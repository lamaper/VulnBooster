static av_cold int xvid_encode_init(AVCodecContext *avctx)

{

    int xerr, i, ret = -1;

    int xvid_flags = avctx->flags;

    struct xvid_context *x = avctx->priv_data;

    uint16_t *intra, *inter;

    int fd;



    xvid_plugin_single_t      single          = { 0 };

    struct xvid_ff_pass1      rc2pass1        = { 0 };

    xvid_plugin_2pass2_t      rc2pass2        = { 0 };

    xvid_plugin_lumimasking_t masking_l       = { 0 };  

    xvid_plugin_lumimasking_t masking_v       = { 0 };  

    xvid_plugin_ssim_t        ssim            = { 0 };

    xvid_gbl_init_t           xvid_gbl_init   = { 0 };

    xvid_enc_create_t         xvid_enc_create = { 0 };

    xvid_enc_plugin_t         plugins[4];



    x->twopassfd = -1;



     

    x->vop_flags = XVID_VOP_HALFPEL;               

    if (xvid_flags & AV_CODEC_FLAG_4MV)

        x->vop_flags    |= XVID_VOP_INTER4V;       

    if (avctx->trellis)

        x->vop_flags    |= XVID_VOP_TRELLISQUANT;  

    if (xvid_flags & AV_CODEC_FLAG_AC_PRED)

        x->vop_flags    |= XVID_VOP_HQACPRED;      

    if (xvid_flags & AV_CODEC_FLAG_GRAY)

        x->vop_flags    |= XVID_VOP_GREYSCALE;



     

    x->me_flags = 0;

    switch (x->me_quality) {

    case 6:

    case 5:

        x->me_flags |= XVID_ME_EXTSEARCH16 |

                       XVID_ME_EXTSEARCH8;

    case 4:

    case 3:

        x->me_flags |= XVID_ME_ADVANCEDDIAMOND8 |

                       XVID_ME_HALFPELREFINE8   |

                       XVID_ME_CHROMA_PVOP      |

                       XVID_ME_CHROMA_BVOP;

    case 2:

    case 1:

        x->me_flags |= XVID_ME_ADVANCEDDIAMOND16 |

                       XVID_ME_HALFPELREFINE16;


FF_DISABLE_DEPRECATION_WARNINGS

        break;

    default:

        switch (avctx->me_method) {

        case ME_FULL:    

             x->me_flags |= XVID_ME_EXTSEARCH16 |

                            XVID_ME_EXTSEARCH8;

        case ME_EPZS:    

             x->me_flags |= XVID_ME_ADVANCEDDIAMOND8 |

                            XVID_ME_HALFPELREFINE8   |

                            XVID_ME_CHROMA_PVOP      |

                            XVID_ME_CHROMA_BVOP;

        case ME_LOG:     

        case ME_PHODS:

        case ME_X1:

             x->me_flags |= XVID_ME_ADVANCEDDIAMOND16 |

                            XVID_ME_HALFPELREFINE16;

        case ME_ZERO:    

        default:

            break;

        }

FF_ENABLE_DEPRECATION_WARNINGS


    }



     

    switch (avctx->mb_decision) {

    case 2:

        x->vop_flags |=  XVID_VOP_MODEDECISION_RD;

        x->me_flags  |=  XVID_ME_HALFPELREFINE8_RD    |

                         XVID_ME_QUARTERPELREFINE8_RD |

                         XVID_ME_EXTSEARCH_RD         |

                         XVID_ME_CHECKPREDICTION_RD;

    case 1:

        if (!(x->vop_flags & XVID_VOP_MODEDECISION_RD))

            x->vop_flags |= XVID_VOP_FAST_MODEDECISION_RD;

        x->me_flags |= XVID_ME_HALFPELREFINE16_RD |

                       XVID_ME_QUARTERPELREFINE16_RD;

    default:

        break;

    }


    if (avctx->flags & CODEC_FLAG_GMC)

        x->gmc = 1;




    x->vol_flags = 0;

    if (x->gmc) {

        x->vol_flags |= XVID_VOL_GMC;

        x->me_flags  |= XVID_ME_GME_REFINE;

    }

    if (xvid_flags & AV_CODEC_FLAG_QPEL) {

        x->vol_flags |= XVID_VOL_QUARTERPEL;

        x->me_flags  |= XVID_ME_QUARTERPELREFINE16;

        if (x->vop_flags & XVID_VOP_INTER4V)

            x->me_flags |= XVID_ME_QUARTERPELREFINE8;

    }



    xvid_gbl_init.version   = XVID_VERSION;

    xvid_gbl_init.debug     = 0;

    xvid_gbl_init.cpu_flags = 0;



     

    xvid_global(NULL, XVID_GBL_INIT, &xvid_gbl_init, NULL);



     

    xvid_enc_create.version = XVID_VERSION;



     

    xvid_enc_create.width  =

    x->xsize               = avctx->width;

    xvid_enc_create.height =

    x->ysize               = avctx->height;



     

     



     

    xvid_enc_create.zones     = NULL;

    xvid_enc_create.num_zones = 0;



    xvid_enc_create.num_threads = avctx->thread_count;


     

    if (avctx->height <= 16) {

        if (avctx->thread_count < 2) {

            xvid_enc_create.num_threads = 0;

        } else {

            av_log(avctx, AV_LOG_ERROR,

                   "Too small height for threads > 1.");

            return AVERROR(EINVAL);

        }

    }




    xvid_enc_create.plugins     = plugins;

    xvid_enc_create.num_plugins = 0;



     

    x->twopassbuffer     = NULL;

    x->old_twopassbuffer = NULL;

    x->twopassfile       = NULL;



    if (xvid_flags & AV_CODEC_FLAG_PASS1) {

        rc2pass1.version     = XVID_VERSION;

        rc2pass1.context     = x;

        x->twopassbuffer     = av_malloc(BUFFER_SIZE);

        x->old_twopassbuffer = av_malloc(BUFFER_SIZE);

        if (!x->twopassbuffer || !x->old_twopassbuffer) {

            av_log(avctx, AV_LOG_ERROR,

                   "Xvid: Cannot allocate 2-pass log buffers\n");

            return AVERROR(ENOMEM);

        }

        x->twopassbuffer[0]     =

        x->old_twopassbuffer[0] = 0;



        plugins[xvid_enc_create.num_plugins].func  = xvid_ff_2pass;

        plugins[xvid_enc_create.num_plugins].param = &rc2pass1;

        xvid_enc_create.num_plugins++;

    } else if (xvid_flags & AV_CODEC_FLAG_PASS2) {

        rc2pass2.version = XVID_VERSION;

        rc2pass2.bitrate = avctx->bit_rate;



        fd = avpriv_tempfile("xvidff.", &x->twopassfile, 0, avctx);

        if (fd < 0) {

            av_log(avctx, AV_LOG_ERROR, "Xvid: Cannot write 2-pass pipe\n");

            return fd;

        }

        x->twopassfd = fd;



        if (!avctx->stats_in) {

            av_log(avctx, AV_LOG_ERROR,

                   "Xvid: No 2-pass information loaded for second pass\n");

            return AVERROR(EINVAL);

        }



        ret = write(fd, avctx->stats_in, strlen(avctx->stats_in));

        if (ret == -1)

            ret = AVERROR(errno);

        else if (strlen(avctx->stats_in) > ret) {

            av_log(avctx, AV_LOG_ERROR, "Xvid: Cannot write to 2-pass pipe\n");

            ret = AVERROR(EIO);

        }

        if (ret < 0)

            return ret;



        rc2pass2.filename                          = x->twopassfile;

        plugins[xvid_enc_create.num_plugins].func  = xvid_plugin_2pass2;

        plugins[xvid_enc_create.num_plugins].param = &rc2pass2;

        xvid_enc_create.num_plugins++;

    } else if (!(xvid_flags & AV_CODEC_FLAG_QSCALE)) {

         

        single.version = XVID_VERSION;

        single.bitrate = avctx->bit_rate;



        plugins[xvid_enc_create.num_plugins].func  = xvid_plugin_single;

        plugins[xvid_enc_create.num_plugins].param = &single;

        xvid_enc_create.num_plugins++;

    }



    if (avctx->lumi_masking != 0.0)

        x->lumi_aq = 1;



     

    if (x->lumi_aq) {

        masking_l.method                          = 0;

        plugins[xvid_enc_create.num_plugins].func = xvid_plugin_lumimasking;



         

        plugins[xvid_enc_create.num_plugins].param =

            avctx->lumi_masking ? NULL : &masking_l;

        xvid_enc_create.num_plugins++;

    }



     

    if (x->variance_aq) {

        masking_v.method                           = 1;

        plugins[xvid_enc_create.num_plugins].func  = xvid_plugin_lumimasking;

        plugins[xvid_enc_create.num_plugins].param = &masking_v;

        xvid_enc_create.num_plugins++;

    }



    if (x->lumi_aq && x->variance_aq )

        av_log(avctx, AV_LOG_INFO,

               "Both lumi_aq and variance_aq are enabled. The resulting quality"

               "will be the worse one of the two effects made by the AQ.\n");



     

    if (x->ssim) {

        plugins[xvid_enc_create.num_plugins].func  = xvid_plugin_ssim;

        ssim.b_printstat                           = x->ssim == 2;

        ssim.acc                                   = x->ssim_acc;

        ssim.cpu_flags                             = xvid_gbl_init.cpu_flags;

        ssim.b_visualize                           = 0;

        plugins[xvid_enc_create.num_plugins].param = &ssim;

        xvid_enc_create.num_plugins++;

    }



     

    xvid_correct_framerate(avctx);

    xvid_enc_create.fincr = avctx->time_base.num;

    xvid_enc_create.fbase = avctx->time_base.den;

    if (avctx->gop_size > 0)

        xvid_enc_create.max_key_interval = avctx->gop_size;

    else

        xvid_enc_create.max_key_interval = 240;  



     

    if (xvid_flags & AV_CODEC_FLAG_QSCALE)

        x->qscale = 1;

    else

        x->qscale = 0;



    xvid_enc_create.min_quant[0] = avctx->qmin;

    xvid_enc_create.min_quant[1] = avctx->qmin;

    xvid_enc_create.min_quant[2] = avctx->qmin;

    xvid_enc_create.max_quant[0] = avctx->qmax;

    xvid_enc_create.max_quant[1] = avctx->qmax;

    xvid_enc_create.max_quant[2] = avctx->qmax;



     

    x->intra_matrix =

    x->inter_matrix = NULL;


FF_DISABLE_DEPRECATION_WARNINGS

    if (avctx->mpeg_quant)

        x->mpeg_quant = avctx->mpeg_quant;

FF_ENABLE_DEPRECATION_WARNINGS




    if (x->mpeg_quant)

        x->vol_flags |= XVID_VOL_MPEGQUANT;

    if ((avctx->intra_matrix || avctx->inter_matrix)) {

        x->vol_flags |= XVID_VOL_MPEGQUANT;



        if (avctx->intra_matrix) {

            intra           = avctx->intra_matrix;

            x->intra_matrix = av_malloc(sizeof(unsigned char) * 64);

            if (!x->intra_matrix)

                return AVERROR(ENOMEM);

        } else

            intra = NULL;

        if (avctx->inter_matrix) {

            inter           = avctx->inter_matrix;

            x->inter_matrix = av_malloc(sizeof(unsigned char) * 64);

            if (!x->inter_matrix)

                return AVERROR(ENOMEM);

        } else

            inter = NULL;



        for (i = 0; i < 64; i++) {

            if (intra)

                x->intra_matrix[i] = (unsigned char) intra[i];

            if (inter)

                x->inter_matrix[i] = (unsigned char) inter[i];

        }

    }



     

    xvid_enc_create.frame_drop_ratio = 0;

    xvid_enc_create.global           = 0;

    if (xvid_flags & AV_CODEC_FLAG_CLOSED_GOP)

        xvid_enc_create.global |= XVID_GLOBAL_CLOSED_GOP;



     

    avctx->extradata      = NULL;

    avctx->extradata_size = 0;

    if (xvid_flags & AV_CODEC_FLAG_GLOBAL_HEADER) {

         

        x->quicktime_format = 1;

        avctx->codec_id     = AV_CODEC_ID_MPEG4;

    } else {

         

        x->quicktime_format = 0;

        if (!avctx->codec_tag)

            avctx->codec_tag = AV_RL32("xvid");

    }



     

    xvid_enc_create.max_bframes   = avctx->max_b_frames;

    xvid_enc_create.bquant_offset = 100 * avctx->b_quant_offset;

    xvid_enc_create.bquant_ratio  = 100 * avctx->b_quant_factor;

    if (avctx->max_b_frames > 0 && !x->quicktime_format)

        xvid_enc_create.global |= XVID_GLOBAL_PACKED;



    av_assert0(xvid_enc_create.num_plugins + (!!x->ssim) + (!!x->variance_aq) + (!!x->lumi_aq) <= FF_ARRAY_ELEMS(plugins));



     

    if (x->quicktime_format) {

        AVFrame *picture;

        AVPacket packet;

        int size, got_packet, ret;



        av_init_packet(&packet);



        picture = av_frame_alloc();

        if (!picture)

            return AVERROR(ENOMEM);



        xerr = xvid_encore(NULL, XVID_ENC_CREATE, &xvid_enc_create, NULL);

        if( xerr ) {

            av_frame_free(&picture);

            av_log(avctx, AV_LOG_ERROR, "Xvid: Could not create encoder reference\n");

            return AVERROR_EXTERNAL;

        }

        x->encoder_handle = xvid_enc_create.handle;

        size = ((avctx->width + 1) & ~1) * ((avctx->height + 1) & ~1);

        picture->data[0] = av_malloc(size + size / 2);

        if (!picture->data[0]) {

            av_frame_free(&picture);

            return AVERROR(ENOMEM);

        }

        picture->data[1] = picture->data[0] + size;

        picture->data[2] = picture->data[1] + size / 4;

        memset(picture->data[0], 0, size);

        memset(picture->data[1], 128, size / 2);

        ret = xvid_encode_frame(avctx, &packet, picture, &got_packet);

        if (!ret && got_packet)

            av_packet_unref(&packet);

        av_free(picture->data[0]);

        av_frame_free(&picture);

        xvid_encore(x->encoder_handle, XVID_ENC_DESTROY, NULL, NULL);

    }



     

    xerr = xvid_encore(NULL, XVID_ENC_CREATE, &xvid_enc_create, NULL);

    if (xerr) {

        av_log(avctx, AV_LOG_ERROR, "Xvid: Could not create encoder reference\n");

        return AVERROR_EXTERNAL;

    }



    x->encoder_handle  = xvid_enc_create.handle;



    return 0;

}
