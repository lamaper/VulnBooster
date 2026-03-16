static void RENAME(postProcess)(const uint8_t src[], int srcStride, uint8_t dst[], int dstStride, int width, int height,

                                const QP_STORE_T QPs[], int QPStride, int isColor, PPContext *c2)

{

    DECLARE_ALIGNED(8, PPContext, c)= *c2;  

    int x,y;


    const int mode= COMPILE_TIME_MODE;


    const int mode= isColor ? c.ppMode.chromMode : c.ppMode.lumMode;


    int black=0, white=255;  

    int QPCorrecture= 256*256;



    int copyAhead;


    int i;




    const int qpHShift= isColor ? 4-c.hChromaSubSample : 4;

    const int qpVShift= isColor ? 4-c.vChromaSubSample : 4;



     

    uint64_t * const yHistogram= c.yHistogram;

    uint8_t * const tempSrc= srcStride > 0 ? c.tempSrc : c.tempSrc - 23*srcStride;

    uint8_t * const tempDst= dstStride > 0 ? c.tempDst : c.tempDst - 23*dstStride;


    for(i=0; i<57; i++){

        int offset= ((i*c.ppMode.baseDcDiff)>>8) + 1;

        int threshold= offset*2 + 1;

        c.mmxDcOffset[i]= 0x7F - offset;

        c.mmxDcThreshold[i]= 0x7F - threshold;

        c.mmxDcOffset[i]*= 0x0101010101010101LL;

        c.mmxDcThreshold[i]*= 0x0101010101010101LL;

    }




    if(mode & CUBIC_IPOL_DEINT_FILTER) copyAhead=16;

    else if(   (mode & LINEAR_BLEND_DEINT_FILTER)

            || (mode & FFMPEG_DEINT_FILTER)

            || (mode & LOWPASS5_DEINT_FILTER)) copyAhead=14;

    else if(   (mode & V_DEBLOCK)

            || (mode & LINEAR_IPOL_DEINT_FILTER)

            || (mode & MEDIAN_DEINT_FILTER)

            || (mode & V_A_DEBLOCK)) copyAhead=13;

    else if(mode & V_X1_FILTER) copyAhead=11;

 

    else if(mode & DERING) copyAhead=9;

    else copyAhead=8;



    copyAhead-= 8;



    if(!isColor){

        uint64_t sum= 0;

        int i;

        uint64_t maxClipped;

        uint64_t clipped;

        double scale;



        c.frameNum++;

         

        if(c.frameNum == 1) yHistogram[0]= width*height/64*15/256;



        for(i=0; i<256; i++){

            sum+= yHistogram[i];

        }



         

        maxClipped= (uint64_t)(sum * c.ppMode.maxClippedThreshold);



        clipped= sum;

        for(black=255; black>0; black--){

            if(clipped < maxClipped) break;

            clipped-= yHistogram[black];

        }



        clipped= sum;

        for(white=0; white<256; white++){

            if(clipped < maxClipped) break;

            clipped-= yHistogram[white];

        }



        scale= (double)(c.ppMode.maxAllowedY - c.ppMode.minAllowedY) / (double)(white-black);


        c.packedYScale= (uint16_t)(scale*256.0 + 0.5);

        c.packedYOffset= (((black*c.packedYScale)>>8) - c.ppMode.minAllowedY) & 0xFFFF;


        c.packedYScale= (uint16_t)(scale*1024.0 + 0.5);

        c.packedYOffset= (black - c.ppMode.minAllowedY) & 0xFFFF;




        c.packedYOffset|= c.packedYOffset<<32;

        c.packedYOffset|= c.packedYOffset<<16;



        c.packedYScale|= c.packedYScale<<32;

        c.packedYScale|= c.packedYScale<<16;



        if(mode & LEVEL_FIX)        QPCorrecture= (int)(scale*256*256 + 0.5);

        else                        QPCorrecture= 256*256;

    }else{

        c.packedYScale= 0x0100010001000100LL;

        c.packedYOffset= 0;

        QPCorrecture= 256*256;

    }



     

    y=-BLOCK_SIZE;

    {

        const uint8_t *srcBlock= &(src[y*srcStride]);

        uint8_t *dstBlock= tempDst + dstStride;



         

         

         

        for(x=0; x<width; x+=BLOCK_SIZE){


 



            __asm__(

                "mov %4, %%"REG_a"              \n\t"

                "shr $2, %%"REG_a"              \n\t"

                "and $6, %%"REG_a"              \n\t"

                "add %5, %%"REG_a"              \n\t"

                "mov %%"REG_a", %%"REG_d"       \n\t"

                "imul %1, %%"REG_a"             \n\t"

                "imul %3, %%"REG_d"             \n\t"

                "prefetchnta 32(%%"REG_a", %0)  \n\t"

                "prefetcht0 32(%%"REG_d", %2)   \n\t"

                "add %1, %%"REG_a"              \n\t"

                "add %3, %%"REG_d"              \n\t"

                "prefetchnta 32(%%"REG_a", %0)  \n\t"

                "prefetcht0 32(%%"REG_d", %2)   \n\t"

                :: "r" (srcBlock), "r" ((x86_reg)srcStride), "r" (dstBlock), "r" ((x86_reg)dstStride),

                "g" ((x86_reg)x), "g" ((x86_reg)copyAhead)

                : "%"REG_a, "%"REG_d

            );





            RENAME(blockCopy)(dstBlock + dstStride*8, dstStride,

                              srcBlock + srcStride*8, srcStride, mode & LEVEL_FIX, &c.packedYOffset);



            RENAME(duplicate)(dstBlock + dstStride*8, dstStride);



            if(mode & LINEAR_IPOL_DEINT_FILTER)

                RENAME(deInterlaceInterpolateLinear)(dstBlock, dstStride);

            else if(mode & LINEAR_BLEND_DEINT_FILTER)

                RENAME(deInterlaceBlendLinear)(dstBlock, dstStride, c.deintTemp + x);

            else if(mode & MEDIAN_DEINT_FILTER)

                RENAME(deInterlaceMedian)(dstBlock, dstStride);

            else if(mode & CUBIC_IPOL_DEINT_FILTER)

                RENAME(deInterlaceInterpolateCubic)(dstBlock, dstStride);

            else if(mode & FFMPEG_DEINT_FILTER)

                RENAME(deInterlaceFF)(dstBlock, dstStride, c.deintTemp + x);

            else if(mode & LOWPASS5_DEINT_FILTER)

                RENAME(deInterlaceL5)(dstBlock, dstStride, c.deintTemp + x, c.deintTemp + width + x);

 

            dstBlock+=8;

            srcBlock+=8;

        }

        if(width==FFABS(dstStride))

            linecpy(dst, tempDst + 9*dstStride, copyAhead, dstStride);

        else{

            int i;

            for(i=0; i<copyAhead; i++){

                memcpy(dst + i*dstStride, tempDst + (9+i)*dstStride, width);

            }

        }

    }



    for(y=0; y<height; y+=BLOCK_SIZE){

         

        const uint8_t *srcBlock= &(src[y*srcStride]);

        uint8_t *dstBlock= &(dst[y*dstStride]);


        uint8_t *tempBlock1= c.tempBlocks;

        uint8_t *tempBlock2= c.tempBlocks + 8;


        const int8_t *QPptr= &QPs[(y>>qpVShift)*QPStride];

        int8_t *nonBQPptr= &c.nonBQPTable[(y>>qpVShift)*FFABS(QPStride)];

        int QP=0;

         

        if(y+15 >= height){

            int i;

             

            linecpy(tempSrc + srcStride*copyAhead, srcBlock + srcStride*copyAhead,

                    FFMAX(height-y-copyAhead, 0), srcStride);



             

            for(i=FFMAX(height-y, 8); i<copyAhead+8; i++)

                    memcpy(tempSrc + srcStride*i, src + srcStride*(height-1), FFABS(srcStride));



             

            linecpy(tempDst, dstBlock - dstStride, FFMIN(height-y+1, copyAhead+1), dstStride);



             

            for(i=height-y+1; i<=copyAhead; i++)

                    memcpy(tempDst + dstStride*i, dst + dstStride*(height-1), FFABS(dstStride));



            dstBlock= tempDst + dstStride;

            srcBlock= tempSrc;

        }



         

         

         

        for(x=0; x<width; x+=BLOCK_SIZE){

            const int stride= dstStride;


            uint8_t *tmpXchg;


            if(isColor){

                QP= QPptr[x>>qpHShift];

                c.nonBQP= nonBQPptr[x>>qpHShift];

            }else{

                QP= QPptr[x>>4];

                QP= (QP* QPCorrecture + 256*128)>>16;

                c.nonBQP= nonBQPptr[x>>4];

                c.nonBQP= (c.nonBQP* QPCorrecture + 256*128)>>16;

                yHistogram[ srcBlock[srcStride*12 + 4] ]++;

            }

            c.QP= QP;


            __asm__ volatile(

                "movd %1, %%mm7         \n\t"

                "packuswb %%mm7, %%mm7  \n\t"  

                "packuswb %%mm7, %%mm7  \n\t"  

                "packuswb %%mm7, %%mm7  \n\t"  

                "movq %%mm7, %0         \n\t"

                : "=m" (c.pQPb)

                : "r" (QP)

            );



 



            __asm__(

                "mov %4, %%"REG_a"              \n\t"

                "shr $2, %%"REG_a"              \n\t"

                "and $6, %%"REG_a"              \n\t"

                "add %5, %%"REG_a"              \n\t"

                "mov %%"REG_a", %%"REG_d"       \n\t"

                "imul %1, %%"REG_a"             \n\t"

                "imul %3, %%"REG_d"             \n\t"

                "prefetchnta 32(%%"REG_a", %0)  \n\t"

                "prefetcht0 32(%%"REG_d", %2)   \n\t"

                "add %1, %%"REG_a"              \n\t"

                "add %3, %%"REG_d"              \n\t"

                "prefetchnta 32(%%"REG_a", %0)  \n\t"

                "prefetcht0 32(%%"REG_d", %2)   \n\t"

                :: "r" (srcBlock), "r" ((x86_reg)srcStride), "r" (dstBlock), "r" ((x86_reg)dstStride),

                "g" ((x86_reg)x), "g" ((x86_reg)copyAhead)

                : "%"REG_a, "%"REG_d

            );





            RENAME(blockCopy)(dstBlock + dstStride*copyAhead, dstStride,

                              srcBlock + srcStride*copyAhead, srcStride, mode & LEVEL_FIX, &c.packedYOffset);



            if(mode & LINEAR_IPOL_DEINT_FILTER)

                RENAME(deInterlaceInterpolateLinear)(dstBlock, dstStride);

            else if(mode & LINEAR_BLEND_DEINT_FILTER)

                RENAME(deInterlaceBlendLinear)(dstBlock, dstStride, c.deintTemp + x);

            else if(mode & MEDIAN_DEINT_FILTER)

                RENAME(deInterlaceMedian)(dstBlock, dstStride);

            else if(mode & CUBIC_IPOL_DEINT_FILTER)

                RENAME(deInterlaceInterpolateCubic)(dstBlock, dstStride);

            else if(mode & FFMPEG_DEINT_FILTER)

                RENAME(deInterlaceFF)(dstBlock, dstStride, c.deintTemp + x);

            else if(mode & LOWPASS5_DEINT_FILTER)

                RENAME(deInterlaceL5)(dstBlock, dstStride, c.deintTemp + x, c.deintTemp + width + x);

 



             

            if(y + 8 < height){

                if(mode & V_X1_FILTER)

                    RENAME(vertX1Filter)(dstBlock, stride, &c);

                else if(mode & V_DEBLOCK){

                    const int t= RENAME(vertClassify)(dstBlock, stride, &c);



                    if(t==1)

                        RENAME(doVertLowPass)(dstBlock, stride, &c);

                    else if(t==2)

                        RENAME(doVertDefFilter)(dstBlock, stride, &c);

                }else if(mode & V_A_DEBLOCK){

                    RENAME(do_a_deblock)(dstBlock, stride, 1, &c);

                }

            }


            RENAME(transpose1)(tempBlock1, tempBlock2, dstBlock, dstStride);


             

            if(x - 8 >= 0){


                if(mode & H_X1_FILTER)

                        RENAME(vertX1Filter)(tempBlock1, 16, &c);

                else if(mode & H_DEBLOCK){

 

                    const int t= RENAME(vertClassify)(tempBlock1, 16, &c);

 

                    if(t==1)

                        RENAME(doVertLowPass)(tempBlock1, 16, &c);

                    else if(t==2)

                        RENAME(doVertDefFilter)(tempBlock1, 16, &c);

                }else if(mode & H_A_DEBLOCK){

                        RENAME(do_a_deblock)(tempBlock1, 16, 1, &c);

                }



                RENAME(transpose2)(dstBlock-4, dstStride, tempBlock1 + 4*16);


                if(mode & H_X1_FILTER)

                    horizX1Filter(dstBlock-4, stride, QP);

                else if(mode & H_DEBLOCK){


                    DECLARE_ALIGNED(16, unsigned char, tempBlock)[272];

                    int t;

                    transpose_16x8_char_toPackedAlign_altivec(tempBlock, dstBlock - (4 + 1), stride);



                    t = vertClassify_altivec(tempBlock-48, 16, &c);

                    if(t==1) {

                        doVertLowPass_altivec(tempBlock-48, 16, &c);

                        transpose_8x16_char_fromPackedAlign_altivec(dstBlock - (4 + 1), tempBlock, stride);

                    }

                    else if(t==2) {

                        doVertDefFilter_altivec(tempBlock-48, 16, &c);

                        transpose_8x16_char_fromPackedAlign_altivec(dstBlock - (4 + 1), tempBlock, stride);

                    }


                    const int t= RENAME(horizClassify)(dstBlock-4, stride, &c);



                    if(t==1)

                        RENAME(doHorizLowPass)(dstBlock-4, stride, &c);

                    else if(t==2)

                        RENAME(doHorizDefFilter)(dstBlock-4, stride, &c);


                }else if(mode & H_A_DEBLOCK){

                    RENAME(do_a_deblock)(dstBlock-8, 1, stride, &c);

                }


                if(mode & DERING){

                 

                    if(y>0) RENAME(dering)(dstBlock - stride - 8, stride, &c);

                }



                if(mode & TEMP_NOISE_FILTER)

                {

                    RENAME(tempNoiseReducer)(dstBlock-8, stride,

                            c.tempBlurred[isColor] + y*dstStride + x,

                            c.tempBlurredPast[isColor] + (y>>3)*256 + (x>>3) + 256,

                            c.ppMode.maxTmpNoise);

                }

            }



            dstBlock+=8;

            srcBlock+=8;


            tmpXchg= tempBlock1;

            tempBlock1= tempBlock2;

            tempBlock2 = tmpXchg;


        }



        if(mode & DERING){

            if(y > 0) RENAME(dering)(dstBlock - dstStride - 8, dstStride, &c);

        }



        if((mode & TEMP_NOISE_FILTER)){

            RENAME(tempNoiseReducer)(dstBlock-8, dstStride,

                    c.tempBlurred[isColor] + y*dstStride + x,

                    c.tempBlurredPast[isColor] + (y>>3)*256 + (x>>3) + 256,

                    c.ppMode.maxTmpNoise);

        }



         

        if(y+15 >= height){

            uint8_t *dstBlock= &(dst[y*dstStride]);

            if(width==FFABS(dstStride))

                linecpy(dstBlock, tempDst + dstStride, height-y, dstStride);

            else{

                int i;

                for(i=0; i<height-y; i++){

                    memcpy(dstBlock + i*dstStride, tempDst + (i+1)*dstStride, width);

                }

            }

        }

 

    }


    __asm__ volatile("femms");


    __asm__ volatile("emms");



    if(!isColor){

        int max=1;

        int i;

        for(i=0; i<256; i++)

            if(yHistogram[i] > max) max=yHistogram[i];



        for(i=1; i<256; i++){

            int x;

            int start=yHistogram[i-1]/(max/256+1);

            int end=yHistogram[i]/(max/256+1);

            int inc= end > start ? 1 : -1;

            for(x=start; x!=end+inc; x+=inc)

                dst[ i*dstStride + x]+=128;

        }



        for(i=0; i<100; i+=2){

            dst[ (white)*dstStride + i]+=128;

            dst[ (black)*dstStride + i]+=128;

        }

    }




    *c2= c;  



}
