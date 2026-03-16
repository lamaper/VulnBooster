static av_cold int xvid_encode_init(AVCodecContext *avctx)

{

    int xerr, i;

    int xvid_flags = avctx->flags;

    struct xvid_context *x = avctx->priv_data;

    uint16_t *intra, *inter;

    int fd;



    xvid_plugin_single_t single         = { 0 };

    struct xvid_ff_pass1 rc2pass1       = { 0 };

    xvid_plugin_2pass2_t rc2pass2       = { 0 };

    xvid_plugin_lumimasking_t masking_l = { 0 };  

    xvid_plugin_lumimasking_t masking_v = { 0 };  

    xvid_plugin_ssim_t ssim             = { 0 };

    xvid_gbl_init_t xvid_gbl_init       = { 0 };

    xvid_enc_create_t xvid_enc_create   = { 0 };

    xvid_enc_plugin_t plugins[7];



     

    x->vop_flags = XVID_VOP_HALFPEL;  

    if (xvid_flags & CODEC_FLAG_4MV)

        x->vop_flags |= XVID_VOP_INTER4V;  

    if (avctx->trellis)

        x->vop_flags |= XVID_VOP_TRELLISQUANT;  

    if (xvid_flags & CODEC_FLAG_AC_PRED)

        x->vop_flags |= XVID_VOP_HQACPRED;  

    if (xvid_flags & CODEC_FLAG_GRAY)

        x->vop_flags |= XVID_VOP_GREYSCALE;



     

    x->me_flags = 0;

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

    if (xvid_flags & CODEC_FLAG_QPEL) {

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



    xvid_enc_create.plugins     = plugins;

    xvid_enc_create.num_plugins = 0;



     

    x->twopassbuffer     = NULL;

    x->old_twopassbuffer = NULL;

    x->twopassfile       = NULL;



    if (xvid_flags & CODEC_FLAG_PASS1) {

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

    } else if (xvid_flags & CODEC_FLAG_PASS2) {

        rc2pass2.version = XVID_VERSION;

        rc2pass2.bitrate = avctx->bit_rate;



        fd = ff_tempfile("xvidff.", &x->twopassfile);

        if (fd < 0) {

            av_log(avctx, AV_LOG_ERROR, "Xvid: Cannot write 2-pass pipe\n");

            return fd;

        }



        if (!avctx->stats_in) {

            av_log(avctx, AV_LOG_ERROR,

                   "Xvid: No 2-pass information loaded for second pass\n");

            return AVERROR_INVALIDDATA;

        }



        if (strlen(avctx->stats_in) >

            write(fd, avctx->stats_in, strlen(avctx->stats_in))) {

            close(fd);

            av_log(avctx, AV_LOG_ERROR, "Xvid: Cannot write to 2-pass pipe\n");

            return AVERROR(EIO);

        }



        close(fd);

        rc2pass2.filename                          = x->twopassfile;

        plugins[xvid_enc_create.num_plugins].func  = xvid_plugin_2pass2;

        plugins[xvid_enc_create.num_plugins].param = &rc2pass2;

        xvid_enc_create.num_plugins++;

    } else if (!(xvid_flags & CODEC_FLAG_QSCALE)) {

         

        single.version = XVID_VERSION;

        single.bitrate = avctx->bit_rate;



        plugins[xvid_enc_create.num_plugins].func  = xvid_plugin_single;

        plugins[xvid_enc_create.num_plugins].param = &single;

        xvid_enc_create.num_plugins++;

    }



    if (avctx->lumi_masking != 0.0)

        x->lumi_aq = 1;



    if (x->lumi_aq && x->variance_aq) {

        x->variance_aq = 0;

        av_log(avctx, AV_LOG_WARNING,

               "variance_aq is ignored when lumi_aq is set.\n");

    }



     

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



     

    if (xvid_flags & CODEC_FLAG_QSCALE)

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

    if (avctx->mpeg_quant)

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

    if (xvid_flags & CODEC_FLAG_CLOSED_GOP)

        xvid_enc_create.global |= XVID_GLOBAL_CLOSED_GOP;



     

    avctx->extradata      = NULL;

    avctx->extradata_size = 0;

    if (xvid_flags & CODEC_FLAG_GLOBAL_HEADER) {

         

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



     

    xerr = xvid_encore(NULL, XVID_ENC_CREATE, &xvid_enc_create, NULL);

    if (xerr) {

        av_log(avctx, AV_LOG_ERROR, "Xvid: Could not create encoder reference\n");

        return -1;

    }



    x->encoder_handle  = xvid_enc_create.handle;

    avctx->coded_frame = av_frame_alloc();

    if (!avctx->coded_frame)

        return AVERROR(ENOMEM);



    return 0;

}
