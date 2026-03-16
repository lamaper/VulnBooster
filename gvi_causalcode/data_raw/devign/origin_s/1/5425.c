SwsContext *getSwsContext(int srcW, int srcH, int srcFormat, int dstW, int dstH, int dstFormat, int flags,

                         SwsFilter *srcFilter, SwsFilter *dstFilter){



	SwsContext *c;

	int i;

	int usesFilter;

	SwsFilter dummyFilter= {NULL, NULL, NULL, NULL};


	if(gCpuCaps.hasMMX)

		asm volatile("emms\n\t"::: "memory");




	if(swScale==NULL) globalInit();



	 

	if(srcFormat==IMGFMT_IYUV) srcFormat=IMGFMT_I420;

	if(srcFormat==IMGFMT_Y8)   srcFormat=IMGFMT_Y800;

	if(dstFormat==IMGFMT_Y8)   dstFormat=IMGFMT_Y800;



	if(!isSupportedIn(srcFormat)) 

	{

		fprintf(stderr, "swScaler: %s is not supported as input format\n", vo_format_name(srcFormat));

		return NULL;

	}

	if(!isSupportedOut(dstFormat))

	{

		fprintf(stderr, "swScaler: %s is not supported as output format\n", vo_format_name(dstFormat));

		return NULL;

	}



	 

	if(srcW<4 || srcH<1 || dstW<8 || dstH<1)  

	{

		fprintf(stderr, "swScaler: %dx%d -> %dx%d is invalid scaling dimension\n", 

			srcW, srcH, dstW, dstH);

		return NULL;

	}



	if(!dstFilter) dstFilter= &dummyFilter;

	if(!srcFilter) srcFilter= &dummyFilter;



	c= memalign(64, sizeof(SwsContext));

	memset(c, 0, sizeof(SwsContext));



	c->srcW= srcW;

	c->srcH= srcH;

	c->dstW= dstW;

	c->dstH= dstH;

	c->lumXInc= ((srcW<<16) + (dstW>>1))/dstW;

	c->lumYInc= ((srcH<<16) + (dstH>>1))/dstH;

	c->flags= flags;

	c->dstFormat= dstFormat;

	c->srcFormat= srcFormat;



	usesFilter=0;

	if(dstFilter->lumV!=NULL && dstFilter->lumV->length>1) usesFilter=1;

	if(dstFilter->lumH!=NULL && dstFilter->lumH->length>1) usesFilter=1;

	if(dstFilter->chrV!=NULL && dstFilter->chrV->length>1) usesFilter=1;

	if(dstFilter->chrH!=NULL && dstFilter->chrH->length>1) usesFilter=1;

	if(srcFilter->lumV!=NULL && srcFilter->lumV->length>1) usesFilter=1;

	if(srcFilter->lumH!=NULL && srcFilter->lumH->length>1) usesFilter=1;

	if(srcFilter->chrV!=NULL && srcFilter->chrV->length>1) usesFilter=1;

	if(srcFilter->chrH!=NULL && srcFilter->chrH->length>1) usesFilter=1;

	

	 

	if(srcW==dstW && srcH==dstH && !usesFilter)

	{

		 

		if(isPlanarYUV(srcFormat) && isBGR(dstFormat))

		{


			if(dstFormat==IMGFMT_BGR32)

				yuv2rgb_init( dstFormat&0xFF  , MODE_BGR);

			else

				yuv2rgb_init( dstFormat&0xFF  , MODE_RGB);


			yuv2rgb_init( dstFormat&0xFF  , MODE_RGB);


			c->swScale= planarYuvToBgr;



			if(flags&SWS_PRINT_INFO)

				printf("SwScaler: using unscaled %s -> %s special converter\n", 

					vo_format_name(srcFormat), vo_format_name(dstFormat));

			return c;

		}



		 

		if(srcFormat == dstFormat || (isPlanarYUV(srcFormat) && isPlanarYUV(dstFormat)))

		{

			c->swScale= simpleCopy;



			if(flags&SWS_PRINT_INFO)

				printf("SwScaler: using unscaled %s -> %s special converter\n", 

					vo_format_name(srcFormat), vo_format_name(dstFormat));

			return c;

		}

		

		 

		if((srcFormat==IMGFMT_BGR32 && dstFormat==IMGFMT_BGR24)

		 ||(srcFormat==IMGFMT_RGB32 && dstFormat==IMGFMT_RGB24))

		{

			c->swScale= bgr32to24Wrapper;



			if(flags&SWS_PRINT_INFO)

				printf("SwScaler: using unscaled %s -> %s special converter\n", 

					vo_format_name(srcFormat), vo_format_name(dstFormat));

			return c;

		}

		

		 

		if((srcFormat==IMGFMT_BGR24 && dstFormat==IMGFMT_BGR32)

		 ||(srcFormat==IMGFMT_RGB24 && dstFormat==IMGFMT_RGB32))

		{

			c->swScale= bgr24to32Wrapper;



			if(flags&SWS_PRINT_INFO)

				printf("SwScaler: using unscaled %s -> %s special converter\n", 

					vo_format_name(srcFormat), vo_format_name(dstFormat));

			return c;

		}



		 

		if(srcFormat==IMGFMT_BGR15 && dstFormat==IMGFMT_BGR16)

		{

			c->swScale= bgr15to16Wrapper;



			if(flags&SWS_PRINT_INFO)

				printf("SwScaler: using unscaled %s -> %s special converter\n", 

					vo_format_name(srcFormat), vo_format_name(dstFormat));

			return c;

		}



		 

		if(srcFormat==IMGFMT_BGR24 && dstFormat==IMGFMT_YV12)

		{

			c->swScale= bgr24toyv12Wrapper;



			if(flags&SWS_PRINT_INFO)

				printf("SwScaler: using unscaled %s -> %s special converter\n", 

					vo_format_name(srcFormat), vo_format_name(dstFormat));

			return c;

		}

	}



	if(cpuCaps.hasMMX2)

	{

		c->canMMX2BeUsed= (dstW >=srcW && (dstW&31)==0 && (srcW&15)==0) ? 1 : 0;

		if(!c->canMMX2BeUsed && dstW >=srcW && (srcW&15)==0 && (flags&SWS_FAST_BILINEAR))

		{

			if(flags&SWS_PRINT_INFO)

				fprintf(stderr, "SwScaler: output Width is not a multiple of 32 -> no MMX2 scaler\n");

		}

	}

	else

		c->canMMX2BeUsed=0;





	 

	if(isHalfChrV(srcFormat)) c->flags= flags= flags&(~SWS_FULL_CHR_V);

	 

	if(isHalfChrH(srcFormat)) c->flags= flags= flags&(~SWS_FULL_CHR_H_INP);

	 

	if(isHalfChrH(dstFormat)) c->flags= flags= flags&(~SWS_FULL_CHR_H_INT);



	if(flags&SWS_FULL_CHR_H_INP)	c->chrSrcW= srcW;

	else				c->chrSrcW= (srcW+1)>>1;



	if(flags&SWS_FULL_CHR_H_INT)	c->chrDstW= dstW;

	else				c->chrDstW= (dstW+1)>>1;



	if(flags&SWS_FULL_CHR_V)	c->chrSrcH= srcH;

	else				c->chrSrcH= (srcH+1)>>1;



	if(isHalfChrV(dstFormat))	c->chrDstH= (dstH+1)>>1;

	else				c->chrDstH= dstH;



	c->chrXInc= ((c->chrSrcW<<16) + (c->chrDstW>>1))/c->chrDstW;

	c->chrYInc= ((c->chrSrcH<<16) + (c->chrDstH>>1))/c->chrDstH;





	 

	 

	 

	 

	 

	 

	if(flags&SWS_FAST_BILINEAR)

	{

		if(c->canMMX2BeUsed)

		{

			c->lumXInc+= 20;

			c->chrXInc+= 20;

		}

		 

		else if(cpuCaps.hasMMX)

		{

			c->lumXInc = ((srcW-2)<<16)/(dstW-2) - 20;

			c->chrXInc = ((c->chrSrcW-2)<<16)/(c->chrDstW-2) - 20;

		}

	}



	 

	{

		const int filterAlign= cpuCaps.hasMMX ? 4 : 1;



		initFilter(&c->hLumFilter, &c->hLumFilterPos, &c->hLumFilterSize, c->lumXInc,

				 srcW      ,       dstW, filterAlign, 1<<14, flags,

				 srcFilter->lumH, dstFilter->lumH);

		initFilter(&c->hChrFilter, &c->hChrFilterPos, &c->hChrFilterSize, c->chrXInc,

				(srcW+1)>>1, c->chrDstW, filterAlign, 1<<14, flags,

				 srcFilter->chrH, dstFilter->chrH);


 

		if(c->canMMX2BeUsed && (flags & SWS_FAST_BILINEAR))

		{

			initMMX2HScaler(      dstW, c->lumXInc, c->funnyYCode);

			initMMX2HScaler(c->chrDstW, c->chrXInc, c->funnyUVCode);

		}


	}  







	 

	initFilter(&c->vLumFilter, &c->vLumFilterPos, &c->vLumFilterSize, c->lumYInc,

			srcH      ,        dstH, 1, (1<<12)-4, flags,

			srcFilter->lumV, dstFilter->lumV);

	initFilter(&c->vChrFilter, &c->vChrFilterPos, &c->vChrFilterSize, c->chrYInc,

			(srcH+1)>>1, c->chrDstH, 1, (1<<12)-4, flags,

			 srcFilter->chrV, dstFilter->chrV);



	 

	c->vLumBufSize= c->vLumFilterSize;

	c->vChrBufSize= c->vChrFilterSize;

	for(i=0; i<dstH; i++)

	{

		int chrI= i*c->chrDstH / dstH;

		int nextSlice= MAX(c->vLumFilterPos[i   ] + c->vLumFilterSize - 1,

				 ((c->vChrFilterPos[chrI] + c->vChrFilterSize - 1)<<1));

		nextSlice&= ~1;  

		if(c->vLumFilterPos[i   ] + c->vLumBufSize < nextSlice)

			c->vLumBufSize= nextSlice - c->vLumFilterPos[i   ];

		if(c->vChrFilterPos[chrI] + c->vChrBufSize < (nextSlice>>1))

			c->vChrBufSize= (nextSlice>>1) - c->vChrFilterPos[chrI];

	}



	 

	c->lumPixBuf= (int16_t**)memalign(4, c->vLumBufSize*2*sizeof(int16_t*));

	c->chrPixBuf= (int16_t**)memalign(4, c->vChrBufSize*2*sizeof(int16_t*));

	 

	for(i=0; i<c->vLumBufSize; i++)

		c->lumPixBuf[i]= c->lumPixBuf[i+c->vLumBufSize]= (uint16_t*)memalign(8, 4000);

	for(i=0; i<c->vChrBufSize; i++)

		c->chrPixBuf[i]= c->chrPixBuf[i+c->vChrBufSize]= (uint16_t*)memalign(8, 8000);



	 

	for(i=0; i<c->vLumBufSize; i++) memset(c->lumPixBuf[i], 0, 4000);

	for(i=0; i<c->vChrBufSize; i++) memset(c->chrPixBuf[i], 64, 8000);



	ASSERT(c->chrDstH <= dstH)



	 

	if(cpuCaps.hasMMX)

	{

		c->lumMmxFilter= (int16_t*)memalign(8, c->vLumFilterSize*      dstH*4*sizeof(int16_t));

		c->chrMmxFilter= (int16_t*)memalign(8, c->vChrFilterSize*c->chrDstH*4*sizeof(int16_t));

		for(i=0; i<c->vLumFilterSize*dstH; i++)

			c->lumMmxFilter[4*i]=c->lumMmxFilter[4*i+1]=c->lumMmxFilter[4*i+2]=c->lumMmxFilter[4*i+3]=

				c->vLumFilter[i];

		for(i=0; i<c->vChrFilterSize*c->chrDstH; i++)

			c->chrMmxFilter[4*i]=c->chrMmxFilter[4*i+1]=c->chrMmxFilter[4*i+2]=c->chrMmxFilter[4*i+3]=

				c->vChrFilter[i];

	}



	if(flags&SWS_PRINT_INFO)

	{


		char *dither= " dithered";


		char *dither= "";


		if(flags&SWS_FAST_BILINEAR)

			fprintf(stderr, "\nSwScaler: FAST_BILINEAR scaler, ");

		else if(flags&SWS_BILINEAR)

			fprintf(stderr, "\nSwScaler: BILINEAR scaler, ");

		else if(flags&SWS_BICUBIC)

			fprintf(stderr, "\nSwScaler: BICUBIC scaler, ");

		else if(flags&SWS_X)

			fprintf(stderr, "\nSwScaler: Experimental scaler, ");

		else if(flags&SWS_POINT)

			fprintf(stderr, "\nSwScaler: Nearest Neighbor / POINT scaler, ");

		else if(flags&SWS_AREA)

			fprintf(stderr, "\nSwScaler: Area Averageing scaler, ");

		else

			fprintf(stderr, "\nSwScaler: ehh flags invalid?! ");



		if(dstFormat==IMGFMT_BGR15 || dstFormat==IMGFMT_BGR16)

			fprintf(stderr, "from %s to%s %s ", 

				vo_format_name(srcFormat), dither, vo_format_name(dstFormat));

		else

			fprintf(stderr, "from %s to %s ", 

				vo_format_name(srcFormat), vo_format_name(dstFormat));



		if(cpuCaps.hasMMX2)

			fprintf(stderr, "using MMX2\n");

		else if(cpuCaps.has3DNow)

			fprintf(stderr, "using 3DNOW\n");

		else if(cpuCaps.hasMMX)

			fprintf(stderr, "using MMX\n");

		else

			fprintf(stderr, "using C\n");

	}



	if((flags & SWS_PRINT_INFO) && verbose)

	{

		if(cpuCaps.hasMMX)

		{

			if(c->canMMX2BeUsed && (flags&SWS_FAST_BILINEAR))

				printf("SwScaler: using FAST_BILINEAR MMX2 scaler for horizontal scaling\n");

			else

			{

				if(c->hLumFilterSize==4)

					printf("SwScaler: using 4-tap MMX scaler for horizontal luminance scaling\n");

				else if(c->hLumFilterSize==8)

					printf("SwScaler: using 8-tap MMX scaler for horizontal luminance scaling\n");

				else

					printf("SwScaler: using n-tap MMX scaler for horizontal luminance scaling\n");



				if(c->hChrFilterSize==4)

					printf("SwScaler: using 4-tap MMX scaler for horizontal chrominance scaling\n");

				else if(c->hChrFilterSize==8)

					printf("SwScaler: using 8-tap MMX scaler for horizontal chrominance scaling\n");

				else

					printf("SwScaler: using n-tap MMX scaler for horizontal chrominance scaling\n");

			}

		}

		else

		{


			printf("SwScaler: using X86-Asm scaler for horizontal scaling\n");


			if(flags & SWS_FAST_BILINEAR)

				printf("SwScaler: using FAST_BILINEAR C scaler for horizontal scaling\n");

			else

				printf("SwScaler: using C scaler for horizontal scaling\n");


		}

		if(isPlanarYUV(dstFormat))

		{

			if(c->vLumFilterSize==1)

				printf("SwScaler: using 1-tap %s \"scaler\" for vertical scaling (YV12 like)\n", cpuCaps.hasMMX ? "MMX" : "C");

			else

				printf("SwScaler: using n-tap %s scaler for vertical scaling (YV12 like)\n", cpuCaps.hasMMX ? "MMX" : "C");

		}

		else

		{

			if(c->vLumFilterSize==1 && c->vChrFilterSize==2)

				printf("SwScaler: using 1-tap %s \"scaler\" for vertical luminance scaling (BGR)\n"

				       "SwScaler:       2-tap scaler for vertical chrominance scaling (BGR)\n",cpuCaps.hasMMX ? "MMX" : "C");

			else if(c->vLumFilterSize==2 && c->vChrFilterSize==2)

				printf("SwScaler: using 2-tap linear %s scaler for vertical scaling (BGR)\n", cpuCaps.hasMMX ? "MMX" : "C");

			else

				printf("SwScaler: using n-tap %s scaler for vertical scaling (BGR)\n", cpuCaps.hasMMX ? "MMX" : "C");

		}



		if(dstFormat==IMGFMT_BGR24)

			printf("SwScaler: using %s YV12->BGR24 Converter\n",

				cpuCaps.hasMMX2 ? "MMX2" : (cpuCaps.hasMMX ? "MMX" : "C"));

		else if(dstFormat==IMGFMT_BGR32)

			printf("SwScaler: using %s YV12->BGR32 Converter\n", cpuCaps.hasMMX ? "MMX" : "C");

		else if(dstFormat==IMGFMT_BGR16)

			printf("SwScaler: using %s YV12->BGR16 Converter\n", cpuCaps.hasMMX ? "MMX" : "C");

		else if(dstFormat==IMGFMT_BGR15)

			printf("SwScaler: using %s YV12->BGR15 Converter\n", cpuCaps.hasMMX ? "MMX" : "C");



		printf("SwScaler: %dx%d -> %dx%d\n", srcW, srcH, dstW, dstH);

	}

	if((flags & SWS_PRINT_INFO) && verbose>1)

	{

		printf("SwScaler:Lum srcW=%d srcH=%d dstW=%d dstH=%d xInc=%d yInc=%d\n",

			c->srcW, c->srcH, c->dstW, c->dstH, c->lumXInc, c->lumYInc);

		printf("SwScaler:Chr srcW=%d srcH=%d dstW=%d dstH=%d xInc=%d yInc=%d\n",

			c->chrSrcW, c->chrSrcH, c->chrDstW, c->chrDstH, c->chrXInc, c->chrYInc);

	}



	c->swScale= swScale;

	return c;

}
