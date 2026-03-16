static void RENAME(swScale)(SwsContext *c, uint8_t* srcParam[], int srcStrideParam[], int srcSliceY,

             int srcSliceH, uint8_t* dstParam[], int dstStride[]){



	 

	const int srcW= c->srcW;

	const int dstW= c->dstW;

	const int dstH= c->dstH;

	const int chrDstW= c->chrDstW;

	const int lumXInc= c->lumXInc;

	const int chrXInc= c->chrXInc;

	const int dstFormat= c->dstFormat;

	const int flags= c->flags;

	const int canMMX2BeUsed= c->canMMX2BeUsed;

	int16_t *vLumFilterPos= c->vLumFilterPos;

	int16_t *vChrFilterPos= c->vChrFilterPos;

	int16_t *hLumFilterPos= c->hLumFilterPos;

	int16_t *hChrFilterPos= c->hChrFilterPos;

	int16_t *vLumFilter= c->vLumFilter;

	int16_t *vChrFilter= c->vChrFilter;

	int16_t *hLumFilter= c->hLumFilter;

	int16_t *hChrFilter= c->hChrFilter;

	int16_t *lumMmxFilter= c->lumMmxFilter;

	int16_t *chrMmxFilter= c->chrMmxFilter;

	const int vLumFilterSize= c->vLumFilterSize;

	const int vChrFilterSize= c->vChrFilterSize;

	const int hLumFilterSize= c->hLumFilterSize;

	const int hChrFilterSize= c->hChrFilterSize;

	int16_t **lumPixBuf= c->lumPixBuf;

	int16_t **chrPixBuf= c->chrPixBuf;

	const int vLumBufSize= c->vLumBufSize;

	const int vChrBufSize= c->vChrBufSize;

	uint8_t *funnyYCode= c->funnyYCode;

	uint8_t *funnyUVCode= c->funnyUVCode;

	uint8_t *formatConvBuffer= c->formatConvBuffer;



	 

	int dstY= c->dstY;

	int lumBufIndex= c->lumBufIndex;

	int chrBufIndex= c->chrBufIndex;

	int lastInLumBuf= c->lastInLumBuf;

	int lastInChrBuf= c->lastInChrBuf;

	int srcStride[3];

	uint8_t *src[3];

	uint8_t *dst[3];

	

	if((c->srcFormat == IMGFMT_IYUV) || (c->srcFormat == IMGFMT_I420)){

		src[0]= srcParam[0];

		src[1]= srcParam[2];

		src[2]= srcParam[1];

		srcStride[0]= srcStrideParam[0];

		srcStride[1]= srcStrideParam[2];

		srcStride[2]= srcStrideParam[1];

	}

	else if(c->srcFormat==IMGFMT_YV12){

		src[0]= srcParam[0];

		src[1]= srcParam[1];

		src[2]= srcParam[2];

		srcStride[0]= srcStrideParam[0];

		srcStride[1]= srcStrideParam[1];

		srcStride[2]= srcStrideParam[2];

	}

	else if(isPacked(c->srcFormat)){

		src[0]=

		src[1]=

		src[2]= srcParam[0];

		srcStride[0]= srcStrideParam[0];

		srcStride[1]=

		srcStride[2]= srcStrideParam[0]<<1;

	}

	else if(c->srcFormat==IMGFMT_Y8){

		src[0]= srcParam[0];

		src[1]=

		src[2]= NULL;

		srcStride[0]= srcStrideParam[0];

		srcStride[1]=

		srcStride[2]= 0;

	}



	if((c->dstFormat == IMGFMT_IYUV) || (c->dstFormat == IMGFMT_I420)){

		dst[0]= dstParam[0];

		dst[1]= dstParam[2];

		dst[2]= dstParam[1];

		

	}else{

		dst[0]= dstParam[0];

		dst[1]= dstParam[1];

		dst[2]= dstParam[2];

	}

	



	if(dstStride[0]%8 !=0 || dstStride[1]%8 !=0 || dstStride[2]%8 !=0)

	{

		static int firstTime=1;  

		if(flags & SWS_PRINT_INFO && firstTime)

		{

			fprintf(stderr, "SwScaler: Warning: dstStride is not aligned!\n"

					"SwScaler:          ->cannot do aligned memory acesses anymore\n");

			firstTime=0;

		}

	}



	 

	if(srcSliceY ==0){

		lumBufIndex=0;

		chrBufIndex=0;

		dstY=0;	

		lastInLumBuf= -1;

		lastInChrBuf= -1;

	}



	for(;dstY < dstH; dstY++){

		unsigned char *dest =dst[0]+dstStride[0]*dstY;

		unsigned char *uDest=dst[1]+dstStride[1]*(dstY>>1);

		unsigned char *vDest=dst[2]+dstStride[2]*(dstY>>1);

		const int chrDstY= isHalfChrV(dstFormat) ? (dstY>>1) : dstY;



		const int firstLumSrcY= vLumFilterPos[dstY];  

		const int firstChrSrcY= vChrFilterPos[chrDstY];  

		const int lastLumSrcY= firstLumSrcY + vLumFilterSize -1;  

		const int lastChrSrcY= firstChrSrcY + vChrFilterSize -1;  



		 

		if(firstLumSrcY > lastInLumBuf) lastInLumBuf= firstLumSrcY-1;

		if(firstChrSrcY > lastInChrBuf) lastInChrBuf= firstChrSrcY-1;

 

		ASSERT(firstLumSrcY >= lastInLumBuf - vLumBufSize + 1)

		ASSERT(firstChrSrcY >= lastInChrBuf - vChrBufSize + 1)



		 

		if(lastLumSrcY < srcSliceY + srcSliceH && lastChrSrcY < ((srcSliceY + srcSliceH)>>1))

		{

			 

			while(lastInLumBuf < lastLumSrcY)

			{

				uint8_t *s= src[0]+(lastInLumBuf + 1 - srcSliceY)*srcStride[0];

				lumBufIndex++;

 

				ASSERT(lumBufIndex < 2*vLumBufSize)

				ASSERT(lastInLumBuf + 1 - srcSliceY < srcSliceH)

				ASSERT(lastInLumBuf + 1 - srcSliceY >= 0)

 

				RENAME(hyscale)(lumPixBuf[ lumBufIndex ], dstW, s, srcW, lumXInc,

						flags, canMMX2BeUsed, hLumFilter, hLumFilterPos, hLumFilterSize,

						funnyYCode, c->srcFormat, formatConvBuffer);

				lastInLumBuf++;

			}

			while(lastInChrBuf < lastChrSrcY)

			{

				uint8_t *src1= src[1]+(lastInChrBuf + 1 - (srcSliceY>>1))*srcStride[1];

				uint8_t *src2= src[2]+(lastInChrBuf + 1 - (srcSliceY>>1))*srcStride[2];

				chrBufIndex++;

				ASSERT(chrBufIndex < 2*vChrBufSize)

				ASSERT(lastInChrBuf + 1 - (srcSliceY>>1) < (srcSliceH>>1))

				ASSERT(lastInChrBuf + 1 - (srcSliceY>>1) >= 0)

				 

				RENAME(hcscale)(chrPixBuf[ chrBufIndex ], chrDstW, src1, src2, (srcW+1)>>1, chrXInc,

						flags, canMMX2BeUsed, hChrFilter, hChrFilterPos, hChrFilterSize,

						funnyUVCode, c->srcFormat, formatConvBuffer);

				lastInChrBuf++;

			}

			 

			if(lumBufIndex >= vLumBufSize ) lumBufIndex-= vLumBufSize;

			if(chrBufIndex >= vChrBufSize ) chrBufIndex-= vChrBufSize;

		}

		else  

		{

 

			 

			while(lastInLumBuf+1 < srcSliceY + srcSliceH)

			{

				uint8_t *s= src[0]+(lastInLumBuf + 1 - srcSliceY)*srcStride[0];

				lumBufIndex++;

				ASSERT(lumBufIndex < 2*vLumBufSize)

				ASSERT(lastInLumBuf + 1 - srcSliceY < srcSliceH)

				ASSERT(lastInLumBuf + 1 - srcSliceY >= 0)

				RENAME(hyscale)(lumPixBuf[ lumBufIndex ], dstW, s, srcW, lumXInc,

						flags, canMMX2BeUsed, hLumFilter, hLumFilterPos, hLumFilterSize,

						funnyYCode, c->srcFormat, formatConvBuffer);

				lastInLumBuf++;

			}

			while(lastInChrBuf+1 < ((srcSliceY + srcSliceH)>>1))

			{

				uint8_t *src1= src[1]+(lastInChrBuf + 1 - (srcSliceY>>1))*srcStride[1];

				uint8_t *src2= src[2]+(lastInChrBuf + 1 - (srcSliceY>>1))*srcStride[2];

				chrBufIndex++;

				ASSERT(chrBufIndex < 2*vChrBufSize)

				ASSERT(lastInChrBuf + 1 - (srcSliceY>>1) < (srcSliceH>>1))

				ASSERT(lastInChrBuf + 1 - (srcSliceY>>1) >= 0)

				RENAME(hcscale)(chrPixBuf[ chrBufIndex ], chrDstW, src1, src2, (srcW+1)>>1, chrXInc,

						flags, canMMX2BeUsed, hChrFilter, hChrFilterPos, hChrFilterSize,

						funnyUVCode, c->srcFormat, formatConvBuffer);

				lastInChrBuf++;

			}

			 

			if(lumBufIndex >= vLumBufSize ) lumBufIndex-= vLumBufSize;

			if(chrBufIndex >= vChrBufSize ) chrBufIndex-= vChrBufSize;

			break;  

		}


		b5Dither= dither8[dstY&1];

		g6Dither= dither4[dstY&1];

		g5Dither= dither8[dstY&1];

		r5Dither= dither8[(dstY+1)&1];


	    if(dstY < dstH-2)

	    {

		if(isPlanarYUV(dstFormat))  

		{

			if(dstY&1) uDest=vDest= NULL;  

			if(vLumFilterSize == 1 && vChrFilterSize == 1)  

			{

				int16_t *lumBuf = lumPixBuf[0];

				int16_t *chrBuf= chrPixBuf[0];

				RENAME(yuv2yuv1)(lumBuf, chrBuf, dest, uDest, vDest, dstW);

			}

			else  

			{

				int16_t **lumSrcPtr= lumPixBuf + lumBufIndex + firstLumSrcY - lastInLumBuf + vLumBufSize;

				int16_t **chrSrcPtr= chrPixBuf + chrBufIndex + firstChrSrcY - lastInChrBuf + vChrBufSize;

				RENAME(yuv2yuvX)(

					vLumFilter+dstY*vLumFilterSize     , lumSrcPtr, vLumFilterSize,

					vChrFilter+(dstY>>1)*vChrFilterSize, chrSrcPtr, vChrFilterSize,

					dest, uDest, vDest, dstW,

					lumMmxFilter+dstY*vLumFilterSize*4, chrMmxFilter+(dstY>>1)*vChrFilterSize*4);

			}

		}

		else

		{

			int16_t **lumSrcPtr= lumPixBuf + lumBufIndex + firstLumSrcY - lastInLumBuf + vLumBufSize;

			int16_t **chrSrcPtr= chrPixBuf + chrBufIndex + firstChrSrcY - lastInChrBuf + vChrBufSize;



			ASSERT(lumSrcPtr + vLumFilterSize - 1 < lumPixBuf + vLumBufSize*2);

			ASSERT(chrSrcPtr + vChrFilterSize - 1 < chrPixBuf + vChrBufSize*2);

			if(vLumFilterSize == 1 && vChrFilterSize == 2)  

			{

				int chrAlpha= vChrFilter[2*dstY+1];



				RENAME(yuv2rgb1)(*lumSrcPtr, *chrSrcPtr, *(chrSrcPtr+1),

						 dest, dstW, chrAlpha, dstFormat, flags);

			}

			else if(vLumFilterSize == 2 && vChrFilterSize == 2)  

			{

				int lumAlpha= vLumFilter[2*dstY+1];

				int chrAlpha= vChrFilter[2*dstY+1];



				RENAME(yuv2rgb2)(*lumSrcPtr, *(lumSrcPtr+1), *chrSrcPtr, *(chrSrcPtr+1),

						 dest, dstW, lumAlpha, chrAlpha, dstFormat, flags);

			}

			else  

			{

				RENAME(yuv2rgbX)(

					vLumFilter+dstY*vLumFilterSize, lumSrcPtr, vLumFilterSize,

					vChrFilter+dstY*vChrFilterSize, chrSrcPtr, vChrFilterSize,

					dest, dstW, dstFormat,

					lumMmxFilter+dstY*vLumFilterSize*4, chrMmxFilter+dstY*vChrFilterSize*4);

			}

		}

            }

	    else  

	    {

		int16_t **lumSrcPtr= lumPixBuf + lumBufIndex + firstLumSrcY - lastInLumBuf + vLumBufSize;

		int16_t **chrSrcPtr= chrPixBuf + chrBufIndex + firstChrSrcY - lastInChrBuf + vChrBufSize;

		if(isPlanarYUV(dstFormat))  

		{

			if(dstY&1) uDest=vDest= NULL;  

			yuv2yuvXinC(

				vLumFilter+dstY*vLumFilterSize     , lumSrcPtr, vLumFilterSize,

				vChrFilter+(dstY>>1)*vChrFilterSize, chrSrcPtr, vChrFilterSize,

				dest, uDest, vDest, dstW);

		}

		else

		{

			ASSERT(lumSrcPtr + vLumFilterSize - 1 < lumPixBuf + vLumBufSize*2);

			ASSERT(chrSrcPtr + vChrFilterSize - 1 < chrPixBuf + vChrBufSize*2);

			yuv2rgbXinC(

				vLumFilter+dstY*vLumFilterSize, lumSrcPtr, vLumFilterSize,

				vChrFilter+dstY*vChrFilterSize, chrSrcPtr, vChrFilterSize,

				dest, dstW, dstFormat);

		}

	    }

	}


	__asm __volatile(SFENCE:::"memory");

	__asm __volatile(EMMS:::"memory");


	 

	c->dstY= dstY;

	c->lumBufIndex= lumBufIndex;

	c->chrBufIndex= chrBufIndex;

	c->lastInLumBuf= lastInLumBuf;

	c->lastInChrBuf= lastInChrBuf;

}
