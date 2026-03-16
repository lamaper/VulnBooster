static inline void dv_decode_video_segment(DVVideoContext *s, 

                                           uint8_t *buf_ptr1, 

                                           const uint16_t *mb_pos_ptr)

{

    int quant, dc, dct_mode, class1, j;

    int mb_index, mb_x, mb_y, v, last_index;

    DCTELEM *block, *block1;

    int c_offset;

    uint8_t *y_ptr;

    void (*idct_put)(uint8_t *dest, int line_size, DCTELEM *block);

    uint8_t *buf_ptr;

    PutBitContext pb, vs_pb;

    GetBitContext gb;

    BlockInfo mb_data[5 * 6], *mb, *mb1;

    DCTELEM sblock[5*6][64] __align8;

    uint8_t mb_bit_buffer[80 + 4];  

    uint8_t vs_bit_buffer[5 * 80 + 4];  

	    

    memset(sblock, 0, sizeof(sblock));



     

    buf_ptr = buf_ptr1;

    block1 = &sblock[0][0];

    mb1 = mb_data;

    init_put_bits(&vs_pb, vs_bit_buffer, 5 * 80);

    for(mb_index = 0; mb_index < 5; mb_index++, mb1 += 6, block1 += 6 * 64) {

         

        quant = buf_ptr[3] & 0x0f;

        buf_ptr += 4;

        init_put_bits(&pb, mb_bit_buffer, 80);

        mb = mb1;

        block = block1;

        for(j = 0;j < 6; j++) {

            last_index = block_sizes[j];

	    init_get_bits(&gb, buf_ptr, last_index);

            

             

            dc = get_sbits(&gb, 9);

            dct_mode = get_bits1(&gb);

            mb->dct_mode = dct_mode;

            mb->scan_table = s->dv_zigzag[dct_mode];

            class1 = get_bits(&gb, 2);

            mb->shift_table = s->dv_idct_shift[class1 == 3][dct_mode]

                [quant + dv_quant_offset[class1]];

            dc = dc << 2;

             

            dc += 1024;

            block[0] = dc;

            buf_ptr += last_index >> 3;

            mb->pos = 0;

            mb->partial_bit_count = 0;


            printf("MB block: %d, %d ", mb_index, j);


            dv_decode_ac(&gb, mb, block);



             

            if (mb->pos >= 64)

                bit_copy(&pb, &gb);

            

            block += 64;

            mb++;

        }


        printf("***pass 2 size=%d MB#=%d\n", put_bits_count(&pb), mb_index);


        block = block1;

        mb = mb1;

        init_get_bits(&gb, mb_bit_buffer, put_bits_count(&pb));

	flush_put_bits(&pb);

        for(j = 0;j < 6; j++, block += 64, mb++) {

            if (mb->pos < 64 && get_bits_left(&gb) > 0) {

                dv_decode_ac(&gb, mb, block);

                 

                if (mb->pos < 64)

                    break;

            }

        }

         

        if (j >= 6)

	    bit_copy(&vs_pb, &gb);

    }


    printf("***pass 3 size=%d\n", put_bits_count(&vs_pb));


    block = &sblock[0][0];

    mb = mb_data;

    init_get_bits(&gb, vs_bit_buffer, put_bits_count(&vs_pb));

    flush_put_bits(&vs_pb);

    for(mb_index = 0; mb_index < 5; mb_index++) {

        for(j = 0;j < 6; j++) {

            if (mb->pos < 64) {


                printf("start %d:%d\n", mb_index, j);


                dv_decode_ac(&gb, mb, block);

            }

	    if (mb->pos >= 64 && mb->pos < 127)

		av_log(NULL, AV_LOG_ERROR, "AC EOB marker is absent pos=%d\n", mb->pos);

            block += 64;

            mb++;

        }

    }

    

     

    block = &sblock[0][0];

    mb = mb_data;

    for(mb_index = 0; mb_index < 5; mb_index++) {

        v = *mb_pos_ptr++;

        mb_x = v & 0xff;

        mb_y = v >> 8;

        y_ptr = s->picture.data[0] + (mb_y * s->picture.linesize[0] * 8) + (mb_x * 8);

        if (s->sys->pix_fmt == PIX_FMT_YUV411P)

            c_offset = (mb_y * s->picture.linesize[1] * 8) + ((mb_x >> 2) * 8);

        else

            c_offset = ((mb_y >> 1) * s->picture.linesize[1] * 8) + ((mb_x >> 1) * 8);

        for(j = 0;j < 6; j++) {

            idct_put = s->idct_put[mb->dct_mode];

            if (j < 4) {

                if (s->sys->pix_fmt == PIX_FMT_YUV411P && mb_x < (704 / 8)) {

                     

                    idct_put(y_ptr + (j * 8), s->picture.linesize[0], block);

                } else {

                    idct_put(y_ptr + ((j & 1) * 8) + ((j >> 1) * 8 * s->picture.linesize[0]),

                             s->picture.linesize[0], block);

                }

            } else {

                if (s->sys->pix_fmt == PIX_FMT_YUV411P && mb_x >= (704 / 8)) {

                    uint64_t aligned_pixels[64/8];

                    uint8_t *pixels= (uint8_t*)aligned_pixels;

		    uint8_t *c_ptr, *c_ptr1, *ptr;

                    int y, linesize;

                     

                    idct_put(pixels, 8, block);

                    linesize = s->picture.linesize[6 - j];

                    c_ptr = s->picture.data[6 - j] + c_offset;

                    ptr = pixels;

                    for(y = 0;y < 8; y++) {

                         

                        c_ptr1 = c_ptr + 8*linesize;

                        c_ptr[0]= ptr[0]; c_ptr1[0]= ptr[4];

                        c_ptr[1]= ptr[1]; c_ptr1[1]= ptr[5];

                        c_ptr[2]= ptr[2]; c_ptr1[2]= ptr[6];

                        c_ptr[3]= ptr[3]; c_ptr1[3]= ptr[7];

                        c_ptr += linesize;

                        ptr += 8;

                    }

                } else {

                     

                    idct_put(s->picture.data[6 - j] + c_offset, 

                             s->picture.linesize[6 - j], block);

                }

            }

            block += 64;

            mb++;

        }

    }

}
