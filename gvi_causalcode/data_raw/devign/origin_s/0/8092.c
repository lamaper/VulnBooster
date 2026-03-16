static int adpcm_decode_frame(AVCodecContext *avctx,

			    void *data, int *data_size,

			    uint8_t *buf, int buf_size)

{

    ADPCMContext *c = avctx->priv_data;

    ADPCMChannelStatus *cs;

    int n, m, channel, i;

    int block_predictor[2];

    short *samples;

    uint8_t *src;

    int st;  



     

    unsigned char last_byte = 0;

    unsigned char nibble;

    int decode_top_nibble_next = 0;

    int diff_channel;



    samples = data;

    src = buf;



    st = avctx->channels == 2;



    switch(avctx->codec->id) {

    case CODEC_ID_ADPCM_IMA_QT:

        n = (buf_size - 2); 

        channel = c->channel;

        cs = &(c->status[channel]);

         



         

        cs->predictor = (*src++) << 8;

        cs->predictor |= (*src & 0x80);

        cs->predictor &= 0xFF80;



         

        if(cs->predictor & 0x8000)

            cs->predictor -= 0x10000;



        CLAMP_TO_SHORT(cs->predictor);



        cs->step_index = (*src++) & 0x7F;



        if (cs->step_index > 88) fprintf(stderr, "ERROR: step_index = %i\n", cs->step_index);

        if (cs->step_index > 88) cs->step_index = 88;



        cs->step = step_table[cs->step_index];



        if (st && channel)

            samples++;



        *samples++ = cs->predictor;

        samples += st;



        for(m=32; n>0 && m>0; n--, m--) {  

            *samples = adpcm_ima_expand_nibble(cs, src[0] & 0x0F);

            samples += avctx->channels;

            *samples = adpcm_ima_expand_nibble(cs, (src[0] >> 4) & 0x0F);

            samples += avctx->channels;

            src ++;

        }



        if(st) {  

            c->channel = (channel + 1) % 2;  

            if(channel == 0) {  

                *data_size = 0;

                return src - buf;

            }

        }

        break;

    case CODEC_ID_ADPCM_IMA_WAV:

        if (avctx->block_align != 0 && buf_size > avctx->block_align)

            buf_size = avctx->block_align;



	 

        cs = &(c->status[0]);

        cs->predictor = (*src++) & 0x0FF;

        cs->predictor |= ((*src++) << 8) & 0x0FF00;

        if(cs->predictor & 0x8000)

            cs->predictor -= 0x10000;

        CLAMP_TO_SHORT(cs->predictor);



	 



	cs->step_index = *src++;

        if (cs->step_index < 0) cs->step_index = 0;

        if (cs->step_index > 88) cs->step_index = 88;

        if (*src++) fprintf(stderr, "unused byte should be null !!\n");  



        if (st) {

            cs = &(c->status[1]);

            cs->predictor = (*src++) & 0x0FF;

            cs->predictor |= ((*src++) << 8) & 0x0FF00;

            if(cs->predictor & 0x8000)

                cs->predictor -= 0x10000;

            CLAMP_TO_SHORT(cs->predictor);



	     



	    cs->step_index = *src++;

            if (cs->step_index < 0) cs->step_index = 0;

            if (cs->step_index > 88) cs->step_index = 88;

            src++;  

        }



        for(m=4; src < (buf + buf_size);) {

	    *samples++ = adpcm_ima_expand_nibble(&c->status[0], src[0] & 0x0F);

            if (st)

                *samples++ = adpcm_ima_expand_nibble(&c->status[1], src[4] & 0x0F);

            *samples++ = adpcm_ima_expand_nibble(&c->status[0], (src[0] >> 4) & 0x0F);

	    if (st) {

                *samples++ = adpcm_ima_expand_nibble(&c->status[1], (src[4] >> 4) & 0x0F);

		if (!--m) {

		    m=4;

		    src+=4;

		}

	    }

	    src++;

	}

        break;

    case CODEC_ID_ADPCM_4XM:

        cs = &(c->status[0]);

        c->status[0].predictor= (int16_t)(src[0] + (src[1]<<8)); src+=2;

        if(st){

            c->status[1].predictor= (int16_t)(src[0] + (src[1]<<8)); src+=2;

        }

        c->status[0].step_index= (int16_t)(src[0] + (src[1]<<8)); src+=2;

        if(st){

            c->status[1].step_index= (int16_t)(src[0] + (src[1]<<8)); src+=2;

        }

 

 



        m= (buf_size - (src - buf))>>st;

 

         

        for(i=0; i<m; i++) {

	    *samples++ = adpcm_4xa_expand_nibble(&c->status[0], src[i] & 0x0F);

            if (st)

                *samples++ = adpcm_4xa_expand_nibble(&c->status[1], src[i+m] & 0x0F);

            *samples++ = adpcm_4xa_expand_nibble(&c->status[0], src[i] >> 4);

	    if (st)

                *samples++ = adpcm_4xa_expand_nibble(&c->status[1], src[i+m] >> 4);

	}



        src += m<<st;



        break;

    case CODEC_ID_ADPCM_MS:

        if (avctx->block_align != 0 && buf_size > avctx->block_align)

            buf_size = avctx->block_align;

        n = buf_size - 7 * avctx->channels;

        if (n < 0)

            return -1;

        block_predictor[0] = (*src++);  

        block_predictor[0] = (block_predictor[0] < 0)?(0):((block_predictor[0] > 7)?(7):(block_predictor[0]));

        block_predictor[1] = 0;

        if (st)

            block_predictor[1] = (*src++);

        block_predictor[1] = (block_predictor[1] < 0)?(0):((block_predictor[1] > 7)?(7):(block_predictor[1]));

        c->status[0].idelta = ((*src & 0xFF) | ((src[1] << 8) & 0xFF00));

        if (c->status[0].idelta & 0x08000)

            c->status[0].idelta -= 0x10000;

        src+=2;

        if (st)

            c->status[1].idelta = ((*src & 0xFF) | ((src[1] << 8) & 0xFF00));

        if (st && c->status[1].idelta & 0x08000)

            c->status[1].idelta |= 0xFFFF0000;

        if (st)

            src+=2;

        c->status[0].coeff1 = AdaptCoeff1[block_predictor[0]];

        c->status[0].coeff2 = AdaptCoeff2[block_predictor[0]];

        c->status[1].coeff1 = AdaptCoeff1[block_predictor[1]];

        c->status[1].coeff2 = AdaptCoeff2[block_predictor[1]];

        

        c->status[0].sample1 = ((*src & 0xFF) | ((src[1] << 8) & 0xFF00));

        src+=2;

        if (st) c->status[1].sample1 = ((*src & 0xFF) | ((src[1] << 8) & 0xFF00));

        if (st) src+=2;

        c->status[0].sample2 = ((*src & 0xFF) | ((src[1] << 8) & 0xFF00));

        src+=2;

        if (st) c->status[1].sample2 = ((*src & 0xFF) | ((src[1] << 8) & 0xFF00));

        if (st) src+=2;



        *samples++ = c->status[0].sample1;

        if (st) *samples++ = c->status[1].sample1;

        *samples++ = c->status[0].sample2;

        if (st) *samples++ = c->status[1].sample2;

        for(;n>0;n--) {

            *samples++ = adpcm_ms_expand_nibble(&c->status[0], (src[0] >> 4) & 0x0F);

            *samples++ = adpcm_ms_expand_nibble(&c->status[st], src[0] & 0x0F);

            src ++;

        }

        break;

    case CODEC_ID_ADPCM_IMA_DK4:

        if (buf_size > BLKSIZE) {

            if (avctx->block_align != 0)

                buf_size = avctx->block_align;

            else

                buf_size = BLKSIZE;

        }

        c->status[0].predictor = (src[0] | (src[1] << 8));

        c->status[0].step_index = src[2];

        src += 4;

        if(c->status[0].predictor & 0x8000)

            c->status[0].predictor -= 0x10000;

        *samples++ = c->status[0].predictor;

        if (st) {

            c->status[1].predictor = (src[0] | (src[1] << 8));

            c->status[1].step_index = src[2];

            src += 4;

            if(c->status[1].predictor & 0x8000)

                c->status[1].predictor -= 0x10000;

            *samples++ = c->status[1].predictor;

        }

        while (src < buf + buf_size) {



             

            *samples++ = adpcm_ima_expand_nibble(&c->status[0], 

                (src[0] >> 4) & 0x0F);



             

            if (st)

                *samples++ = adpcm_ima_expand_nibble(&c->status[1], 

                    src[0] & 0x0F);

            else

                *samples++ = adpcm_ima_expand_nibble(&c->status[0], 

                    src[0] & 0x0F);



            src++;

        }

        break;

    case CODEC_ID_ADPCM_IMA_DK3:

        if (buf_size > BLKSIZE) {

            if (avctx->block_align != 0)

                buf_size = avctx->block_align;

            else

                buf_size = BLKSIZE;

        }

        c->status[0].predictor = (src[10] | (src[11] << 8));

        c->status[1].predictor = (src[12] | (src[13] << 8));

        c->status[0].step_index = src[14];

        c->status[1].step_index = src[15];

         

        if(c->status[0].predictor & 0x8000)

            c->status[0].predictor -= 0x10000;

        if(c->status[1].predictor & 0x8000)

            c->status[1].predictor -= 0x10000;

        src += 16;

        diff_channel = c->status[1].predictor;



         

        while (1) {



             



             

            DK3_GET_NEXT_NIBBLE();

            adpcm_ima_expand_nibble(&c->status[0], nibble);



             

            DK3_GET_NEXT_NIBBLE();

            adpcm_ima_expand_nibble(&c->status[1], nibble);



             

            diff_channel = (diff_channel + c->status[1].predictor) / 2;

            *samples++ = c->status[0].predictor + c->status[1].predictor;

            *samples++ = c->status[0].predictor - c->status[1].predictor;



             

            DK3_GET_NEXT_NIBBLE();

            adpcm_ima_expand_nibble(&c->status[0], nibble);



             

            diff_channel = (diff_channel + c->status[1].predictor) / 2;

            *samples++ = c->status[0].predictor + c->status[1].predictor;

            *samples++ = c->status[0].predictor - c->status[1].predictor;

        }

        break;

    case CODEC_ID_ADPCM_IMA_WS:

         

        while (src < buf + buf_size) {



            if (st) {

                *samples++ = adpcm_ima_expand_nibble(&c->status[0], 

                    (src[0] >> 4) & 0x0F);

                *samples++ = adpcm_ima_expand_nibble(&c->status[1], 

                    src[0] & 0x0F);

            } else {

                *samples++ = adpcm_ima_expand_nibble(&c->status[0], 

                    (src[0] >> 4) & 0x0F);

                *samples++ = adpcm_ima_expand_nibble(&c->status[0], 

                    src[0] & 0x0F);

            }



            src++;

        }

        break;

    case CODEC_ID_ADPCM_XA:

        c->status[0].sample1 = c->status[0].sample2 = 

        c->status[1].sample1 = c->status[1].sample2 = 0;

        while (buf_size >= 128) {

            xa_decode(samples, src, &c->status[0], &c->status[1], 

                avctx->channels);

            src += 128;

            samples += 28 * 8;

            buf_size -= 128;

        }

        break;

    default:

        *data_size = 0;

        return -1;

    }

    *data_size = (uint8_t *)samples - (uint8_t *)data;

    return src - buf;

}
