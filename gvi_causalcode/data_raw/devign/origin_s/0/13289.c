static int RENAME(dct_quantize)(MpegEncContext *s,

                            DCTELEM *block, int n,

                            int qscale, int *overflow)

{

    int level=0, last_non_zero_p1, q;  

    const uint16_t *qmat, *bias;

    static __align8 int16_t temp_block[64];



     

    ff_fdct_mmx (block);  



    if (s->mb_intra) {

        int dummy;

        if (n < 4)

            q = s->y_dc_scale;

        else

            q = s->c_dc_scale;

         

        if (!s->h263_aic) {


        asm volatile (

        	"imul %%ecx		\n\t"

        	: "=d" (level), "=a"(dummy)

        	: "a" ((block[0]>>2) + q), "c" (inverse[q<<1])

        );


        asm volatile (

        	"xorl %%edx, %%edx	\n\t"

        	"divw %%cx		\n\t"

        	"movzwl %%ax, %%eax	\n\t"

        	: "=a" (level)

        	: "a" ((block[0]>>2) + q), "c" (q<<1)

        	: "%edx"

        );


        } else

             

            level = (block[0] + 4)>>3;

            

        block[0]=0;  

 

        last_non_zero_p1 = 1;

        bias = s->q_intra_matrix16_bias[qscale];

        qmat = s->q_intra_matrix16[qscale];

    } else {

        last_non_zero_p1 = 0;

        bias = s->q_inter_matrix16_bias[qscale];

        qmat = s->q_inter_matrix16[qscale];

    }



    if(s->out_format == FMT_H263 && s->mpeg_quant==0){

	   

        asm volatile(

            "movd %%eax, %%mm3			\n\t"  

            SPREADW(%%mm3)

            "pxor %%mm7, %%mm7			\n\t"  

            "pxor %%mm4, %%mm4			\n\t"  

            "movq (%1), %%mm5			\n\t"  

            "pxor %%mm6, %%mm6			\n\t"

            "psubw (%2), %%mm6			\n\t"  

            "movl $-128, %%eax			\n\t"

            : "+a" (last_non_zero_p1)

            : "r" (qmat), "r" (bias)

            );

	   

	  asm volatile(

            ".balign 16				\n\t"

            "1:					\n\t"

            "pxor %%mm1, %%mm1			\n\t"  

            "movq (%1, %%eax), %%mm0		\n\t"  

            "pcmpgtw %%mm0, %%mm1		\n\t"  

            "pxor %%mm1, %%mm0			\n\t" 

            "psubw %%mm1, %%mm0			\n\t"  

            "psubusw %%mm6, %%mm0		\n\t"  

            "pmulhw %%mm5, %%mm0		\n\t"  

            "por %%mm0, %%mm4			\n\t" 

            "pxor %%mm1, %%mm0			\n\t" 

            "psubw %%mm1, %%mm0			\n\t"  

            "movq %%mm0, (%3, %%eax)		\n\t"

            "pcmpeqw %%mm7, %%mm0		\n\t"  

            "movq (%2, %%eax), %%mm1		\n\t" 

            "movq %%mm7, (%1, %%eax)		\n\t"  

            "pandn %%mm1, %%mm0			\n\t"

	    PMAXW(%%mm0, %%mm3)

            "addl $8, %%eax			\n\t"

            " js 1b				\n\t"

            : "+a" (last_non_zero_p1)

            : "r" (block+64), "r" (inv_zigzag_direct16+64), "r" (temp_block+64)

            );

	   

	  asm volatile(

            "movq %%mm3, %%mm0			\n\t"

            "psrlq $32, %%mm3			\n\t"

	    PMAXW(%%mm0, %%mm3)

            "movq %%mm3, %%mm0			\n\t"

            "psrlq $16, %%mm3			\n\t"

	    PMAXW(%%mm0, %%mm3)

            "movd %%mm3, %%eax			\n\t"

            "movzbl %%al, %%eax			\n\t"  

            "movd %2, %%mm1			\n\t"  

	    SPREADW(%%mm1)

            "psubusw %%mm1, %%mm4		\n\t" 

            "packuswb %%mm4, %%mm4		\n\t"

            "movd %%mm4, %1			\n\t"  

            : "+a" (last_non_zero_p1), "=r" (*overflow)

            : "r" (s->max_qcoeff)

            );

    }else{  

        asm volatile(

            "pushl %%ebp				\n\t"

            "pushl %%ebx				\n\t"

            "movl %0, %%ebp				\n\t"

            "movl (%%ebp), %%ebx		\n\t"

            "movd %%ebx, %%mm3			\n\t"  

            SPREADW(%%mm3)

            "pxor %%mm7, %%mm7			\n\t"  

            "pxor %%mm4, %%mm4			\n\t"  

            "movl $-128, %%ebx			\n\t"

            ".balign 16				\n\t"

            "1:					\n\t"

            "pxor %%mm1, %%mm1			\n\t"  

            "movq (%1, %%ebx), %%mm0		\n\t"  

            "pcmpgtw %%mm0, %%mm1		\n\t"  

            "pxor %%mm1, %%mm0			\n\t" 

            "psubw %%mm1, %%mm0			\n\t"  

            "movq (%3, %%ebx), %%mm6		\n\t"  

            "paddusw %%mm6, %%mm0		\n\t"  

            "movq (%2, %%ebx), %%mm5		\n\t"  

            "pmulhw %%mm5, %%mm0		\n\t"  

            "por %%mm0, %%mm4			\n\t" 

            "pxor %%mm1, %%mm0			\n\t" 

            "psubw %%mm1, %%mm0			\n\t"  

            "movq %%mm0, (%5, %%ebx)		\n\t"

            "pcmpeqw %%mm7, %%mm0		\n\t"  

            "movq (%4, %%ebx), %%mm1		\n\t" 

            "movq %%mm7, (%1, %%ebx)		\n\t"  

            "pandn %%mm1, %%mm0			\n\t"

	    PMAXW(%%mm0, %%mm3)

            "addl $8, %%ebx			\n\t"

            " js 1b				\n\t"

            "movq %%mm3, %%mm0			\n\t"

            "psrlq $32, %%mm3			\n\t"

	    PMAXW(%%mm0, %%mm3)

            "movq %%mm3, %%mm0			\n\t"

            "psrlq $16, %%mm3			\n\t"

	    PMAXW(%%mm0, %%mm3)

            "movd %%mm3, %%ebx			\n\t"

            "movzbl %%bl, %%ebx			\n\t"  

            "movl %%ebx, (%%ebp)		\n\t"

            "popl %%ebx					\n\t"

            "popl %%ebp					\n\t"

            :

			: "m" (last_non_zero_p1),

              "r" (block+64), "r" (qmat+64), "r" (bias+64),

              "r" (inv_zigzag_direct16+64), "r" (temp_block+64)

        );

         

        asm volatile(

            "movd %1, %%mm1			\n\t"  

	    SPREADW(%%mm1)

            "psubusw %%mm1, %%mm4		\n\t" 

            "packuswb %%mm4, %%mm4		\n\t"

            "movd %%mm4, %0			\n\t"  

        : "=r" (*overflow)

        : "r" (s->max_qcoeff)

        );

    }



    if(s->mb_intra) block[0]= level;

    else            block[0]= temp_block[0];



    if(s->dsp.idct_permutation_type == FF_SIMPLE_IDCT_PERM){

        if(last_non_zero_p1 <= 1) goto end;

        block[0x08] = temp_block[0x01]; block[0x10] = temp_block[0x08]; 

        block[0x20] = temp_block[0x10]; 

        if(last_non_zero_p1 <= 4) goto end;

        block[0x18] = temp_block[0x09]; block[0x04] = temp_block[0x02]; 

        block[0x09] = temp_block[0x03]; 

        if(last_non_zero_p1 <= 7) goto end;

        block[0x14] = temp_block[0x0A]; block[0x28] = temp_block[0x11]; 

        block[0x12] = temp_block[0x18]; block[0x02] = temp_block[0x20]; 

        if(last_non_zero_p1 <= 11) goto end;

        block[0x1A] = temp_block[0x19]; block[0x24] = temp_block[0x12]; 

        block[0x19] = temp_block[0x0B]; block[0x01] = temp_block[0x04]; 

        block[0x0C] = temp_block[0x05]; 

        if(last_non_zero_p1 <= 16) goto end;

        block[0x11] = temp_block[0x0C]; block[0x29] = temp_block[0x13]; 

        block[0x16] = temp_block[0x1A]; block[0x0A] = temp_block[0x21]; 

        block[0x30] = temp_block[0x28]; block[0x22] = temp_block[0x30]; 

        block[0x38] = temp_block[0x29]; block[0x06] = temp_block[0x22]; 

        if(last_non_zero_p1 <= 24) goto end;

        block[0x1B] = temp_block[0x1B]; block[0x21] = temp_block[0x14]; 

        block[0x1C] = temp_block[0x0D]; block[0x05] = temp_block[0x06]; 

        block[0x0D] = temp_block[0x07]; block[0x15] = temp_block[0x0E]; 

        block[0x2C] = temp_block[0x15]; block[0x13] = temp_block[0x1C]; 

        if(last_non_zero_p1 <= 32) goto end;

        block[0x0B] = temp_block[0x23]; block[0x34] = temp_block[0x2A]; 

        block[0x2A] = temp_block[0x31]; block[0x32] = temp_block[0x38]; 

        block[0x3A] = temp_block[0x39]; block[0x26] = temp_block[0x32]; 

        block[0x39] = temp_block[0x2B]; block[0x03] = temp_block[0x24]; 

        if(last_non_zero_p1 <= 40) goto end;

        block[0x1E] = temp_block[0x1D]; block[0x25] = temp_block[0x16]; 

        block[0x1D] = temp_block[0x0F]; block[0x2D] = temp_block[0x17]; 

        block[0x17] = temp_block[0x1E]; block[0x0E] = temp_block[0x25]; 

        block[0x31] = temp_block[0x2C]; block[0x2B] = temp_block[0x33]; 

        if(last_non_zero_p1 <= 48) goto end;

        block[0x36] = temp_block[0x3A]; block[0x3B] = temp_block[0x3B]; 

        block[0x23] = temp_block[0x34]; block[0x3C] = temp_block[0x2D]; 

        block[0x07] = temp_block[0x26]; block[0x1F] = temp_block[0x1F]; 

        block[0x0F] = temp_block[0x27]; block[0x35] = temp_block[0x2E]; 

        if(last_non_zero_p1 <= 56) goto end;

        block[0x2E] = temp_block[0x35]; block[0x33] = temp_block[0x3C]; 

        block[0x3E] = temp_block[0x3D]; block[0x27] = temp_block[0x36]; 

        block[0x3D] = temp_block[0x2F]; block[0x2F] = temp_block[0x37]; 

        block[0x37] = temp_block[0x3E]; block[0x3F] = temp_block[0x3F];

    }else if(s->dsp.idct_permutation_type == FF_LIBMPEG2_IDCT_PERM){

        if(last_non_zero_p1 <= 1) goto end;

        block[0x04] = temp_block[0x01]; 

        block[0x08] = temp_block[0x08]; block[0x10] = temp_block[0x10]; 

        if(last_non_zero_p1 <= 4) goto end;

        block[0x0C] = temp_block[0x09]; block[0x01] = temp_block[0x02]; 

        block[0x05] = temp_block[0x03]; 

        if(last_non_zero_p1 <= 7) goto end;

        block[0x09] = temp_block[0x0A]; block[0x14] = temp_block[0x11]; 

        block[0x18] = temp_block[0x18]; block[0x20] = temp_block[0x20]; 

        if(last_non_zero_p1 <= 11) goto end;

        block[0x1C] = temp_block[0x19]; 

        block[0x11] = temp_block[0x12]; block[0x0D] = temp_block[0x0B]; 

        block[0x02] = temp_block[0x04]; block[0x06] = temp_block[0x05]; 

        if(last_non_zero_p1 <= 16) goto end;

        block[0x0A] = temp_block[0x0C]; block[0x15] = temp_block[0x13]; 

        block[0x19] = temp_block[0x1A]; block[0x24] = temp_block[0x21]; 

        block[0x28] = temp_block[0x28]; block[0x30] = temp_block[0x30]; 

        block[0x2C] = temp_block[0x29]; block[0x21] = temp_block[0x22]; 

        if(last_non_zero_p1 <= 24) goto end;

        block[0x1D] = temp_block[0x1B]; block[0x12] = temp_block[0x14]; 

        block[0x0E] = temp_block[0x0D]; block[0x03] = temp_block[0x06]; 

        block[0x07] = temp_block[0x07]; block[0x0B] = temp_block[0x0E]; 

        block[0x16] = temp_block[0x15]; block[0x1A] = temp_block[0x1C]; 

        if(last_non_zero_p1 <= 32) goto end;

        block[0x25] = temp_block[0x23]; block[0x29] = temp_block[0x2A]; 

        block[0x34] = temp_block[0x31]; block[0x38] = temp_block[0x38]; 

        block[0x3C] = temp_block[0x39]; block[0x31] = temp_block[0x32]; 

        block[0x2D] = temp_block[0x2B]; block[0x22] = temp_block[0x24]; 

        if(last_non_zero_p1 <= 40) goto end;

        block[0x1E] = temp_block[0x1D]; block[0x13] = temp_block[0x16]; 

        block[0x0F] = temp_block[0x0F]; block[0x17] = temp_block[0x17]; 

        block[0x1B] = temp_block[0x1E]; block[0x26] = temp_block[0x25]; 

        block[0x2A] = temp_block[0x2C]; block[0x35] = temp_block[0x33]; 

        if(last_non_zero_p1 <= 48) goto end;

        block[0x39] = temp_block[0x3A]; block[0x3D] = temp_block[0x3B]; 

        block[0x32] = temp_block[0x34]; block[0x2E] = temp_block[0x2D]; 

            block[0x23] = temp_block[0x26]; block[0x1F] = temp_block[0x1F]; 

        block[0x27] = temp_block[0x27]; block[0x2B] = temp_block[0x2E]; 

        if(last_non_zero_p1 <= 56) goto end;

        block[0x36] = temp_block[0x35]; block[0x3A] = temp_block[0x3C]; 

        block[0x3E] = temp_block[0x3D]; block[0x33] = temp_block[0x36]; 

        block[0x2F] = temp_block[0x2F]; block[0x37] = temp_block[0x37]; 

        block[0x3B] = temp_block[0x3E]; block[0x3F] = temp_block[0x3F];

    }else{

        if(last_non_zero_p1 <= 1) goto end;

        block[0x01] = temp_block[0x01]; 

        block[0x08] = temp_block[0x08]; block[0x10] = temp_block[0x10]; 

        if(last_non_zero_p1 <= 4) goto end;

        block[0x09] = temp_block[0x09]; block[0x02] = temp_block[0x02]; 

        block[0x03] = temp_block[0x03]; 

        if(last_non_zero_p1 <= 7) goto end;

        block[0x0A] = temp_block[0x0A]; block[0x11] = temp_block[0x11]; 

        block[0x18] = temp_block[0x18]; block[0x20] = temp_block[0x20]; 

        if(last_non_zero_p1 <= 11) goto end;

        block[0x19] = temp_block[0x19]; 

        block[0x12] = temp_block[0x12]; block[0x0B] = temp_block[0x0B]; 

        block[0x04] = temp_block[0x04]; block[0x05] = temp_block[0x05]; 

        if(last_non_zero_p1 <= 16) goto end;

        block[0x0C] = temp_block[0x0C]; block[0x13] = temp_block[0x13]; 

        block[0x1A] = temp_block[0x1A]; block[0x21] = temp_block[0x21]; 

        block[0x28] = temp_block[0x28]; block[0x30] = temp_block[0x30]; 

        block[0x29] = temp_block[0x29]; block[0x22] = temp_block[0x22]; 

        if(last_non_zero_p1 <= 24) goto end;

        block[0x1B] = temp_block[0x1B]; block[0x14] = temp_block[0x14]; 

        block[0x0D] = temp_block[0x0D]; block[0x06] = temp_block[0x06]; 

        block[0x07] = temp_block[0x07]; block[0x0E] = temp_block[0x0E]; 

        block[0x15] = temp_block[0x15]; block[0x1C] = temp_block[0x1C]; 

        if(last_non_zero_p1 <= 32) goto end;

        block[0x23] = temp_block[0x23]; block[0x2A] = temp_block[0x2A]; 

        block[0x31] = temp_block[0x31]; block[0x38] = temp_block[0x38]; 

        block[0x39] = temp_block[0x39]; block[0x32] = temp_block[0x32]; 

        block[0x2B] = temp_block[0x2B]; block[0x24] = temp_block[0x24]; 

        if(last_non_zero_p1 <= 40) goto end;

        block[0x1D] = temp_block[0x1D]; block[0x16] = temp_block[0x16]; 

        block[0x0F] = temp_block[0x0F]; block[0x17] = temp_block[0x17]; 

        block[0x1E] = temp_block[0x1E]; block[0x25] = temp_block[0x25]; 

        block[0x2C] = temp_block[0x2C]; block[0x33] = temp_block[0x33]; 

        if(last_non_zero_p1 <= 48) goto end;

        block[0x3A] = temp_block[0x3A]; block[0x3B] = temp_block[0x3B]; 

        block[0x34] = temp_block[0x34]; block[0x2D] = temp_block[0x2D]; 

        block[0x26] = temp_block[0x26]; block[0x1F] = temp_block[0x1F]; 

        block[0x27] = temp_block[0x27]; block[0x2E] = temp_block[0x2E]; 

        if(last_non_zero_p1 <= 56) goto end;

        block[0x35] = temp_block[0x35]; block[0x3C] = temp_block[0x3C]; 

        block[0x3D] = temp_block[0x3D]; block[0x36] = temp_block[0x36]; 

        block[0x2F] = temp_block[0x2F]; block[0x37] = temp_block[0x37]; 

        block[0x3E] = temp_block[0x3E]; block[0x3F] = temp_block[0x3F];

    }

    end:

 



    return last_non_zero_p1 - 1;

}
