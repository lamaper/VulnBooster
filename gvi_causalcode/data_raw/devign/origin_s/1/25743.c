static void RENAME(SwScale_YV12slice)(unsigned char* srcptr[],int stride[], int srcSliceY ,

			     int srcSliceH, uint8_t* dstptr[], int dststride, int dstbpp,

			     int srcW, int srcH, int dstW, int dstH){





unsigned int lumXInc= (srcW << 16) / dstW;

unsigned int lumYInc= (srcH << 16) / dstH;

unsigned int chrXInc;

unsigned int chrYInc;



static int dstY;



 

static int oldDstW= -1;

static int oldSrcW= -1;

static int oldDstH= -1;

static int oldSrcH= -1;

static int oldFlags=-1;



static int lastInLumBuf;

static int lastInChrBuf;



int chrDstW, chrDstH;



static int lumBufIndex=0;

static int chrBufIndex=0;



static int firstTime=1;



int widthAlign= dstbpp==12 ? 16 : 8;

if(((dstW + widthAlign-1)&(~(widthAlign-1))) > dststride)

{

	dstW&= ~(widthAlign-1);

	if(firstTime)

		fprintf(stderr, "SwScaler: Warning: dstStride is not a multiple of %d!\n"

				"SwScaler: ->lowering width to compensate, new width=%d\n"

				"SwScaler: ->cannot do aligned memory acesses anymore\n",

				widthAlign, dstW);

}


canMMX2BeUsed= (lumXInc <= 0x10000 && (dstW&31)==0 && (srcW&15)==0) ? 1 : 0;

if(!canMMX2BeUsed && lumXInc <= 0x10000 && (srcW&15)==0 && sws_flags==SWS_FAST_BILINEAR)

{

	if(firstTime)  

		fprintf(stderr, "SwScaler: output Width is not a multiple of 32 -> no MMX2 scaler\n");

}




if(firstTime)

{


	char *dither= " dithered";


	char *dither= "";


	if(sws_flags==SWS_FAST_BILINEAR)

		fprintf(stderr, "SwScaler: FAST_BILINEAR scaler ");

	else if(sws_flags==SWS_BILINEAR)

		fprintf(stderr, "SwScaler: BILINEAR scaler ");

	else if(sws_flags==SWS_BICUBIC)

		fprintf(stderr, "SwScaler: BICUBIC scaler ");

	else

		fprintf(stderr, "SwScaler: ehh flags invalid?! ");



	if(dstbpp==15)

		fprintf(stderr, "with%s BGR15 output ", dither);

	else if(dstbpp==16)

		fprintf(stderr, "with%s BGR16 output ", dither);

	else if(dstbpp==24)

		fprintf(stderr, "with BGR24 output ");

	else if(dstbpp==32)

		fprintf(stderr, "with BGR32 output ");

	else if(dstbpp==12)

		fprintf(stderr, "with YV12 output ");

	else

		fprintf(stderr, "without output ");


		fprintf(stderr, "using MMX2\n");


		fprintf(stderr, "using 3DNOW\n");


		fprintf(stderr, "using MMX\n");


		fprintf(stderr, "using X86 ASM2\n");


		fprintf(stderr, "using C\n");


}





 

 

 

 

 

if(sws_flags==SWS_FAST_BILINEAR)

{

	if(canMMX2BeUsed) 	lumXInc+= 20;

	else			lumXInc = ((srcW-2)<<16)/(dstW-2) - 20;

}



if(fullUVIpol && !(dstbpp==12)) 	chrXInc= lumXInc>>1, chrDstW= dstW;

else					chrXInc= lumXInc,    chrDstW= dstW>>1;



if(dstbpp==12)	chrYInc= lumYInc,    chrDstH= dstH>>1;

else		chrYInc= lumYInc>>1, chrDstH= dstH;



   



  if(srcSliceY ==0){

 

	lumBufIndex=0;

	chrBufIndex=0;

	dstY=0;



	 

	if(oldDstW!=dstW || oldSrcW!=srcW || oldFlags!=sws_flags)

	{


		const int filterAlign=4;


		const int filterAlign=1;


		oldDstW= dstW; oldSrcW= srcW; oldFlags= sws_flags;



		if(sws_flags != SWS_FAST_BILINEAR)

		{

			RENAME(initFilter)(hLumFilter, hLumFilterPos, &hLumFilterSize, lumXInc,

					   srcW   , dstW   , filterAlign, 1<<14);

			RENAME(initFilter)(hChrFilter, hChrFilterPos, &hChrFilterSize, chrXInc,

					   srcW>>1, chrDstW, filterAlign, 1<<14);

		}


 

		if(canMMX2BeUsed && sws_flags == SWS_FAST_BILINEAR)

		{

			initMMX2HScaler(dstW   , lumXInc, funnyYCode);

			initMMX2HScaler(chrDstW, chrXInc, funnyUVCode);

		}


	}  



	if(oldDstH!=dstH || oldSrcH!=srcH || oldFlags!=sws_flags)

	{

		int i;

		oldDstH= dstH; oldSrcH= srcH; oldFlags= sws_flags;  



		 

		for(i=0; i<vLumBufSize; i++) free(lumPixBuf[i]);

		for(i=0; i<vChrBufSize; i++) free(chrPixBuf[i]);



		RENAME(initFilter)(vLumFilter, vLumFilterPos, &vLumFilterSize, lumYInc,

				srcH   , dstH,    1, (1<<12)-4);

		RENAME(initFilter)(vChrFilter, vChrFilterPos, &vChrFilterSize, chrYInc,

				srcH>>1, chrDstH, 1, (1<<12)-4);



		 

		vLumBufSize= vLumFilterSize; vChrBufSize= vChrFilterSize;

		for(i=0; i<dstH; i++)

		{

			int chrI= i*chrDstH / dstH;

			int nextSlice= MAX(vLumFilterPos[i   ] + vLumFilterSize - 1,

					 ((vChrFilterPos[chrI] + vChrFilterSize - 1)<<1));

			nextSlice&= ~1;  

			if(vLumFilterPos[i   ] + vLumBufSize < nextSlice)

				vLumBufSize= nextSlice - vLumFilterPos[i   ];

			if(vChrFilterPos[chrI] + vChrBufSize < (nextSlice>>1))

				vChrBufSize= (nextSlice>>1) - vChrFilterPos[chrI];

		}



		 

		 

		for(i=0; i<vLumBufSize; i++)

			lumPixBuf[i]= lumPixBuf[i+vLumBufSize]= (uint16_t*)memalign(8, 4000);

		for(i=0; i<vChrBufSize; i++)

			chrPixBuf[i]= chrPixBuf[i+vChrBufSize]= (uint16_t*)memalign(8, 8000);



		 

		for(i=0; i<vLumBufSize; i++) memset(lumPixBuf[i], 0, 4000);

		for(i=0; i<vChrBufSize; i++) memset(chrPixBuf[i], 64, 8000);


		 

		for(i=0; i<vLumFilterSize*dstH; i++)

			lumMmxFilter[4*i]=lumMmxFilter[4*i+1]=lumMmxFilter[4*i+2]=lumMmxFilter[4*i+3]=

				vLumFilter[i];



		for(i=0; i<vChrFilterSize*chrDstH; i++)

			chrMmxFilter[4*i]=chrMmxFilter[4*i+1]=chrMmxFilter[4*i+2]=chrMmxFilter[4*i+3]=

				vChrFilter[i];


	}



	lastInLumBuf= -1;

	lastInChrBuf= -1;

  }  



	for(;dstY < dstH; dstY++){

		unsigned char *dest =dstptr[0]+dststride*dstY;

		unsigned char *uDest=dstptr[1]+(dststride>>1)*(dstY>>1);

		unsigned char *vDest=dstptr[2]+(dststride>>1)*(dstY>>1);

		const int chrDstY= dstbpp==12 ? (dstY>>1) : dstY;



		const int firstLumSrcY= vLumFilterPos[dstY];  

		const int firstChrSrcY= vChrFilterPos[chrDstY];  

		const int lastLumSrcY= firstLumSrcY + vLumFilterSize -1;  

		const int lastChrSrcY= firstChrSrcY + vChrFilterSize -1;  



		if(sws_flags == SWS_FAST_BILINEAR)

		{

			 

			if(firstLumSrcY > lastInLumBuf) lastInLumBuf= firstLumSrcY-1;

			if(firstChrSrcY > lastInChrBuf) lastInChrBuf= firstChrSrcY-1;

		}



		ASSERT(firstLumSrcY >= lastInLumBuf - vLumBufSize + 1)

		ASSERT(firstChrSrcY >= lastInChrBuf - vChrBufSize + 1)



		 

		if(lastLumSrcY < srcSliceY + srcSliceH && lastChrSrcY < ((srcSliceY + srcSliceH)>>1))

		{

			 

			while(lastInLumBuf < lastLumSrcY)

			{

				uint8_t *src= srcptr[0]+(lastInLumBuf + 1 - srcSliceY)*stride[0];

				lumBufIndex++;

				ASSERT(lumBufIndex < 2*vLumBufSize)

				ASSERT(lastInLumBuf + 1 - srcSliceY < srcSliceH)

				ASSERT(lastInLumBuf + 1 - srcSliceY >= 0)

 

				RENAME(hyscale)(lumPixBuf[ lumBufIndex ], dstW, src, srcW, lumXInc);

				lastInLumBuf++;

			}

			while(lastInChrBuf < lastChrSrcY)

			{

				uint8_t *src1= srcptr[1]+(lastInChrBuf + 1 - (srcSliceY>>1))*stride[1];

				uint8_t *src2= srcptr[2]+(lastInChrBuf + 1 - (srcSliceY>>1))*stride[2];

				chrBufIndex++;

				ASSERT(chrBufIndex < 2*vChrBufSize)

				ASSERT(lastInChrBuf + 1 - (srcSliceY>>1) < (srcSliceH>>1))

				ASSERT(lastInChrBuf + 1 - (srcSliceY>>1) >= 0)

				RENAME(hcscale)(chrPixBuf[ chrBufIndex ], chrDstW, src1, src2, srcW>>1, chrXInc);

				lastInChrBuf++;

			}

			 

			if(lumBufIndex >= vLumBufSize ) lumBufIndex-= vLumBufSize;

			if(chrBufIndex >= vChrBufSize ) chrBufIndex-= vChrBufSize;

		}

		else  

		{

 

			 

			while(lastInLumBuf+1 < srcSliceY + srcSliceH)

			{

				uint8_t *src= srcptr[0]+(lastInLumBuf + 1 - srcSliceY)*stride[0];

				lumBufIndex++;

				ASSERT(lumBufIndex < 2*vLumBufSize)

				ASSERT(lastInLumBuf + 1 - srcSliceY < srcSliceH)

				ASSERT(lastInLumBuf + 1 - srcSliceY >= 0)

				RENAME(hyscale)(lumPixBuf[ lumBufIndex ], dstW, src, srcW, lumXInc);

				lastInLumBuf++;

			}

			while(lastInChrBuf+1 < ((srcSliceY + srcSliceH)>>1))

			{

				uint8_t *src1= srcptr[1]+(lastInChrBuf + 1 - (srcSliceY>>1))*stride[1];

				uint8_t *src2= srcptr[2]+(lastInChrBuf + 1 - (srcSliceY>>1))*stride[2];

				chrBufIndex++;

				ASSERT(chrBufIndex < 2*vChrBufSize)

				ASSERT(lastInChrBuf + 1 - (srcSliceY>>1) < (srcSliceH>>1))

				ASSERT(lastInChrBuf + 1 - (srcSliceY>>1) >= 0)

				RENAME(hcscale)(chrPixBuf[ chrBufIndex ], chrDstW, src1, src2, srcW>>1, chrXInc);

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




		if(dstbpp==12)  

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

						 dest, dstW, chrAlpha, dstbpp);

			}

			else if(vLumFilterSize == 2 && vChrFilterSize == 2)  

			{

				int lumAlpha= vLumFilter[2*dstY+1];

				int chrAlpha= vChrFilter[2*dstY+1];



				RENAME(yuv2rgb2)(*lumSrcPtr, *(lumSrcPtr+1), *chrSrcPtr, *(chrSrcPtr+1),

						 dest, dstW, lumAlpha, chrAlpha, dstbpp);

			}

			else  

			{

				RENAME(yuv2rgbX)(

					vLumFilter+dstY*vLumFilterSize, lumSrcPtr, vLumFilterSize,

					vChrFilter+dstY*vChrFilterSize, chrSrcPtr, vChrFilterSize,

					dest, dstW, dstbpp,

					lumMmxFilter+dstY*vLumFilterSize*4, chrMmxFilter+dstY*vChrFilterSize*4);

			}

		}

	}


	__asm __volatile(SFENCE:::"memory");

	__asm __volatile(EMMS:::"memory");


	firstTime=0;

}