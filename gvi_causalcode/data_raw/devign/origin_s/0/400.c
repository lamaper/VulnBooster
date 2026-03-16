static void dct_unquantize_mpeg1_mmx(MpegEncContext *s,

                                     DCTELEM *block, int n, int qscale)

{

    int i, level;

    const UINT16 *quant_matrix;

    if (s->mb_intra) {

        if (n < 4) 

            block[0] = block[0] * s->y_dc_scale;

        else

            block[0] = block[0] * s->c_dc_scale;

        if (s->out_format == FMT_H263) {

            i = 1;

            goto unquant_even;

        }

         

        quant_matrix = s->intra_matrix;

	i=1;

	 

	while(i&3)

	{

            level = block[i];

            if (level) {

                if (level < 0) level = -level;

                    level = (int)(level * qscale * quant_matrix[i]) >> 3;

                    level = (level - 1) | 1;

                if (block[i] < 0) level = -level;

                block[i] = level;

            }

	    i++;

	}

	__asm __volatile(

	"movd	%0, %%mm6\n\t"        

	"punpckldq %%mm6, %%mm6\n\t"  

	"movq	%2, %%mm4\n\t"

	"movq	%%mm6, %%mm7\n\t"

	"movq	%1, %%mm5\n\t"

	"packssdw %%mm6, %%mm7\n\t"  

	"pxor	%%mm6, %%mm6\n\t"

	::"g"(qscale),"m"(mm_wone),"m"(mm_wabs):"memory");

        for(;i<64;i+=4) {

		__asm __volatile(

			"movq	%1, %%mm0\n\t"

			"movq	%%mm7, %%mm1\n\t"

			"movq	%%mm0, %%mm2\n\t"

			"movq	%%mm0, %%mm3\n\t"

			"pcmpgtw %%mm6, %%mm2\n\t"

			"pmullw	%2, %%mm1\n\t"

			"pandn	%%mm4, %%mm2\n\t"

			"por	%%mm5, %%mm2\n\t"

			"pmullw	%%mm2, %%mm0\n\t"  



			"pcmpeqw %%mm6, %%mm3\n\t"

			"pmullw	%%mm0, %%mm1\n\t"

			"psraw	$3, %%mm1\n\t"

			"psubw	%%mm5, %%mm1\n\t"    

			"pandn	%%mm4, %%mm3\n\t"   

			"por	%%mm5, %%mm1\n\t"    

			"pmullw %%mm2, %%mm1\n\t"    



			"pand	%%mm3, %%mm1\n\t"  

			"movq	%%mm1, %0"

			:"=m"(block[i])

			:"m"(block[i]), "m"(quant_matrix[i])

			:"memory");

        }

    } else {

        i = 0;

    unquant_even:

        quant_matrix = s->non_intra_matrix;

	 

	while(i&7)

	{

	    level = block[i];

            if (level) {

                if (level < 0) level = -level;

                    level = (((level << 1) + 1) * qscale *

                             ((int) quant_matrix[i])) >> 4;

                    level = (level - 1) | 1;

                if(block[i] < 0) level = -level;

                block[i] = level;

	    }

	    i++;

	}



asm volatile(

		"pcmpeqw %%mm7, %%mm7		\n\t"

		"psrlw $15, %%mm7		\n\t"

		"movd %2, %%mm6			\n\t"

		"packssdw %%mm6, %%mm6		\n\t"

		"packssdw %%mm6, %%mm6		\n\t"

		"1:				\n\t"

		"movq (%0, %3), %%mm0		\n\t"

		"movq 8(%0, %3), %%mm1		\n\t"

		"movq (%1, %3), %%mm4		\n\t"

		"movq 8(%1, %3), %%mm5		\n\t"

		"pmullw %%mm6, %%mm4		\n\t"  

		"pmullw %%mm6, %%mm5		\n\t"  

		"pxor %%mm2, %%mm2		\n\t"

		"pxor %%mm3, %%mm3		\n\t"

		"pcmpgtw %%mm0, %%mm2		\n\t"  

		"pcmpgtw %%mm1, %%mm3		\n\t"  

		"pxor %%mm2, %%mm0		\n\t"

		"pxor %%mm3, %%mm1		\n\t"

		"psubw %%mm2, %%mm0		\n\t"  

		"psubw %%mm3, %%mm1		\n\t"  

		"paddw %%mm0, %%mm0		\n\t"  

		"paddw %%mm1, %%mm1		\n\t"  

		"paddw %%mm7, %%mm0		\n\t"  

		"paddw %%mm7, %%mm1		\n\t"  

		"pmullw %%mm4, %%mm0		\n\t"  

		"pmullw %%mm5, %%mm1		\n\t"  

		"pxor %%mm4, %%mm4		\n\t"

		"pxor %%mm5, %%mm5		\n\t"  

		"pcmpeqw (%0, %3), %%mm4	\n\t"  

		"pcmpeqw 8(%0, %3), %%mm5	\n\t"  

		"psraw $4, %%mm0		\n\t"

		"psraw $4, %%mm1		\n\t"

		"psubw %%mm7, %%mm0		\n\t"

		"psubw %%mm7, %%mm1		\n\t"

		"por %%mm7, %%mm0		\n\t"

		"por %%mm7, %%mm1		\n\t"

		"pxor %%mm2, %%mm0		\n\t"

		"pxor %%mm3, %%mm1		\n\t"

		"psubw %%mm2, %%mm0		\n\t"

		"psubw %%mm3, %%mm1		\n\t"

		"pandn %%mm0, %%mm4		\n\t"

		"pandn %%mm1, %%mm5		\n\t"

		"movq %%mm4, (%0, %3)		\n\t"

		"movq %%mm5, 8(%0, %3)		\n\t"



		"addl $16, %3			\n\t"

		"cmpl $128, %3			\n\t"

		"jb 1b				\n\t"

		::"r" (block), "r"(quant_matrix), "g" (qscale), "r" (2*i)

		: "memory"

	);


	__asm __volatile(

	"movd	%0, %%mm6\n\t"        

	"punpckldq %%mm6, %%mm6\n\t"  

	"movq	%2, %%mm4\n\t"

	"movq	%%mm6, %%mm7\n\t"

	"movq	%1, %%mm5\n\t"

	"packssdw %%mm6, %%mm7\n\t"  

	"pxor	%%mm6, %%mm6\n\t"

	::"g"(qscale),"m"(mm_wone),"m"(mm_wabs));

        for(;i<64;i+=4) {

		__asm __volatile(

			"movq	%1, %%mm0\n\t"

			"movq	%%mm7, %%mm1\n\t"

			"movq	%%mm0, %%mm2\n\t"

			"movq	%%mm0, %%mm3\n\t"

			"pcmpgtw %%mm6, %%mm2\n\t"

			"pmullw	%2, %%mm1\n\t"

			"pandn	%%mm4, %%mm2\n\t"

			"por	%%mm5, %%mm2\n\t"

			"pmullw	%%mm2, %%mm0\n\t"  

			"psllw	$1, %%mm0\n\t"  

			"paddw	%%mm5, %%mm0\n\t"  



			"pmullw	%%mm0, %%mm1\n\t"

			"psraw	$4, %%mm1\n\t"

			"pcmpeqw %%mm6, %%mm3\n\t"

			"psubw	%%mm5, %%mm1\n\t"    

			"pandn	%%mm4, %%mm3\n\t"   

			"por	%%mm5, %%mm1\n\t"    

			"pmullw %%mm2, %%mm1\n\t"    



			"pand	%%mm3, %%mm1\n\t"  

			"movq	%%mm1, %0"

			:"=m"(block[i])

			:"m"(block[i]), "m"(quant_matrix[i]));

        }


    }

}
