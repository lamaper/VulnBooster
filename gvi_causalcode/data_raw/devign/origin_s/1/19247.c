inline static void RENAME(hcscale)(uint16_t *dst, int dstWidth, uint8_t *src1, uint8_t *src2,

				   int srcW, int xInc, int flags, int canMMX2BeUsed, int16_t *hChrFilter,

				   int16_t *hChrFilterPos, int hChrFilterSize, void *funnyUVCode,

				   int srcFormat, uint8_t *formatConvBuffer)

{

    if(srcFormat==IMGFMT_YUY2)

    {

	RENAME(yuy2ToUV)(formatConvBuffer, formatConvBuffer+2048, src1, src2, srcW);

	src1= formatConvBuffer;

	src2= formatConvBuffer+2048;

    }

    else if(srcFormat==IMGFMT_BGR32)

    {

	RENAME(bgr32ToUV)(formatConvBuffer, formatConvBuffer+2048, src1, src2, srcW);

	src1= formatConvBuffer;

	src2= formatConvBuffer+2048;

    }

    else if(srcFormat==IMGFMT_BGR24)

    {

	RENAME(bgr24ToUV)(formatConvBuffer, formatConvBuffer+2048, src1, src2, srcW);

	src1= formatConvBuffer;

	src2= formatConvBuffer+2048;

    }

    else if(srcFormat==IMGFMT_BGR16)

    {

	RENAME(bgr16ToUV)(formatConvBuffer, formatConvBuffer+2048, src1, src2, srcW);

	src1= formatConvBuffer;

	src2= formatConvBuffer+2048;

    }

    else if(srcFormat==IMGFMT_BGR15)

    {

	RENAME(bgr15ToUV)(formatConvBuffer, formatConvBuffer+2048, src1, src2, srcW);

	src1= formatConvBuffer;

	src2= formatConvBuffer+2048;

    }

    else if(srcFormat==IMGFMT_RGB32)

    {

	RENAME(rgb32ToUV)(formatConvBuffer, formatConvBuffer+2048, src1, src2, srcW);

	src1= formatConvBuffer;

	src2= formatConvBuffer+2048;

    }

    else if(srcFormat==IMGFMT_RGB24)

    {

	RENAME(rgb24ToUV)(formatConvBuffer, formatConvBuffer+2048, src1, src2, srcW);

	src1= formatConvBuffer;

	src2= formatConvBuffer+2048;

    }

    else if(isGray(srcFormat))

    {

    	return;

    }


	 

    if(!(flags&SWS_FAST_BILINEAR) || (!canMMX2BeUsed))


    if(!(flags&SWS_FAST_BILINEAR))


    {

    	RENAME(hScale)(dst     , dstWidth, src1, srcW, xInc, hChrFilter, hChrFilterPos, hChrFilterSize);

    	RENAME(hScale)(dst+2048, dstWidth, src2, srcW, xInc, hChrFilter, hChrFilterPos, hChrFilterSize);

    }

    else  

    {



	int i;

	if(canMMX2BeUsed)

	{

		asm volatile(

		"pxor %%mm7, %%mm7		\n\t"

		"pxor %%mm2, %%mm2		\n\t"  

		"movd %5, %%mm6			\n\t"  

		"punpcklwd %%mm6, %%mm6		\n\t"

		"punpcklwd %%mm6, %%mm6		\n\t"

		"movq %%mm6, %%mm2		\n\t"

		"psllq $16, %%mm2		\n\t"

		"paddw %%mm6, %%mm2		\n\t"

		"psllq $16, %%mm2		\n\t"

		"paddw %%mm6, %%mm2		\n\t"

		"psllq $16, %%mm2		\n\t"  

		"movq %%mm2, %%mm4		\n\t"

		"movd %4, %%mm6			\n\t"  

		"punpcklwd %%mm6, %%mm6		\n\t"

		"punpcklwd %%mm6, %%mm6		\n\t"

		"xorl %%eax, %%eax		\n\t"  

		"movl %0, %%esi			\n\t"  

		"movl %1, %%edi			\n\t"  

		"movl %3, %%edx			\n\t"  

		"xorl %%ecx, %%ecx		\n\t"

		"xorl %%ebx, %%ebx		\n\t"

		"movw %4, %%bx			\n\t"  


			PREFETCH" 1024(%%esi)		\n\t"\

			PREFETCH" 1056(%%esi)		\n\t"\

			PREFETCH" 1088(%%esi)		\n\t"\

			"call *%7			\n\t"\

			"movq %%mm4, %%mm2	\n\t"\

			"xorl %%ecx, %%ecx		\n\t"



FUNNYUVCODE

FUNNYUVCODE

FUNNYUVCODE

FUNNYUVCODE



FUNNYUVCODE

FUNNYUVCODE

FUNNYUVCODE

FUNNYUVCODE

		"xorl %%eax, %%eax		\n\t"  

		"movl %6, %%esi			\n\t"  

		"movl %1, %%edi			\n\t"  

		"addl $4096, %%edi		\n\t"



FUNNYUVCODE

FUNNYUVCODE

FUNNYUVCODE

FUNNYUVCODE



FUNNYUVCODE

FUNNYUVCODE

FUNNYUVCODE

FUNNYUVCODE



		:: "m" (src1), "m" (dst), "m" (dstWidth), "m" ((xInc*4)>>16),

		  "m" ((xInc*4)&0xFFFF), "m" (xInc&0xFFFF), "m" (src2), "m" (funnyUVCode)

		: "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi"

	);

		for(i=dstWidth-1; (i*xInc)>>16 >=srcW-1; i--)

		{

 

			dst[i] = src1[srcW-1]*128;

			dst[i+2048] = src2[srcW-1]*128;

		}

	}

	else

	{


	asm volatile(

		"xorl %%eax, %%eax		\n\t"  

		"xorl %%ebx, %%ebx		\n\t"  

		"xorl %%ecx, %%ecx		\n\t"  

		".balign 16			\n\t"

		"1:				\n\t"

		"movl %0, %%esi			\n\t"

		"movzbl  (%%esi, %%ebx), %%edi	\n\t"  

		"movzbl 1(%%esi, %%ebx), %%esi	\n\t"  

		"subl %%edi, %%esi		\n\t"  

		"imull %%ecx, %%esi		\n\t"  

		"shll $16, %%edi		\n\t"

		"addl %%edi, %%esi		\n\t"  

		"movl %1, %%edi			\n\t"

		"shrl $9, %%esi			\n\t"

		"movw %%si, (%%edi, %%eax, 2)	\n\t"



		"movzbl  (%5, %%ebx), %%edi	\n\t"  

		"movzbl 1(%5, %%ebx), %%esi	\n\t"  

		"subl %%edi, %%esi		\n\t"  

		"imull %%ecx, %%esi		\n\t"  

		"shll $16, %%edi		\n\t"

		"addl %%edi, %%esi		\n\t"  

		"movl %1, %%edi			\n\t"

		"shrl $9, %%esi			\n\t"

		"movw %%si, 4096(%%edi, %%eax, 2)\n\t"



		"addw %4, %%cx			\n\t"  

		"adcl %3, %%ebx			\n\t"  

		"addl $1, %%eax			\n\t"

		"cmpl %2, %%eax			\n\t"

		" jb 1b				\n\t"



		:: "m" (src1), "m" (dst), "m" (dstWidth), "m" (xInc>>16), "m" (xInc&0xFFFF),

		"r" (src2)

		: "%eax", "%ebx", "%ecx", "%edi", "%esi"

		);


	}  



	int i;

	unsigned int xpos=0;

	for(i=0;i<dstWidth;i++)

	{

		register unsigned int xx=xpos>>16;

		register unsigned int xalpha=(xpos&0xFFFF)>>9;

		dst[i]=(src1[xx]*(xalpha^127)+src1[xx+1]*xalpha);

		dst[i+2048]=(src2[xx]*(xalpha^127)+src2[xx+1]*xalpha);

 

		xpos+=xInc;

	}


   }

}
