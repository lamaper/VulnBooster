int h263_decode_picture_header(MpegEncContext *s)

{

    int format, width, height, i;

    uint32_t startcode;

    

    align_get_bits(&s->gb);



    startcode= get_bits(&s->gb, 22-8);



    for(i= s->gb.size_in_bits - get_bits_count(&s->gb); i>24; i-=8) {

        startcode = ((startcode << 8) | get_bits(&s->gb, 8)) & 0x003FFFFF;

        

        if(startcode == 0x20)

            break;

    }

        

    if (startcode != 0x20) {

        av_log(s->avctx, AV_LOG_ERROR, "Bad picture start code\n");

        return -1;

    }

     

    s->picture_number = get_bits(&s->gb, 8);  



         

    if (get_bits1(&s->gb) != 1) {

         

        av_log(s->avctx, AV_LOG_ERROR, "Bad marker\n");

        return -1;

    }

    if (get_bits1(&s->gb) != 0) {

        av_log(s->avctx, AV_LOG_ERROR, "Bad H263 id\n");

        return -1;	 

    }

    skip_bits1(&s->gb);	 

    skip_bits1(&s->gb);	 

    skip_bits1(&s->gb);	 



     

    s->gob_number = 0;

        

    format = get_bits(&s->gb, 3);

     



    if (format != 7 && format != 6) {

        s->h263_plus = 0;

         

        width = h263_format[format][0];

        height = h263_format[format][1];

        if (!width)

            return -1;

        

        s->pict_type = I_TYPE + get_bits1(&s->gb);



        s->h263_long_vectors = get_bits1(&s->gb); 



        if (get_bits1(&s->gb) != 0) {

            av_log(s->avctx, AV_LOG_ERROR, "H263 SAC not supported\n");

            return -1;	 

        }

        s->obmc= get_bits1(&s->gb);  

        s->unrestricted_mv = s->h263_long_vectors || s->obmc;

        

        if (get_bits1(&s->gb) != 0) {

            av_log(s->avctx, AV_LOG_ERROR, "H263 PB frame not supported\n");

            return -1;	 

        }

        s->qscale = get_bits(&s->gb, 5);

        skip_bits1(&s->gb);	 



        s->width = width;

        s->height = height;

    } else {

        int ufep;

        

         

        s->h263_plus = 1;

        ufep = get_bits(&s->gb, 3);  



                 

        if (ufep == 1) {

                    

            format = get_bits(&s->gb, 3);

            dprintf("ufep=1, format: %d\n", format);

            skip_bits(&s->gb,1);  

            s->umvplus = get_bits(&s->gb, 1);  

            skip_bits1(&s->gb);  

            s->obmc= get_bits1(&s->gb);  

            s->unrestricted_mv = s->umvplus || s->obmc;

            s->h263_aic = get_bits1(&s->gb);  

	    

            if (get_bits1(&s->gb) != 0) {

                av_log(s->avctx, AV_LOG_ERROR, "Deblocking Filter not supported\n");

            }

            if (get_bits1(&s->gb) != 0) {

                av_log(s->avctx, AV_LOG_ERROR, "Slice Structured not supported\n");

            }

            if (get_bits1(&s->gb) != 0) {

                av_log(s->avctx, AV_LOG_ERROR, "Reference Picture Selection not supported\n");

            }

            if (get_bits1(&s->gb) != 0) {

                av_log(s->avctx, AV_LOG_ERROR, "Independent Segment Decoding not supported\n");

            }

            s->alt_inter_vlc= get_bits1(&s->gb);

            s->modified_quant= get_bits1(&s->gb);

            

            skip_bits(&s->gb, 1);  



            skip_bits(&s->gb, 3);  

        } else if (ufep != 0) {

            av_log(s->avctx, AV_LOG_ERROR, "Bad UFEP type (%d)\n", ufep);

            return -1;

        }

            

         

        s->pict_type = get_bits(&s->gb, 3) + I_TYPE;

	if (s->pict_type == 8 && s->avctx->codec_tag == ff_get_fourcc("ZYGO"))

	    s->pict_type = I_TYPE;

        if (s->pict_type != I_TYPE &&

            s->pict_type != P_TYPE)

            return -1;

        skip_bits(&s->gb, 2);

        s->no_rounding = get_bits1(&s->gb);

        skip_bits(&s->gb, 4);

        

         

        if (ufep) {

            if (format == 6) {

                 

                s->aspect_ratio_info = get_bits(&s->gb, 4);

                dprintf("aspect: %d\n", s->aspect_ratio_info);

                 

                width = (get_bits(&s->gb, 9) + 1) * 4;

                skip_bits1(&s->gb);

                height = get_bits(&s->gb, 9) * 4;

                dprintf("\nH.263+ Custom picture: %dx%d\n",width,height);

                if (s->aspect_ratio_info == FF_ASPECT_EXTENDED) {

                     

                    s->avctx->sample_aspect_ratio.num= get_bits(&s->gb, 8);

                    s->avctx->sample_aspect_ratio.den= get_bits(&s->gb, 8);

                }else{

                    s->avctx->sample_aspect_ratio= pixel_aspect[s->aspect_ratio_info];

                }

            } else {

                width = h263_format[format][0];

                height = h263_format[format][1];

            }

            if ((width == 0) || (height == 0))

                return -1;

            s->width = width;

            s->height = height;

            if (s->umvplus) {

                if(get_bits1(&s->gb)==0)  

                    skip_bits1(&s->gb); 

            }

        }

            

        s->qscale = get_bits(&s->gb, 5);

    }

     

    while (get_bits1(&s->gb) != 0) {

        skip_bits(&s->gb, 8);

    }

    s->f_code = 1;

    

    if(s->h263_aic){

         s->y_dc_scale_table= 

         s->c_dc_scale_table= ff_aic_dc_scale_table;

    }else{

        s->y_dc_scale_table=

        s->c_dc_scale_table= ff_mpeg1_dc_scale_table;

    }



     if(s->avctx->debug&FF_DEBUG_PICT_INFO){

         av_log(s->avctx, AV_LOG_DEBUG, "qp:%d %c size:%d rnd:%d%s%s%s%s%s%s%s\n", 

         s->qscale, av_get_pict_type_char(s->pict_type),

         s->gb.size_in_bits, 1-s->no_rounding,

         s->obmc ? " AP" : "",

         s->umvplus ? " UMV" : "",

         s->h263_long_vectors ? " LONG" : "",

         s->h263_plus ? " +" : "",

         s->h263_aic ? " AIC" : "",

         s->alt_inter_vlc ? " AIV" : "",

         s->modified_quant ? " MQ" : ""

         ); 

     }


    if (s->pict_type == I_TYPE && s->avctx->codec_tag == ff_get_fourcc("ZYGO")){

        int i,j;

        for(i=0; i<85; i++) av_log(s->avctx, AV_LOG_DEBUG, "%d", get_bits1(&s->gb));

        av_log(s->avctx, AV_LOG_DEBUG, "\n");

        for(i=0; i<13; i++){

            for(j=0; j<3; j++){

                int v= get_bits(&s->gb, 8);

                v |= get_sbits(&s->gb, 8)<<8;

                av_log(s->avctx, AV_LOG_DEBUG, " %5d", v);

            }

            av_log(s->avctx, AV_LOG_DEBUG, "\n");

        }

        for(i=0; i<50; i++) av_log(s->avctx, AV_LOG_DEBUG, "%d", get_bits1(&s->gb));

    }




    return 0;

}
