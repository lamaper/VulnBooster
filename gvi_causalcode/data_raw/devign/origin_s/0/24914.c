static int swScale(SwsContext *c, const uint8_t* src[],

                   int srcStride[], int srcSliceY,

                   int srcSliceH, uint8_t* dst[], int dstStride[])

{

     

    const int srcW= c->srcW;

    const int dstW= c->dstW;

    const int dstH= c->dstH;

    const int chrDstW= c->chrDstW;

    const int chrSrcW= c->chrSrcW;

    const int lumXInc= c->lumXInc;

    const int chrXInc= c->chrXInc;

    const enum PixelFormat dstFormat= c->dstFormat;

    const int flags= c->flags;

    int16_t *vLumFilterPos= c->vLumFilterPos;

    int16_t *vChrFilterPos= c->vChrFilterPos;

    int16_t *hLumFilterPos= c->hLumFilterPos;

    int16_t *hChrFilterPos= c->hChrFilterPos;

    int16_t *vLumFilter= c->vLumFilter;

    int16_t *vChrFilter= c->vChrFilter;

    int16_t *hLumFilter= c->hLumFilter;

    int16_t *hChrFilter= c->hChrFilter;

    int32_t *lumMmxFilter= c->lumMmxFilter;

    int32_t *chrMmxFilter= c->chrMmxFilter;

    int32_t av_unused *alpMmxFilter= c->alpMmxFilter;

    const int vLumFilterSize= c->vLumFilterSize;

    const int vChrFilterSize= c->vChrFilterSize;

    const int hLumFilterSize= c->hLumFilterSize;

    const int hChrFilterSize= c->hChrFilterSize;

    int16_t **lumPixBuf= c->lumPixBuf;

    int16_t **chrUPixBuf= c->chrUPixBuf;

    int16_t **chrVPixBuf= c->chrVPixBuf;

    int16_t **alpPixBuf= c->alpPixBuf;

    const int vLumBufSize= c->vLumBufSize;

    const int vChrBufSize= c->vChrBufSize;

    uint8_t *formatConvBuffer= c->formatConvBuffer;

    const int chrSrcSliceY= srcSliceY >> c->chrSrcVSubSample;

    const int chrSrcSliceH= -((-srcSliceH) >> c->chrSrcVSubSample);

    int lastDstY;

    uint32_t *pal=c->pal_yuv;

    yuv2planar1_fn yuv2yuv1 = c->yuv2yuv1;

    yuv2planarX_fn yuv2yuvX = c->yuv2yuvX;

    yuv2packed1_fn yuv2packed1 = c->yuv2packed1;

    yuv2packed2_fn yuv2packed2 = c->yuv2packed2;

    yuv2packedX_fn yuv2packedX = c->yuv2packedX;



     

    int dstY= c->dstY;

    int lumBufIndex= c->lumBufIndex;

    int chrBufIndex= c->chrBufIndex;

    int lastInLumBuf= c->lastInLumBuf;

    int lastInChrBuf= c->lastInChrBuf;



    if (isPacked(c->srcFormat)) {

        src[0]=

        src[1]=

        src[2]=

        src[3]= src[0];

        srcStride[0]=

        srcStride[1]=

        srcStride[2]=

        srcStride[3]= srcStride[0];

    }

    srcStride[1]<<= c->vChrDrop;

    srcStride[2]<<= c->vChrDrop;



    DEBUG_BUFFERS("swScale() %p[%d] %p[%d] %p[%d] %p[%d] -> %p[%d] %p[%d] %p[%d] %p[%d]\n",

                  src[0], srcStride[0], src[1], srcStride[1], src[2], srcStride[2], src[3], srcStride[3],

                  dst[0], dstStride[0], dst[1], dstStride[1], dst[2], dstStride[2], dst[3], dstStride[3]);

    DEBUG_BUFFERS("srcSliceY: %d srcSliceH: %d dstY: %d dstH: %d\n",

                   srcSliceY,    srcSliceH,    dstY,    dstH);

    DEBUG_BUFFERS("vLumFilterSize: %d vLumBufSize: %d vChrFilterSize: %d vChrBufSize: %d\n",

                   vLumFilterSize,    vLumBufSize,    vChrFilterSize,    vChrBufSize);



    if (dstStride[0]%8 !=0 || dstStride[1]%8 !=0 || dstStride[2]%8 !=0 || dstStride[3]%8 != 0) {

        static int warnedAlready=0;  

        if (flags & SWS_PRINT_INFO && !warnedAlready) {

            av_log(c, AV_LOG_WARNING, "Warning: dstStride is not aligned!\n"

                   "         ->cannot do aligned memory accesses anymore\n");

            warnedAlready=1;

        }

    }



     

    if (srcSliceY ==0) {

        lumBufIndex=-1;

        chrBufIndex=-1;

        dstY=0;

        lastInLumBuf= -1;

        lastInChrBuf= -1;

    }



    lastDstY= dstY;



    for (;dstY < dstH; dstY++) {

        unsigned char *dest =dst[0]+dstStride[0]*dstY;

        const int chrDstY= dstY>>c->chrDstVSubSample;

        unsigned char *uDest=dst[1]+dstStride[1]*chrDstY;

        unsigned char *vDest=dst[2]+dstStride[2]*chrDstY;

        unsigned char *aDest=(CONFIG_SWSCALE_ALPHA && alpPixBuf) ? dst[3]+dstStride[3]*dstY : NULL;



        const int firstLumSrcY= vLumFilterPos[dstY];  

        const int firstLumSrcY2= vLumFilterPos[FFMIN(dstY | ((1<<c->chrDstVSubSample) - 1), dstH-1)];

        const int firstChrSrcY= vChrFilterPos[chrDstY];  

        int lastLumSrcY= firstLumSrcY + vLumFilterSize -1;  

        int lastLumSrcY2=firstLumSrcY2+ vLumFilterSize -1;  

        int lastChrSrcY= firstChrSrcY + vChrFilterSize -1;  

        int enough_lines;



         

        if (firstLumSrcY > lastInLumBuf) lastInLumBuf= firstLumSrcY-1;

        if (firstChrSrcY > lastInChrBuf) lastInChrBuf= firstChrSrcY-1;

        assert(firstLumSrcY >= lastInLumBuf - vLumBufSize + 1);

        assert(firstChrSrcY >= lastInChrBuf - vChrBufSize + 1);



        DEBUG_BUFFERS("dstY: %d\n", dstY);

        DEBUG_BUFFERS("\tfirstLumSrcY: %d lastLumSrcY: %d lastInLumBuf: %d\n",

                         firstLumSrcY,    lastLumSrcY,    lastInLumBuf);

        DEBUG_BUFFERS("\tfirstChrSrcY: %d lastChrSrcY: %d lastInChrBuf: %d\n",

                         firstChrSrcY,    lastChrSrcY,    lastInChrBuf);



         

        enough_lines = lastLumSrcY2 < srcSliceY + srcSliceH && lastChrSrcY < -((-srcSliceY - srcSliceH)>>c->chrSrcVSubSample);



        if (!enough_lines) {

            lastLumSrcY = srcSliceY + srcSliceH - 1;

            lastChrSrcY = chrSrcSliceY + chrSrcSliceH - 1;

            DEBUG_BUFFERS("buffering slice: lastLumSrcY %d lastChrSrcY %d\n",

                                            lastLumSrcY, lastChrSrcY);

        }



         

        while(lastInLumBuf < lastLumSrcY) {

            const uint8_t *src1= src[0]+(lastInLumBuf + 1 - srcSliceY)*srcStride[0];

            const uint8_t *src2= src[3]+(lastInLumBuf + 1 - srcSliceY)*srcStride[3];

            lumBufIndex++;

            assert(lumBufIndex < 2*vLumBufSize);

            assert(lastInLumBuf + 1 - srcSliceY < srcSliceH);

            assert(lastInLumBuf + 1 - srcSliceY >= 0);

            hyscale(c, lumPixBuf[ lumBufIndex ], dstW, src1, srcW, lumXInc,

                    hLumFilter, hLumFilterPos, hLumFilterSize,

                    formatConvBuffer,

                    pal, 0);

            if (CONFIG_SWSCALE_ALPHA && alpPixBuf)

                hyscale(c, alpPixBuf[ lumBufIndex ], dstW, src2, srcW,

                        lumXInc, hLumFilter, hLumFilterPos, hLumFilterSize,

                        formatConvBuffer,

                        pal, 1);

            lastInLumBuf++;

            DEBUG_BUFFERS("\t\tlumBufIndex %d: lastInLumBuf: %d\n",

                               lumBufIndex,    lastInLumBuf);

        }

        while(lastInChrBuf < lastChrSrcY) {

            const uint8_t *src1= src[1]+(lastInChrBuf + 1 - chrSrcSliceY)*srcStride[1];

            const uint8_t *src2= src[2]+(lastInChrBuf + 1 - chrSrcSliceY)*srcStride[2];

            chrBufIndex++;

            assert(chrBufIndex < 2*vChrBufSize);

            assert(lastInChrBuf + 1 - chrSrcSliceY < (chrSrcSliceH));

            assert(lastInChrBuf + 1 - chrSrcSliceY >= 0);

             



            if (c->needs_hcscale)

                hcscale(c, chrUPixBuf[chrBufIndex], chrVPixBuf[chrBufIndex],

                          chrDstW, src1, src2, chrSrcW, chrXInc,

                          hChrFilter, hChrFilterPos, hChrFilterSize,

                          formatConvBuffer, pal);

            lastInChrBuf++;

            DEBUG_BUFFERS("\t\tchrBufIndex %d: lastInChrBuf: %d\n",

                               chrBufIndex,    lastInChrBuf);

        }

         

        if (lumBufIndex >= vLumBufSize) lumBufIndex-= vLumBufSize;

        if (chrBufIndex >= vChrBufSize) chrBufIndex-= vChrBufSize;

        if (!enough_lines)

            break;  


        updateMMXDitherTables(c, dstY, lumBufIndex, chrBufIndex, lastInLumBuf, lastInChrBuf);


        if (dstY >= dstH-2) {

             

            find_c_packed_planar_out_funcs(c, &yuv2yuv1, &yuv2yuvX,

                                           &yuv2packed1, &yuv2packed2,

                                           &yuv2packedX);

        }



        {

            const int16_t **lumSrcPtr= (const int16_t **) lumPixBuf + lumBufIndex + firstLumSrcY - lastInLumBuf + vLumBufSize;

            const int16_t **chrUSrcPtr= (const int16_t **) chrUPixBuf + chrBufIndex + firstChrSrcY - lastInChrBuf + vChrBufSize;

            const int16_t **chrVSrcPtr= (const int16_t **) chrVPixBuf + chrBufIndex + firstChrSrcY - lastInChrBuf + vChrBufSize;

            const int16_t **alpSrcPtr= (CONFIG_SWSCALE_ALPHA && alpPixBuf) ? (const int16_t **) alpPixBuf + lumBufIndex + firstLumSrcY - lastInLumBuf + vLumBufSize : NULL;

            if (isPlanarYUV(dstFormat) || dstFormat==PIX_FMT_GRAY8) {  

                const int chrSkipMask= (1<<c->chrDstVSubSample)-1;

                if ((dstY&chrSkipMask) || isGray(dstFormat)) uDest=vDest= NULL;  

                if (c->yuv2yuv1 && vLumFilterSize == 1 && vChrFilterSize == 1) {  

                    const int16_t *lumBuf = lumSrcPtr[0];

                    const int16_t *chrUBuf= chrUSrcPtr[0];

                    const int16_t *chrVBuf= chrVSrcPtr[0];

                    const int16_t *alpBuf= (CONFIG_SWSCALE_ALPHA && alpPixBuf) ? alpSrcPtr[0] : NULL;

                    yuv2yuv1(c, lumBuf, chrUBuf, chrVBuf, alpBuf, dest,

                                uDest, vDest, aDest, dstW, chrDstW);

                } else {  

                    yuv2yuvX(c,

                                vLumFilter+dstY*vLumFilterSize   , lumSrcPtr, vLumFilterSize,

                                vChrFilter+chrDstY*vChrFilterSize, chrUSrcPtr,

                                chrVSrcPtr, vChrFilterSize,

                                alpSrcPtr, dest, uDest, vDest, aDest, dstW, chrDstW);

                }

            } else {

                assert(lumSrcPtr  + vLumFilterSize - 1 < lumPixBuf  + vLumBufSize*2);

                assert(chrUSrcPtr + vChrFilterSize - 1 < chrUPixBuf + vChrBufSize*2);

                if (c->yuv2packed1 && vLumFilterSize == 1 && vChrFilterSize == 2) {  

                    int chrAlpha= vChrFilter[2*dstY+1];

                    yuv2packed1(c, *lumSrcPtr, *chrUSrcPtr, *(chrUSrcPtr+1),

                                   *chrVSrcPtr, *(chrVSrcPtr+1),

                                   alpPixBuf ? *alpSrcPtr : NULL,

                                   dest, dstW, chrAlpha, dstFormat, flags, dstY);

                } else if (c->yuv2packed2 && vLumFilterSize == 2 && vChrFilterSize == 2) {  

                    int lumAlpha= vLumFilter[2*dstY+1];

                    int chrAlpha= vChrFilter[2*dstY+1];

                    lumMmxFilter[2]=

                    lumMmxFilter[3]= vLumFilter[2*dstY   ]*0x10001;

                    chrMmxFilter[2]=

                    chrMmxFilter[3]= vChrFilter[2*chrDstY]*0x10001;

                    yuv2packed2(c, *lumSrcPtr, *(lumSrcPtr+1), *chrUSrcPtr, *(chrUSrcPtr+1),

                                   *chrVSrcPtr, *(chrVSrcPtr+1),

                                   alpPixBuf ? *alpSrcPtr : NULL, alpPixBuf ? *(alpSrcPtr+1) : NULL,

                                   dest, dstW, lumAlpha, chrAlpha, dstY);

                } else {  

                    yuv2packedX(c,

                                   vLumFilter+dstY*vLumFilterSize, lumSrcPtr, vLumFilterSize,

                                   vChrFilter+dstY*vChrFilterSize, chrUSrcPtr, chrVSrcPtr, vChrFilterSize,

                                   alpSrcPtr, dest, dstW, dstY);

                }

            }

        }

    }



    if ((dstFormat == PIX_FMT_YUVA420P) && !alpPixBuf)

        fillPlane(dst[3], dstStride[3], dstW, dstY-lastDstY, lastDstY, 255);


    if (av_get_cpu_flags() & AV_CPU_FLAG_MMX2)

        __asm__ volatile("sfence":::"memory");


    emms_c();



     

    c->dstY= dstY;

    c->lumBufIndex= lumBufIndex;

    c->chrBufIndex= chrBufIndex;

    c->lastInLumBuf= lastInLumBuf;

    c->lastInChrBuf= lastInChrBuf;



    return dstY - lastDstY;

}
