static int alac_decode_frame(AVCodecContext *avctx,

                             void *outbuffer, int *outputsize,

                             uint8_t *inbuffer, int input_buffer_size)

{

    ALACContext *alac = avctx->priv_data;



    int channels;

    int32_t outputsamples;



     

    if (!inbuffer || !input_buffer_size)

        return input_buffer_size;



     

    if (!alac->context_initialized) {

        if (alac->avctx->extradata_size != ALAC_EXTRADATA_SIZE) {

            av_log(avctx, AV_LOG_ERROR, "alac: expected %d extradata bytes\n",

                ALAC_EXTRADATA_SIZE);

            return input_buffer_size;

        }

        alac_set_info(alac);

        alac->context_initialized = 1;

    }



    outputsamples = alac->setinfo_max_samples_per_frame;



    init_get_bits(&alac->gb, inbuffer, input_buffer_size * 8);



    channels = get_bits(&alac->gb, 3);



    *outputsize = outputsamples * alac->bytespersample;



    switch(channels) {

    case 0: {  

        int hassize;

        int isnotcompressed;

        int readsamplesize;



        int wasted_bytes;

        int ricemodifier;





         

        get_bits(&alac->gb, 4);



        get_bits(&alac->gb, 12);  



        hassize = get_bits(&alac->gb, 1);  



        wasted_bytes = get_bits(&alac->gb, 2);  



        isnotcompressed = get_bits(&alac->gb, 1);  



        if (hassize) {

             

            outputsamples = get_bits(&alac->gb, 32);

            *outputsize = outputsamples * alac->bytespersample;

        }



        readsamplesize = alac->setinfo_sample_size - (wasted_bytes * 8);



        if (!isnotcompressed) {

          

            int16_t predictor_coef_table[32];

            int predictor_coef_num;

            int prediction_type;

            int prediction_quantitization;

            int i;



             

            get_bits(&alac->gb, 8);

            get_bits(&alac->gb, 8);



            prediction_type = get_bits(&alac->gb, 4);

            prediction_quantitization = get_bits(&alac->gb, 4);



            ricemodifier = get_bits(&alac->gb, 3);

            predictor_coef_num = get_bits(&alac->gb, 5);



             

            for (i = 0; i < predictor_coef_num; i++) {

                predictor_coef_table[i] = (int16_t)get_bits(&alac->gb, 16);

            }



            if (wasted_bytes) {

                 

                av_log(avctx, AV_LOG_ERROR, "FIXME: unimplemented, unhandling of wasted_bytes\n");

            }



            bastardized_rice_decompress(alac,

                                        alac->predicterror_buffer_a,

                                        outputsamples,

                                        readsamplesize,

                                        alac->setinfo_rice_initialhistory,

                                        alac->setinfo_rice_kmodifier,

                                        ricemodifier * alac->setinfo_rice_historymult / 4,

                                        (1 << alac->setinfo_rice_kmodifier) - 1);



            if (prediction_type == 0) {

               

                predictor_decompress_fir_adapt(alac->predicterror_buffer_a,

                                               alac->outputsamples_buffer_a,

                                               outputsamples,

                                               readsamplesize,

                                               predictor_coef_table,

                                               predictor_coef_num,

                                               prediction_quantitization);

            } else {

                av_log(avctx, AV_LOG_ERROR, "FIXME: unhandled prediction type: %i\n", prediction_type);

                 

            }



        } else {

           

            if (readsamplesize <= 16) {

                int i;

                for (i = 0; i < outputsamples; i++) {

                    int32_t audiobits = get_bits(&alac->gb, readsamplesize);



                    audiobits = SIGN_EXTENDED32(audiobits, readsamplesize);



                    alac->outputsamples_buffer_a[i] = audiobits;

                }

            } else {

                int i;

                for (i = 0; i < outputsamples; i++) {

                    int32_t audiobits;



                    audiobits = get_bits(&alac->gb, 16);

                     

                    audiobits = audiobits << 16;

                    audiobits = audiobits >> (32 - readsamplesize);



                    audiobits |= get_bits(&alac->gb, readsamplesize - 16);



                    alac->outputsamples_buffer_a[i] = audiobits;

                }

            }

             

        }



        switch(alac->setinfo_sample_size) {

        case 16: {

            int i;

            for (i = 0; i < outputsamples; i++) {

                int16_t sample = alac->outputsamples_buffer_a[i];

                ((int16_t*)outbuffer)[i * alac->numchannels] = sample;

            }

            break;

        }

        case 20:

        case 24:

        case 32:

            av_log(avctx, AV_LOG_ERROR, "FIXME: unimplemented sample size %i\n", alac->setinfo_sample_size);

            break;

        default:

            break;

        }

        break;

    }

    case 1: {  

        int hassize;

        int isnotcompressed;

        int readsamplesize;



        int wasted_bytes;



        uint8_t interlacing_shift;

        uint8_t interlacing_leftweight;



         

        get_bits(&alac->gb, 4);



        get_bits(&alac->gb, 12);  



        hassize = get_bits(&alac->gb, 1);  



        wasted_bytes = get_bits(&alac->gb, 2);  



        isnotcompressed = get_bits(&alac->gb, 1);  



        if (hassize) {

             

            outputsamples = get_bits(&alac->gb, 32);

            *outputsize = outputsamples * alac->bytespersample;

        }



        readsamplesize = alac->setinfo_sample_size - (wasted_bytes * 8) + 1;



        if (!isnotcompressed) {

          

            int16_t predictor_coef_table_a[32];

            int predictor_coef_num_a;

            int prediction_type_a;

            int prediction_quantitization_a;

            int ricemodifier_a;



            int16_t predictor_coef_table_b[32];

            int predictor_coef_num_b;

            int prediction_type_b;

            int prediction_quantitization_b;

            int ricemodifier_b;



            int i;



            interlacing_shift = get_bits(&alac->gb, 8);

            interlacing_leftweight = get_bits(&alac->gb, 8);



             

            prediction_type_a = get_bits(&alac->gb, 4);

            prediction_quantitization_a = get_bits(&alac->gb, 4);



            ricemodifier_a = get_bits(&alac->gb, 3);

            predictor_coef_num_a = get_bits(&alac->gb, 5);



             

            for (i = 0; i < predictor_coef_num_a; i++) {

                predictor_coef_table_a[i] = (int16_t)get_bits(&alac->gb, 16);

            }



             

            prediction_type_b = get_bits(&alac->gb, 4);

            prediction_quantitization_b = get_bits(&alac->gb, 4);



            ricemodifier_b = get_bits(&alac->gb, 3);

            predictor_coef_num_b = get_bits(&alac->gb, 5);



             

            for (i = 0; i < predictor_coef_num_b; i++) {

                predictor_coef_table_b[i] = (int16_t)get_bits(&alac->gb, 16);

            }



             

            if (wasted_bytes) {

               

                av_log(avctx, AV_LOG_ERROR, "FIXME: unimplemented, unhandling of wasted_bytes\n");

            }



             

            bastardized_rice_decompress(alac,

                                        alac->predicterror_buffer_a,

                                        outputsamples,

                                        readsamplesize,

                                        alac->setinfo_rice_initialhistory,

                                        alac->setinfo_rice_kmodifier,

                                        ricemodifier_a * alac->setinfo_rice_historymult / 4,

                                        (1 << alac->setinfo_rice_kmodifier) - 1);



            if (prediction_type_a == 0) {

               

                predictor_decompress_fir_adapt(alac->predicterror_buffer_a,

                                               alac->outputsamples_buffer_a,

                                               outputsamples,

                                               readsamplesize,

                                               predictor_coef_table_a,

                                               predictor_coef_num_a,

                                               prediction_quantitization_a);

            } else {

               

                av_log(avctx, AV_LOG_ERROR, "FIXME: unhandled prediction type: %i\n", prediction_type_a);

            }



             

            bastardized_rice_decompress(alac,

                                        alac->predicterror_buffer_b,

                                        outputsamples,

                                        readsamplesize,

                                        alac->setinfo_rice_initialhistory,

                                        alac->setinfo_rice_kmodifier,

                                        ricemodifier_b * alac->setinfo_rice_historymult / 4,

                                        (1 << alac->setinfo_rice_kmodifier) - 1);



            if (prediction_type_b == 0) {

               

                predictor_decompress_fir_adapt(alac->predicterror_buffer_b,

                                               alac->outputsamples_buffer_b,

                                               outputsamples,

                                               readsamplesize,

                                               predictor_coef_table_b,

                                               predictor_coef_num_b,

                                               prediction_quantitization_b);

            } else {

                av_log(avctx, AV_LOG_ERROR, "FIXME: unhandled prediction type: %i\n", prediction_type_b);

            }

        } else {

          

            if (alac->setinfo_sample_size <= 16) {

                int i;

                for (i = 0; i < outputsamples; i++) {

                    int32_t audiobits_a, audiobits_b;



                    audiobits_a = get_bits(&alac->gb, alac->setinfo_sample_size);

                    audiobits_b = get_bits(&alac->gb, alac->setinfo_sample_size);



                    audiobits_a = SIGN_EXTENDED32(audiobits_a, alac->setinfo_sample_size);

                    audiobits_b = SIGN_EXTENDED32(audiobits_b, alac->setinfo_sample_size);



                    alac->outputsamples_buffer_a[i] = audiobits_a;

                    alac->outputsamples_buffer_b[i] = audiobits_b;

                }

            } else {

                int i;

                for (i = 0; i < outputsamples; i++) {

                    int32_t audiobits_a, audiobits_b;



                    audiobits_a = get_bits(&alac->gb, 16);

                    audiobits_a = audiobits_a << 16;

                    audiobits_a = audiobits_a >> (32 - alac->setinfo_sample_size);

                    audiobits_a |= get_bits(&alac->gb, alac->setinfo_sample_size - 16);



                    audiobits_b = get_bits(&alac->gb, 16);

                    audiobits_b = audiobits_b << 16;

                    audiobits_b = audiobits_b >> (32 - alac->setinfo_sample_size);

                    audiobits_b |= get_bits(&alac->gb, alac->setinfo_sample_size - 16);



                    alac->outputsamples_buffer_a[i] = audiobits_a;

                    alac->outputsamples_buffer_b[i] = audiobits_b;

                }

            }

             

            interlacing_shift = 0;

            interlacing_leftweight = 0;

        }



        switch(alac->setinfo_sample_size) {

        case 16: {

            deinterlace_16(alac->outputsamples_buffer_a,

                           alac->outputsamples_buffer_b,

                           (int16_t*)outbuffer,

                           alac->numchannels,

                           outputsamples,

                           interlacing_shift,

                           interlacing_leftweight);

            break;

        }

        case 20:

        case 24:

        case 32:

            av_log(avctx, AV_LOG_ERROR, "FIXME: unimplemented sample size %i\n", alac->setinfo_sample_size);

            break;

        default:

            break;

        }



        break;

    }

    }



    return input_buffer_size;

}
