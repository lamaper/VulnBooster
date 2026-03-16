static int encode_dvb_subtitles(DVBSubtitleContext *s,

                                uint8_t *outbuf, const AVSubtitle *h)

{

    uint8_t *q, *pseg_len;

    int page_id, region_id, clut_id, object_id, i, bpp_index, page_state;





    q = outbuf;



    page_id = 1;



    if (h->num_rects == 0 || h->rects == NULL)

        return -1;



    *q++ = 0x00;  



     



    *q++ = 0x0f;  

    *q++ = 0x10;  

    bytestream_put_be16(&q, page_id);

    pseg_len = q;

    q += 2;  

    *q++ = 30;  

    if (s->hide_state)

        page_state = 0;  

    else

        page_state = 2;  

     

    *q++ = (s->object_version << 4) | (page_state << 2) | 3;



    for (region_id = 0; region_id < h->num_rects; region_id++) {

        *q++ = region_id;

        *q++ = 0xff;  

        bytestream_put_be16(&q, h->rects[region_id]->x);  

        bytestream_put_be16(&q, h->rects[region_id]->y);  

    }



    bytestream_put_be16(&pseg_len, q - pseg_len - 2);



    if (!s->hide_state) {

        for (clut_id = 0; clut_id < h->num_rects; clut_id++) {



             



            if (h->rects[clut_id]->nb_colors <= 4) {

                 

                bpp_index = 0;

            } else if (h->rects[clut_id]->nb_colors <= 16) {

                 

                bpp_index = 1;

            } else {

                return -1;

            }



            *q++ = 0x0f;  

            *q++ = 0x12;  

            bytestream_put_be16(&q, page_id);

            pseg_len = q;

            q += 2;  

            *q++ = clut_id;

            *q++ = (0 << 4) | 0xf;  



            for(i = 0; i < h->rects[clut_id]->nb_colors; i++) {

                *q++ = i;  

                *q++ = (1 << (7 - bpp_index)) | (0xf << 1) | 1;  

                {

                    int a, r, g, b;

                    uint32_t x= ((uint32_t*)h->rects[clut_id]->pict.data[1])[i];

                    a = (x >> 24) & 0xff;

                    r = (x >> 16) & 0xff;

                    g = (x >>  8) & 0xff;

                    b = (x >>  0) & 0xff;



                    *q++ = RGB_TO_Y_CCIR(r, g, b);

                    *q++ = RGB_TO_V_CCIR(r, g, b, 0);

                    *q++ = RGB_TO_U_CCIR(r, g, b, 0);

                    *q++ = 255 - a;

                }

            }



            bytestream_put_be16(&pseg_len, q - pseg_len - 2);

        }

    }



    for (region_id = 0; region_id < h->num_rects; region_id++) {



         



        if (h->rects[region_id]->nb_colors <= 4) {

             

            bpp_index = 0;

        } else if (h->rects[region_id]->nb_colors <= 16) {

             

            bpp_index = 1;

        } else {

            return -1;

        }



        *q++ = 0x0f;  

        *q++ = 0x11;  

        bytestream_put_be16(&q, page_id);

        pseg_len = q;

        q += 2;  

        *q++ = region_id;

        *q++ = (s->object_version << 4) | (0 << 3) | 0x07;  

        bytestream_put_be16(&q, h->rects[region_id]->w);  

        bytestream_put_be16(&q, h->rects[region_id]->h);  

        *q++ = ((1 + bpp_index) << 5) | ((1 + bpp_index) << 2) | 0x03;

        *q++ = region_id;  

        *q++ = 0;  

        *q++ = 0x03;  



        if (!s->hide_state) {

            bytestream_put_be16(&q, region_id);  

            *q++ = (0 << 6) | (0 << 4);

            *q++ = 0;

            *q++ = 0xf0;

            *q++ = 0;

        }



        bytestream_put_be16(&pseg_len, q - pseg_len - 2);

    }



    if (!s->hide_state) {



        for (object_id = 0; object_id < h->num_rects; object_id++) {

             



            if (h->rects[object_id]->nb_colors <= 4) {

                 

                bpp_index = 0;

            } else if (h->rects[object_id]->nb_colors <= 16) {

                 

                bpp_index = 1;

            } else {

                return -1;

            }



            *q++ = 0x0f;  

            *q++ = 0x13;

            bytestream_put_be16(&q, page_id);

            pseg_len = q;

            q += 2;  



            bytestream_put_be16(&q, object_id);

            *q++ = (s->object_version << 4) | (0 << 2) | (0 << 1) | 1;  

            {

                uint8_t *ptop_field_len, *pbottom_field_len, *top_ptr, *bottom_ptr;

                void (*dvb_encode_rle)(uint8_t **pq,

                                        const uint8_t *bitmap, int linesize,

                                        int w, int h);

                ptop_field_len = q;

                q += 2;

                pbottom_field_len = q;

                q += 2;



                if (bpp_index == 0)

                    dvb_encode_rle = dvb_encode_rle2;

                else

                    dvb_encode_rle = dvb_encode_rle4;



                top_ptr = q;

                dvb_encode_rle(&q, h->rects[object_id]->pict.data[0], h->rects[object_id]->w * 2,

                                    h->rects[object_id]->w, h->rects[object_id]->h >> 1);

                bottom_ptr = q;

                dvb_encode_rle(&q, h->rects[object_id]->pict.data[0] + h->rects[object_id]->w,

                                    h->rects[object_id]->w * 2, h->rects[object_id]->w,

                                    h->rects[object_id]->h >> 1);



                bytestream_put_be16(&ptop_field_len, bottom_ptr - top_ptr);

                bytestream_put_be16(&pbottom_field_len, q - bottom_ptr);

            }



            bytestream_put_be16(&pseg_len, q - pseg_len - 2);

        }

    }



     



    *q++ = 0x0f;  

    *q++ = 0x80;  

    bytestream_put_be16(&q, page_id);

    pseg_len = q;

    q += 2;  



    bytestream_put_be16(&pseg_len, q - pseg_len - 2);



    *q++ = 0xff;  



    s->object_version = (s->object_version + 1) & 0xf;

    s->hide_state = !s->hide_state;

    return q - outbuf;

}
