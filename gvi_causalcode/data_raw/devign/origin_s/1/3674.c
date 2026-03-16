static inline void RENAME(yuvPlanartoyuy2)(const uint8_t *ysrc, const uint8_t *usrc, const uint8_t *vsrc, uint8_t *dst,

	long width, long height,

	long lumStride, long chromStride, long dstStride, long vertLumPerChroma)

{

	long y;

	const long chromWidth= width>>1;

	for(y=0; y<height; y++)

	{


 

		asm volatile(

			"xor %%"REG_a", %%"REG_a"	\n\t"

			ASMALIGN(4)

			"1:				\n\t"

			PREFETCH" 32(%1, %%"REG_a", 2)	\n\t"

			PREFETCH" 32(%2, %%"REG_a")	\n\t"

			PREFETCH" 32(%3, %%"REG_a")	\n\t"

			"movq (%2, %%"REG_a"), %%mm0	\n\t"  

			"movq %%mm0, %%mm2		\n\t"  

			"movq (%3, %%"REG_a"), %%mm1	\n\t"  

			"punpcklbw %%mm1, %%mm0		\n\t"  

			"punpckhbw %%mm1, %%mm2		\n\t"  



			"movq (%1, %%"REG_a",2), %%mm3	\n\t"  

			"movq 8(%1, %%"REG_a",2), %%mm5	\n\t"  

			"movq %%mm3, %%mm4		\n\t"  

			"movq %%mm5, %%mm6		\n\t"  

			"punpcklbw %%mm0, %%mm3		\n\t"  

			"punpckhbw %%mm0, %%mm4		\n\t"  

			"punpcklbw %%mm2, %%mm5		\n\t"  

			"punpckhbw %%mm2, %%mm6		\n\t"  



			MOVNTQ" %%mm3, (%0, %%"REG_a", 4)\n\t"

			MOVNTQ" %%mm4, 8(%0, %%"REG_a", 4)\n\t"

			MOVNTQ" %%mm5, 16(%0, %%"REG_a", 4)\n\t"

			MOVNTQ" %%mm6, 24(%0, %%"REG_a", 4)\n\t"



			"add $8, %%"REG_a"		\n\t"

			"cmp %4, %%"REG_a"		\n\t"

			" jb 1b				\n\t"

			::"r"(dst), "r"(ysrc), "r"(usrc), "r"(vsrc), "g" (chromWidth)

			: "%"REG_a

		);




	y1 = yc[n];					\

	y2 = yc2[n];					\

	u = uc[n];					\

	v = vc[n];					\

	asm("unpkbw %1, %0" : "=r"(y1) : "r"(y1));	\

	asm("unpkbw %1, %0" : "=r"(y2) : "r"(y2));	\

	asm("unpkbl %1, %0" : "=r"(u) : "r"(u));	\

	asm("unpkbl %1, %0" : "=r"(v) : "r"(v));	\

	yuv1 = (u << 8) + (v << 24);			\

	yuv2 = yuv1 + y2;				\

	yuv1 += y1;					\

	qdst[n] = yuv1;					\

	qdst2[n] = yuv2;



		int i;

		uint64_t *qdst = (uint64_t *) dst;

		uint64_t *qdst2 = (uint64_t *) (dst + dstStride);

		const uint32_t *yc = (uint32_t *) ysrc;

		const uint32_t *yc2 = (uint32_t *) (ysrc + lumStride);

		const uint16_t *uc = (uint16_t*) usrc, *vc = (uint16_t*) vsrc;

		for(i = 0; i < chromWidth; i += 8){

			uint64_t y1, y2, yuv1, yuv2;

			uint64_t u, v;

			 

			asm("ldq $31,64(%0)" :: "r"(yc));

			asm("ldq $31,64(%0)" :: "r"(yc2));

			asm("ldq $31,64(%0)" :: "r"(uc));

			asm("ldq $31,64(%0)" :: "r"(vc));



			pl2yuy2(0);

			pl2yuy2(1);

			pl2yuy2(2);

			pl2yuy2(3);



			yc += 4;

			yc2 += 4;

			uc += 4;

			vc += 4;

			qdst += 4;

			qdst2 += 4;

		}

		y++;

		ysrc += lumStride;

		dst += dstStride;


		int i;

		uint64_t *ldst = (uint64_t *) dst;

		const uint8_t *yc = ysrc, *uc = usrc, *vc = vsrc;

		for(i = 0; i < chromWidth; i += 2){

			uint64_t k, l;

			k = yc[0] + (uc[0] << 8) +

			    (yc[1] << 16) + (vc[0] << 24);

			l = yc[2] + (uc[1] << 8) +

			    (yc[3] << 16) + (vc[1] << 24);

			*ldst++ = k + (l << 32);

			yc += 4;

			uc += 2;

			vc += 2;

		}


		int i, *idst = (int32_t *) dst;

		const uint8_t *yc = ysrc, *uc = usrc, *vc = vsrc;

		for(i = 0; i < chromWidth; i++){


			*idst++ = (yc[0] << 24)+ (uc[0] << 16) +

			    (yc[1] << 8) + (vc[0] << 0);


			*idst++ = yc[0] + (uc[0] << 8) +

			    (yc[1] << 16) + (vc[0] << 24);


			yc += 2;

			uc++;

			vc++;

		}



		if((y&(vertLumPerChroma-1))==(vertLumPerChroma-1) )

		{

			usrc += chromStride;

			vsrc += chromStride;

		}

		ysrc += lumStride;

		dst += dstStride;

	}


asm(    EMMS" \n\t"

        SFENCE" \n\t"

        :::"memory");


}
