static inline void idct(int16_t *block)

{

        int64_t __attribute__((aligned(8))) align_tmp[16];

        int16_t * const temp= (int16_t*)align_tmp;



        asm volatile(



        "movq " #src0 ", %%mm0          \n\t"  \

        "movq " #src4 ", %%mm1          \n\t"  \

        "movq " #src1 ", %%mm2          \n\t"  \

        "movq " #src5 ", %%mm3          \n\t"  \

        "movq 16(%2), %%mm4             \n\t"  \

        "pmaddwd %%mm0, %%mm4           \n\t"  \

        "movq 24(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm5, %%mm0           \n\t"  \

        "movq 32(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm1, %%mm5           \n\t"  \

        "movq 40(%2), %%mm6             \n\t"  \

        "pmaddwd %%mm6, %%mm1           \n\t"  \

        "movq 48(%2), %%mm7             \n\t"  \

        "pmaddwd %%mm2, %%mm7           \n\t"  \


        "movq %%mm4, %%mm6              \n\t"  \

        "paddd %%mm5, %%mm4             \n\t"  \

        "psubd %%mm5, %%mm6             \n\t"  \

        "movq 56(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm3, %%mm5           \n\t"  \


        "paddd %%mm0, %%mm1             \n\t"  \

        "paddd %%mm0, %%mm0             \n\t" \

        "psubd %%mm1, %%mm0             \n\t"  \

        "pmaddwd 64(%2), %%mm2          \n\t"  \

        "paddd %%mm5, %%mm7             \n\t"  \

        "movq 72(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm3, %%mm5           \n\t"  \

        "paddd %%mm4, %%mm7             \n\t"  \

        "paddd %%mm4, %%mm4             \n\t"  \

        "psubd %%mm7, %%mm4             \n\t"  \

        "paddd %%mm2, %%mm5             \n\t"  \

        "psrad $" #shift ", %%mm7       \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "movq %%mm1, %%mm2              \n\t"  \

        "paddd %%mm5, %%mm1             \n\t"  \

        "psubd %%mm5, %%mm2             \n\t"  \

        "psrad $" #shift ", %%mm1       \n\t"\

        "psrad $" #shift ", %%mm2       \n\t"\

        "packssdw %%mm1, %%mm7          \n\t"  \

        "packssdw %%mm4, %%mm2          \n\t"  \

        "movq %%mm7, " #dst "           \n\t"\

        "movq " #src1 ", %%mm1          \n\t"  \

        "movq 80(%2), %%mm4             \n\t"  \

        "movq %%mm2, 24+" #dst "        \n\t"\

        "pmaddwd %%mm1, %%mm4           \n\t"  \

        "movq 88(%2), %%mm7             \n\t"  \

        "pmaddwd 96(%2), %%mm1          \n\t"  \

        "pmaddwd %%mm3, %%mm7           \n\t"  \

        "movq %%mm0, %%mm2              \n\t"  \

        "pmaddwd 104(%2), %%mm3         \n\t"  \

        "paddd %%mm7, %%mm4             \n\t"  \

        "paddd %%mm4, %%mm2             \n\t"  \

        "psubd %%mm4, %%mm0             \n\t"  \

        "psrad $" #shift ", %%mm2       \n\t"\

        "psrad $" #shift ", %%mm0       \n\t"\

        "movq %%mm6, %%mm4              \n\t"  \

        "paddd %%mm1, %%mm3             \n\t"  \

        "paddd %%mm3, %%mm6             \n\t"  \

        "psubd %%mm3, %%mm4             \n\t"  \

        "psrad $" #shift ", %%mm6       \n\t"\

        "packssdw %%mm6, %%mm2          \n\t"  \

        "movq %%mm2, 8+" #dst "         \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "packssdw %%mm0, %%mm4          \n\t"  \

        "movq %%mm4, 16+" #dst "        \n\t"\


        "movq " #src0 ", %%mm0          \n\t"  \

        "movq " #src4 ", %%mm1          \n\t"  \

        "movq " #src1 ", %%mm2          \n\t"  \

        "movq " #src5 ", %%mm3          \n\t"  \

        "movq 16(%2), %%mm4             \n\t"  \

        "pmaddwd %%mm0, %%mm4           \n\t"  \

        "movq 24(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm5, %%mm0           \n\t"  \

        "movq 32(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm1, %%mm5           \n\t"  \

        "movq 40(%2), %%mm6             \n\t"  \

        "pmaddwd %%mm6, %%mm1           \n\t"  \


        "movq %%mm4, %%mm6              \n\t"  \

        "movq 48(%2), %%mm7             \n\t"  \


        "pmaddwd %%mm2, %%mm7           \n\t"  \

        "paddd %%mm5, %%mm4             \n\t"  \

        "psubd %%mm5, %%mm6             \n\t"  \

        "movq %%mm0, %%mm5              \n\t"  \

        "paddd %%mm1, %%mm0             \n\t"  \

        "psubd %%mm1, %%mm5             \n\t"  \

        "movq 56(%2), %%mm1             \n\t"  \

        "pmaddwd %%mm3, %%mm1           \n\t"  \

        "pmaddwd 64(%2), %%mm2          \n\t"  \

        "paddd %%mm1, %%mm7             \n\t"  \

        "movq 72(%2), %%mm1             \n\t"  \

        "pmaddwd %%mm3, %%mm1           \n\t"  \

        "paddd %%mm4, %%mm7             \n\t"  \

        "paddd %%mm4, %%mm4             \n\t"  \

        "psubd %%mm7, %%mm4             \n\t"  \

        "paddd %%mm2, %%mm1             \n\t"  \

        "psrad $" #shift ", %%mm7       \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "movq %%mm0, %%mm2              \n\t"  \

        "paddd %%mm1, %%mm0             \n\t"  \

        "psubd %%mm1, %%mm2             \n\t"  \

        "psrad $" #shift ", %%mm0       \n\t"\

        "psrad $" #shift ", %%mm2       \n\t"\

        "packssdw %%mm7, %%mm7          \n\t"  \

        "movd %%mm7, " #dst "           \n\t"\

        "packssdw %%mm0, %%mm0          \n\t"  \

        "movd %%mm0, 16+" #dst "        \n\t"\

        "packssdw %%mm2, %%mm2          \n\t"  \

        "movd %%mm2, 96+" #dst "        \n\t"\

        "packssdw %%mm4, %%mm4          \n\t"  \

        "movd %%mm4, 112+" #dst "       \n\t"\

        "movq " #src1 ", %%mm0          \n\t"  \

        "movq 80(%2), %%mm4             \n\t"  \

        "pmaddwd %%mm0, %%mm4           \n\t"  \

        "movq 88(%2), %%mm7             \n\t"  \

        "pmaddwd 96(%2), %%mm0          \n\t"  \

        "pmaddwd %%mm3, %%mm7           \n\t"  \

        "movq %%mm5, %%mm2              \n\t"  \

        "pmaddwd 104(%2), %%mm3         \n\t"  \

        "paddd %%mm7, %%mm4             \n\t"  \

        "paddd %%mm4, %%mm2             \n\t"  \

        "psubd %%mm4, %%mm5             \n\t"  \

        "psrad $" #shift ", %%mm2       \n\t"\

        "psrad $" #shift ", %%mm5       \n\t"\

        "movq %%mm6, %%mm4              \n\t"  \

        "paddd %%mm0, %%mm3             \n\t"  \

        "paddd %%mm3, %%mm6             \n\t"  \

        "psubd %%mm3, %%mm4             \n\t"  \

        "psrad $" #shift ", %%mm6       \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "packssdw %%mm2, %%mm2          \n\t"  \

        "packssdw %%mm6, %%mm6          \n\t"  \

        "movd %%mm2, 32+" #dst "        \n\t"\

        "packssdw %%mm4, %%mm4          \n\t"  \

        "packssdw %%mm5, %%mm5          \n\t"  \

        "movd %%mm6, 48+" #dst "        \n\t"\

        "movd %%mm4, 64+" #dst "        \n\t"\

        "movd %%mm5, 80+" #dst "        \n\t"\


        "movq " #src0 ", %%mm0          \n\t"  \

        "movq " #src4 ", %%mm1          \n\t"  \

        "movq " #src1 ", %%mm2          \n\t"  \

        "movq " #src5 ", %%mm3          \n\t"  \

        "movq "MANGLE(wm1010)", %%mm4   \n\t"\

        "pand %%mm0, %%mm4              \n\t"\

        "por %%mm1, %%mm4               \n\t"\

        "por %%mm2, %%mm4               \n\t"\

        "por %%mm3, %%mm4               \n\t"\

        "packssdw %%mm4,%%mm4           \n\t"\

        "movd %%mm4, %%eax              \n\t"\

        "orl %%eax, %%eax               \n\t"\

        "jz 1f                          \n\t"\

        "movq 16(%2), %%mm4             \n\t"  \

        "pmaddwd %%mm0, %%mm4           \n\t"  \

        "movq 24(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm5, %%mm0           \n\t"  \

        "movq 32(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm1, %%mm5           \n\t"  \

        "movq 40(%2), %%mm6             \n\t"  \

        "pmaddwd %%mm6, %%mm1           \n\t"  \

        "movq 48(%2), %%mm7             \n\t"  \

        "pmaddwd %%mm2, %%mm7           \n\t"  \


        "movq %%mm4, %%mm6              \n\t"  \

        "paddd %%mm5, %%mm4             \n\t"  \

        "psubd %%mm5, %%mm6             \n\t"  \

        "movq 56(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm3, %%mm5           \n\t"  \


        "paddd %%mm0, %%mm1             \n\t"  \

        "paddd %%mm0, %%mm0             \n\t" \

        "psubd %%mm1, %%mm0             \n\t"  \

        "pmaddwd 64(%2), %%mm2          \n\t"  \

        "paddd %%mm5, %%mm7             \n\t"  \

        "movq 72(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm3, %%mm5           \n\t"  \

        "paddd %%mm4, %%mm7             \n\t"  \

        "paddd %%mm4, %%mm4             \n\t"  \

        "psubd %%mm7, %%mm4             \n\t"  \

        "paddd %%mm2, %%mm5             \n\t"  \

        "psrad $" #shift ", %%mm7       \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "movq %%mm1, %%mm2              \n\t"  \

        "paddd %%mm5, %%mm1             \n\t"  \

        "psubd %%mm5, %%mm2             \n\t"  \

        "psrad $" #shift ", %%mm1       \n\t"\

        "psrad $" #shift ", %%mm2       \n\t"\

        "packssdw %%mm1, %%mm7          \n\t"  \

        "packssdw %%mm4, %%mm2          \n\t"  \

        "movq %%mm7, " #dst "           \n\t"\

        "movq " #src1 ", %%mm1          \n\t"  \

        "movq 80(%2), %%mm4             \n\t"  \

        "movq %%mm2, 24+" #dst "        \n\t"\

        "pmaddwd %%mm1, %%mm4           \n\t"  \

        "movq 88(%2), %%mm7             \n\t"  \

        "pmaddwd 96(%2), %%mm1          \n\t"  \

        "pmaddwd %%mm3, %%mm7           \n\t"  \

        "movq %%mm0, %%mm2              \n\t"  \

        "pmaddwd 104(%2), %%mm3         \n\t"  \

        "paddd %%mm7, %%mm4             \n\t"  \

        "paddd %%mm4, %%mm2             \n\t"  \

        "psubd %%mm4, %%mm0             \n\t"  \

        "psrad $" #shift ", %%mm2       \n\t"\

        "psrad $" #shift ", %%mm0       \n\t"\

        "movq %%mm6, %%mm4              \n\t"  \

        "paddd %%mm1, %%mm3             \n\t"  \

        "paddd %%mm3, %%mm6             \n\t"  \

        "psubd %%mm3, %%mm4             \n\t"  \

        "psrad $" #shift ", %%mm6       \n\t"\

        "packssdw %%mm6, %%mm2          \n\t"  \

        "movq %%mm2, 8+" #dst "         \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "packssdw %%mm0, %%mm4          \n\t"  \

        "movq %%mm4, 16+" #dst "        \n\t"\

        "jmp 2f                         \n\t"\

        "1:                             \n\t"\

        "pslld $16, %%mm0               \n\t"\

        "#paddd "MANGLE(d40000)", %%mm0 \n\t"\

        "psrad $13, %%mm0               \n\t"\

        "packssdw %%mm0, %%mm0          \n\t"\

        "movq %%mm0, " #dst "           \n\t"\

        "movq %%mm0, 8+" #dst "         \n\t"\

        "movq %%mm0, 16+" #dst "        \n\t"\

        "movq %%mm0, 24+" #dst "        \n\t"\

        "2:                             \n\t"





 

ROW_IDCT(    (%0),  8(%0), 16(%0), 24(%0),  0(%1),paddd 8(%2), 11)

 



DC_COND_ROW_IDCT(  32(%0), 40(%0), 48(%0), 56(%0), 32(%1),paddd (%2), 11)

DC_COND_ROW_IDCT(  64(%0), 72(%0), 80(%0), 88(%0), 64(%1),paddd (%2), 11)

DC_COND_ROW_IDCT(  96(%0),104(%0),112(%0),120(%0), 96(%1),paddd (%2), 11)





 

COL_IDCT(    (%1), 64(%1), 32(%1),  96(%1),  0(%0),/nop, 20)

COL_IDCT(   8(%1), 72(%1), 40(%1), 104(%1),  4(%0),/nop, 20)

COL_IDCT(  16(%1), 80(%1), 48(%1), 112(%1),  8(%0),/nop, 20)

COL_IDCT(  24(%1), 88(%1), 56(%1), 120(%1), 12(%0),/nop, 20)



        "movq " #src0 ", %%mm0          \n\t"  \

        "movq " #src4 ", %%mm1          \n\t"  \

        "movq " #src1 ", %%mm2          \n\t"  \

        "movq " #src5 ", %%mm3          \n\t"  \

        "movq "MANGLE(wm1010)", %%mm4   \n\t"\

        "pand %%mm0, %%mm4              \n\t"\

        "por %%mm1, %%mm4               \n\t"\

        "por %%mm2, %%mm4               \n\t"\

        "por %%mm3, %%mm4               \n\t"\

        "packssdw %%mm4,%%mm4           \n\t"\

        "movd %%mm4, %%eax              \n\t"\

        "orl %%eax, %%eax               \n\t"\

        "jz 1f                          \n\t"\

        "movq 16(%2), %%mm4             \n\t"  \

        "pmaddwd %%mm0, %%mm4           \n\t"  \

        "movq 24(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm5, %%mm0           \n\t"  \

        "movq 32(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm1, %%mm5           \n\t"  \

        "movq 40(%2), %%mm6             \n\t"  \

        "pmaddwd %%mm6, %%mm1           \n\t"  \

        "movq 48(%2), %%mm7             \n\t"  \

        "pmaddwd %%mm2, %%mm7           \n\t"  \


        "movq %%mm4, %%mm6              \n\t"  \

        "paddd %%mm5, %%mm4             \n\t"  \

        "psubd %%mm5, %%mm6             \n\t"  \

        "movq 56(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm3, %%mm5           \n\t"  \


        "paddd %%mm0, %%mm1             \n\t"  \

        "paddd %%mm0, %%mm0             \n\t" \

        "psubd %%mm1, %%mm0             \n\t"  \

        "pmaddwd 64(%2), %%mm2          \n\t"  \

        "paddd %%mm5, %%mm7             \n\t"  \

        "movq 72(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm3, %%mm5           \n\t"  \

        "paddd %%mm4, %%mm7             \n\t"  \

        "paddd %%mm4, %%mm4             \n\t"  \

        "psubd %%mm7, %%mm4             \n\t"  \

        "paddd %%mm2, %%mm5             \n\t"  \

        "psrad $" #shift ", %%mm7       \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "movq %%mm1, %%mm2              \n\t"  \

        "paddd %%mm5, %%mm1             \n\t"  \

        "psubd %%mm5, %%mm2             \n\t"  \

        "psrad $" #shift ", %%mm1       \n\t"\

        "psrad $" #shift ", %%mm2       \n\t"\

        "packssdw %%mm1, %%mm7          \n\t"  \

        "packssdw %%mm4, %%mm2          \n\t"  \

        "movq %%mm7, " #dst "           \n\t"\

        "movq " #src1 ", %%mm1          \n\t"  \

        "movq 80(%2), %%mm4             \n\t"  \

        "movq %%mm2, 24+" #dst "        \n\t"\

        "pmaddwd %%mm1, %%mm4           \n\t"  \

        "movq 88(%2), %%mm7             \n\t"  \

        "pmaddwd 96(%2), %%mm1          \n\t"  \

        "pmaddwd %%mm3, %%mm7           \n\t"  \

        "movq %%mm0, %%mm2              \n\t"  \

        "pmaddwd 104(%2), %%mm3         \n\t"  \

        "paddd %%mm7, %%mm4             \n\t"  \

        "paddd %%mm4, %%mm2             \n\t"  \

        "psubd %%mm4, %%mm0             \n\t"  \

        "psrad $" #shift ", %%mm2       \n\t"\

        "psrad $" #shift ", %%mm0       \n\t"\

        "movq %%mm6, %%mm4              \n\t"  \

        "paddd %%mm1, %%mm3             \n\t"  \

        "paddd %%mm3, %%mm6             \n\t"  \

        "psubd %%mm3, %%mm4             \n\t"  \

        "psrad $" #shift ", %%mm6       \n\t"\

        "packssdw %%mm6, %%mm2          \n\t"  \

        "movq %%mm2, 8+" #dst "         \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "packssdw %%mm0, %%mm4          \n\t"  \

        "movq %%mm4, 16+" #dst "        \n\t"\

        "jmp 2f                         \n\t"\

        "1:                             \n\t"\

        "pslld $16, %%mm0               \n\t"\

        "paddd "MANGLE(d40000)", %%mm0  \n\t"\

        "psrad $13, %%mm0               \n\t"\

        "packssdw %%mm0, %%mm0          \n\t"\

        "movq %%mm0, " #dst "           \n\t"\

        "movq %%mm0, 8+" #dst "         \n\t"\

        "movq %%mm0, 16+" #dst "        \n\t"\

        "movq %%mm0, 24+" #dst "        \n\t"\

        "2:                             \n\t"


        "movq " #src0 ", %%mm0          \n\t"  \

        "movq " #src4 ", %%mm1          \n\t"  \

        "movq " #src1 ", %%mm2          \n\t"  \

        "movq " #src5 ", %%mm3          \n\t"  \

        "movq %%mm0, %%mm4              \n\t"\

        "por %%mm1, %%mm4               \n\t"\

        "por %%mm2, %%mm4               \n\t"\

        "por %%mm3, %%mm4               \n\t"\

        "packssdw %%mm4,%%mm4           \n\t"\

        "movd %%mm4, %%eax              \n\t"\

        "orl %%eax, %%eax               \n\t"\

        "jz " #bt "                     \n\t"\

        "movq 16(%2), %%mm4             \n\t"  \

        "pmaddwd %%mm0, %%mm4           \n\t"  \

        "movq 24(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm5, %%mm0           \n\t"  \

        "movq 32(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm1, %%mm5           \n\t"  \

        "movq 40(%2), %%mm6             \n\t"  \

        "pmaddwd %%mm6, %%mm1           \n\t"  \

        "movq 48(%2), %%mm7             \n\t"  \

        "pmaddwd %%mm2, %%mm7           \n\t"  \


        "movq %%mm4, %%mm6              \n\t"  \

        "paddd %%mm5, %%mm4             \n\t"  \

        "psubd %%mm5, %%mm6             \n\t"  \

        "movq 56(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm3, %%mm5           \n\t"  \


        "paddd %%mm0, %%mm1             \n\t"  \

        "paddd %%mm0, %%mm0             \n\t" \

        "psubd %%mm1, %%mm0             \n\t"  \

        "pmaddwd 64(%2), %%mm2          \n\t"  \

        "paddd %%mm5, %%mm7             \n\t"  \

        "movq 72(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm3, %%mm5           \n\t"  \

        "paddd %%mm4, %%mm7             \n\t"  \

        "paddd %%mm4, %%mm4             \n\t"  \

        "psubd %%mm7, %%mm4             \n\t"  \

        "paddd %%mm2, %%mm5             \n\t"  \

        "psrad $" #shift ", %%mm7       \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "movq %%mm1, %%mm2              \n\t"  \

        "paddd %%mm5, %%mm1             \n\t"  \

        "psubd %%mm5, %%mm2             \n\t"  \

        "psrad $" #shift ", %%mm1       \n\t"\

        "psrad $" #shift ", %%mm2       \n\t"\

        "packssdw %%mm1, %%mm7          \n\t"  \

        "packssdw %%mm4, %%mm2          \n\t"  \

        "movq %%mm7, " #dst "           \n\t"\

        "movq " #src1 ", %%mm1          \n\t"  \

        "movq 80(%2), %%mm4             \n\t"  \

        "movq %%mm2, 24+" #dst "        \n\t"\

        "pmaddwd %%mm1, %%mm4           \n\t"  \

        "movq 88(%2), %%mm7             \n\t"  \

        "pmaddwd 96(%2), %%mm1          \n\t"  \

        "pmaddwd %%mm3, %%mm7           \n\t"  \

        "movq %%mm0, %%mm2              \n\t"  \

        "pmaddwd 104(%2), %%mm3         \n\t"  \

        "paddd %%mm7, %%mm4             \n\t"  \

        "paddd %%mm4, %%mm2             \n\t"  \

        "psubd %%mm4, %%mm0             \n\t"  \

        "psrad $" #shift ", %%mm2       \n\t"\

        "psrad $" #shift ", %%mm0       \n\t"\

        "movq %%mm6, %%mm4              \n\t"  \

        "paddd %%mm1, %%mm3             \n\t"  \

        "paddd %%mm3, %%mm6             \n\t"  \

        "psubd %%mm3, %%mm4             \n\t"  \

        "psrad $" #shift ", %%mm6       \n\t"\

        "packssdw %%mm6, %%mm2          \n\t"  \

        "movq %%mm2, 8+" #dst "         \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "packssdw %%mm0, %%mm4          \n\t"  \

        "movq %%mm4, 16+" #dst "        \n\t"\


        "movq " #src0 ", %%mm0          \n\t"  \

        "movq " #src4 ", %%mm1          \n\t"  \

        "movq " #src1 ", %%mm2          \n\t"  \

        "movq " #src5 ", %%mm3          \n\t"  \

        "movq 16(%2), %%mm4             \n\t"  \

        "pmaddwd %%mm0, %%mm4           \n\t"  \

        "movq 24(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm5, %%mm0           \n\t"  \

        "movq 32(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm1, %%mm5           \n\t"  \

        "movq 40(%2), %%mm6             \n\t"  \

        "pmaddwd %%mm6, %%mm1           \n\t"  \

        "movq 48(%2), %%mm7             \n\t"  \

        "pmaddwd %%mm2, %%mm7           \n\t"  \


        "movq %%mm4, %%mm6              \n\t"  \

        "paddd %%mm5, %%mm4             \n\t"  \

        "psubd %%mm5, %%mm6             \n\t"  \

        "movq 56(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm3, %%mm5           \n\t"  \


        "paddd %%mm0, %%mm1             \n\t"  \

        "paddd %%mm0, %%mm0             \n\t" \

        "psubd %%mm1, %%mm0             \n\t"  \

        "pmaddwd 64(%2), %%mm2          \n\t"  \

        "paddd %%mm5, %%mm7             \n\t"  \

        "movq 72(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm3, %%mm5           \n\t"  \

        "paddd %%mm4, %%mm7             \n\t"  \

        "paddd %%mm4, %%mm4             \n\t"  \

        "psubd %%mm7, %%mm4             \n\t"  \

        "paddd %%mm2, %%mm5             \n\t"  \

        "psrad $" #shift ", %%mm7       \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "movq %%mm1, %%mm2              \n\t"  \

        "paddd %%mm5, %%mm1             \n\t"  \

        "psubd %%mm5, %%mm2             \n\t"  \

        "psrad $" #shift ", %%mm1       \n\t"\

        "psrad $" #shift ", %%mm2       \n\t"\

        "packssdw %%mm1, %%mm7          \n\t"  \

        "packssdw %%mm4, %%mm2          \n\t"  \

        "movq %%mm7, " #dst "           \n\t"\

        "movq " #src1 ", %%mm1          \n\t"  \

        "movq 80(%2), %%mm4             \n\t"  \

        "movq %%mm2, 24+" #dst "        \n\t"\

        "pmaddwd %%mm1, %%mm4           \n\t"  \

        "movq 88(%2), %%mm7             \n\t"  \

        "pmaddwd 96(%2), %%mm1          \n\t"  \

        "pmaddwd %%mm3, %%mm7           \n\t"  \

        "movq %%mm0, %%mm2              \n\t"  \

        "pmaddwd 104(%2), %%mm3         \n\t"  \

        "paddd %%mm7, %%mm4             \n\t"  \

        "paddd %%mm4, %%mm2             \n\t"  \

        "psubd %%mm4, %%mm0             \n\t"  \

        "psrad $" #shift ", %%mm2       \n\t"\

        "psrad $" #shift ", %%mm0       \n\t"\

        "movq %%mm6, %%mm4              \n\t"  \

        "paddd %%mm1, %%mm3             \n\t"  \

        "paddd %%mm3, %%mm6             \n\t"  \

        "psubd %%mm3, %%mm4             \n\t"  \

        "psrad $" #shift ", %%mm6       \n\t"\

        "packssdw %%mm6, %%mm2          \n\t"  \

        "movq %%mm2, 8+" #dst "         \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "packssdw %%mm0, %%mm4          \n\t"  \

        "movq %%mm4, 16+" #dst "        \n\t"\



 

DC_COND_IDCT(  0(%0),  8(%0), 16(%0), 24(%0),  0(%1),paddd 8(%2), 11)

Z_COND_IDCT(  32(%0), 40(%0), 48(%0), 56(%0), 32(%1),paddd (%2), 11, 4f)

Z_COND_IDCT(  64(%0), 72(%0), 80(%0), 88(%0), 64(%1),paddd (%2), 11, 2f)

Z_COND_IDCT(  96(%0),104(%0),112(%0),120(%0), 96(%1),paddd (%2), 11, 1f)



        "movq " #src0 ", %%mm0          \n\t"  \

        "movq " #src4 ", %%mm1          \n\t"  \

        "movq " #src1 ", %%mm2          \n\t"  \

        "movq " #src5 ", %%mm3          \n\t"  \

        "movq 16(%2), %%mm4             \n\t"  \

        "pmaddwd %%mm0, %%mm4           \n\t"  \

        "movq 24(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm5, %%mm0           \n\t"  \

        "movq 32(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm1, %%mm5           \n\t"  \

        "movq 40(%2), %%mm6             \n\t"  \

        "pmaddwd %%mm6, %%mm1           \n\t"  \


        "movq %%mm4, %%mm6              \n\t"  \

        "movq 48(%2), %%mm7             \n\t"  \


        "pmaddwd %%mm2, %%mm7           \n\t"  \

        "paddd %%mm5, %%mm4             \n\t"  \

        "psubd %%mm5, %%mm6             \n\t"  \

        "movq %%mm0, %%mm5              \n\t"  \

        "paddd %%mm1, %%mm0             \n\t"  \

        "psubd %%mm1, %%mm5             \n\t"  \

        "movq 56(%2), %%mm1             \n\t"  \

        "pmaddwd %%mm3, %%mm1           \n\t"  \

        "pmaddwd 64(%2), %%mm2          \n\t"  \

        "paddd %%mm1, %%mm7             \n\t"  \

        "movq 72(%2), %%mm1             \n\t"  \

        "pmaddwd %%mm3, %%mm1           \n\t"  \

        "paddd %%mm4, %%mm7             \n\t"  \

        "paddd %%mm4, %%mm4             \n\t"  \

        "psubd %%mm7, %%mm4             \n\t"  \

        "paddd %%mm2, %%mm1             \n\t"  \

        "psrad $" #shift ", %%mm7       \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "movq %%mm0, %%mm2              \n\t"  \

        "paddd %%mm1, %%mm0             \n\t"  \

        "psubd %%mm1, %%mm2             \n\t"  \

        "psrad $" #shift ", %%mm0       \n\t"\

        "psrad $" #shift ", %%mm2       \n\t"\

        "packssdw %%mm7, %%mm7          \n\t"  \

        "movd %%mm7, " #dst "           \n\t"\

        "packssdw %%mm0, %%mm0          \n\t"  \

        "movd %%mm0, 16+" #dst "        \n\t"\

        "packssdw %%mm2, %%mm2          \n\t"  \

        "movd %%mm2, 96+" #dst "        \n\t"\

        "packssdw %%mm4, %%mm4          \n\t"  \

        "movd %%mm4, 112+" #dst "       \n\t"\

        "movq " #src1 ", %%mm0          \n\t"  \

        "movq 80(%2), %%mm4             \n\t"  \

        "pmaddwd %%mm0, %%mm4           \n\t"  \

        "movq 88(%2), %%mm7             \n\t"  \

        "pmaddwd 96(%2), %%mm0          \n\t"  \

        "pmaddwd %%mm3, %%mm7           \n\t"  \

        "movq %%mm5, %%mm2              \n\t"  \

        "pmaddwd 104(%2), %%mm3         \n\t"  \

        "paddd %%mm7, %%mm4             \n\t"  \

        "paddd %%mm4, %%mm2             \n\t"  \

        "psubd %%mm4, %%mm5             \n\t"  \

        "psrad $" #shift ", %%mm2       \n\t"\

        "psrad $" #shift ", %%mm5       \n\t"\

        "movq %%mm6, %%mm4              \n\t"  \

        "paddd %%mm0, %%mm3             \n\t"  \

        "paddd %%mm3, %%mm6             \n\t"  \

        "psubd %%mm3, %%mm4             \n\t"  \

        "psrad $" #shift ", %%mm6       \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "packssdw %%mm2, %%mm2          \n\t"  \

        "packssdw %%mm6, %%mm6          \n\t"  \

        "movd %%mm2, 32+" #dst "        \n\t"\

        "packssdw %%mm4, %%mm4          \n\t"  \

        "packssdw %%mm5, %%mm5          \n\t"  \

        "movd %%mm6, 48+" #dst "        \n\t"\

        "movd %%mm4, 64+" #dst "        \n\t"\

        "movd %%mm5, 80+" #dst "        \n\t"





 

IDCT(    (%1), 64(%1), 32(%1),  96(%1),  0(%0),/nop, 20)

IDCT(   8(%1), 72(%1), 40(%1), 104(%1),  4(%0),/nop, 20)

IDCT(  16(%1), 80(%1), 48(%1), 112(%1),  8(%0),/nop, 20)

IDCT(  24(%1), 88(%1), 56(%1), 120(%1), 12(%0),/nop, 20)

        "jmp 9f                         \n\t"



        "#.balign 16                    \n\t"\

        "4:                             \n\t"

Z_COND_IDCT(  64(%0), 72(%0), 80(%0), 88(%0), 64(%1),paddd (%2), 11, 6f)

Z_COND_IDCT(  96(%0),104(%0),112(%0),120(%0), 96(%1),paddd (%2), 11, 5f)



        "movq " #src0 ", %%mm0          \n\t"  \

        "movq " #src4 ", %%mm1          \n\t"  \

        "movq " #src5 ", %%mm3          \n\t"  \

        "movq 16(%2), %%mm4             \n\t"  \

        "pmaddwd %%mm0, %%mm4           \n\t"  \

        "movq 24(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm5, %%mm0           \n\t"  \

        "movq 32(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm1, %%mm5           \n\t"  \

        "movq 40(%2), %%mm6             \n\t"  \

        "pmaddwd %%mm6, %%mm1           \n\t"  \


        "movq %%mm4, %%mm6              \n\t"  \


        "paddd %%mm5, %%mm4             \n\t"  \

        "psubd %%mm5, %%mm6             \n\t"  \

        "movq %%mm0, %%mm5              \n\t"  \

        "paddd %%mm1, %%mm0             \n\t"  \

        "psubd %%mm1, %%mm5             \n\t"  \

        "movq 56(%2), %%mm1             \n\t"  \

        "pmaddwd %%mm3, %%mm1           \n\t"  \

        "movq 72(%2), %%mm7             \n\t"  \

        "pmaddwd %%mm3, %%mm7           \n\t"  \

        "paddd %%mm4, %%mm1             \n\t"  \

        "paddd %%mm4, %%mm4             \n\t"  \

        "psubd %%mm1, %%mm4             \n\t"  \

        "psrad $" #shift ", %%mm1       \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "movq %%mm0, %%mm2              \n\t"  \

        "paddd %%mm7, %%mm0             \n\t"  \

        "psubd %%mm7, %%mm2             \n\t"  \

        "psrad $" #shift ", %%mm0       \n\t"\

        "psrad $" #shift ", %%mm2       \n\t"\

        "packssdw %%mm1, %%mm1          \n\t"  \

        "movd %%mm1, " #dst "           \n\t"\

        "packssdw %%mm0, %%mm0          \n\t"  \

        "movd %%mm0, 16+" #dst "        \n\t"\

        "packssdw %%mm2, %%mm2          \n\t"  \

        "movd %%mm2, 96+" #dst "        \n\t"\

        "packssdw %%mm4, %%mm4          \n\t"  \

        "movd %%mm4, 112+" #dst "       \n\t"\

        "movq 88(%2), %%mm1             \n\t"  \

        "pmaddwd %%mm3, %%mm1           \n\t"  \

        "movq %%mm5, %%mm2              \n\t"  \

        "pmaddwd 104(%2), %%mm3         \n\t"  \

        "paddd %%mm1, %%mm2             \n\t"  \

        "psubd %%mm1, %%mm5             \n\t"  \

        "psrad $" #shift ", %%mm2       \n\t"\

        "psrad $" #shift ", %%mm5       \n\t"\

        "movq %%mm6, %%mm1              \n\t"  \

        "paddd %%mm3, %%mm6             \n\t"  \

        "psubd %%mm3, %%mm1             \n\t"  \

        "psrad $" #shift ", %%mm6       \n\t"\

        "psrad $" #shift ", %%mm1       \n\t"\

        "packssdw %%mm2, %%mm2          \n\t"  \

        "packssdw %%mm6, %%mm6          \n\t"  \

        "movd %%mm2, 32+" #dst "        \n\t"\

        "packssdw %%mm1, %%mm1          \n\t"  \

        "packssdw %%mm5, %%mm5          \n\t"  \

        "movd %%mm6, 48+" #dst "        \n\t"\

        "movd %%mm1, 64+" #dst "        \n\t"\

        "movd %%mm5, 80+" #dst "        \n\t"



 

IDCT(    (%1), 64(%1), 32(%1),  96(%1),  0(%0),/nop, 20)

IDCT(   8(%1), 72(%1), 40(%1), 104(%1),  4(%0),/nop, 20)

IDCT(  16(%1), 80(%1), 48(%1), 112(%1),  8(%0),/nop, 20)

IDCT(  24(%1), 88(%1), 56(%1), 120(%1), 12(%0),/nop, 20)

        "jmp 9f                         \n\t"



        "#.balign 16                    \n\t"\

        "6:                             \n\t"

Z_COND_IDCT(  96(%0),104(%0),112(%0),120(%0), 96(%1),paddd (%2), 11, 7f)



        "movq " #src0 ", %%mm0          \n\t"  \

        "movq " #src5 ", %%mm3          \n\t"  \

        "movq 16(%2), %%mm4             \n\t"  \

        "pmaddwd %%mm0, %%mm4           \n\t"  \

        "movq 24(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm5, %%mm0           \n\t"  \


        "movq %%mm4, %%mm6              \n\t"  \


        "movq %%mm0, %%mm5              \n\t"  \

        "movq 56(%2), %%mm1             \n\t"  \

        "pmaddwd %%mm3, %%mm1           \n\t"  \

        "movq 72(%2), %%mm7             \n\t"  \

        "pmaddwd %%mm3, %%mm7           \n\t"  \

        "paddd %%mm4, %%mm1             \n\t"  \

        "paddd %%mm4, %%mm4             \n\t"  \

        "psubd %%mm1, %%mm4             \n\t"  \

        "psrad $" #shift ", %%mm1       \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "movq %%mm0, %%mm2              \n\t"  \

        "paddd %%mm7, %%mm0             \n\t"  \

        "psubd %%mm7, %%mm2             \n\t"  \

        "psrad $" #shift ", %%mm0       \n\t"\

        "psrad $" #shift ", %%mm2       \n\t"\

        "packssdw %%mm1, %%mm1          \n\t"  \

        "movd %%mm1, " #dst "           \n\t"\

        "packssdw %%mm0, %%mm0          \n\t"  \

        "movd %%mm0, 16+" #dst "        \n\t"\

        "packssdw %%mm2, %%mm2          \n\t"  \

        "movd %%mm2, 96+" #dst "        \n\t"\

        "packssdw %%mm4, %%mm4          \n\t"  \

        "movd %%mm4, 112+" #dst "       \n\t"\

        "movq 88(%2), %%mm1             \n\t"  \

        "pmaddwd %%mm3, %%mm1           \n\t"  \

        "movq %%mm5, %%mm2              \n\t"  \

        "pmaddwd 104(%2), %%mm3         \n\t"  \

        "paddd %%mm1, %%mm2             \n\t"  \

        "psubd %%mm1, %%mm5             \n\t"  \

        "psrad $" #shift ", %%mm2       \n\t"\

        "psrad $" #shift ", %%mm5       \n\t"\

        "movq %%mm6, %%mm1              \n\t"  \

        "paddd %%mm3, %%mm6             \n\t"  \

        "psubd %%mm3, %%mm1             \n\t"  \

        "psrad $" #shift ", %%mm6       \n\t"\

        "psrad $" #shift ", %%mm1       \n\t"\

        "packssdw %%mm2, %%mm2          \n\t"  \

        "packssdw %%mm6, %%mm6          \n\t"  \

        "movd %%mm2, 32+" #dst "        \n\t"\

        "packssdw %%mm1, %%mm1          \n\t"  \

        "packssdw %%mm5, %%mm5          \n\t"  \

        "movd %%mm6, 48+" #dst "        \n\t"\

        "movd %%mm1, 64+" #dst "        \n\t"\

        "movd %%mm5, 80+" #dst "        \n\t"





 

IDCT(    (%1), 64(%1), 32(%1),  96(%1),  0(%0),/nop, 20)

IDCT(   8(%1), 72(%1), 40(%1), 104(%1),  4(%0),/nop, 20)

IDCT(  16(%1), 80(%1), 48(%1), 112(%1),  8(%0),/nop, 20)

IDCT(  24(%1), 88(%1), 56(%1), 120(%1), 12(%0),/nop, 20)

        "jmp 9f                         \n\t"



        "#.balign 16                    \n\t"\

        "2:                             \n\t"

Z_COND_IDCT(  96(%0),104(%0),112(%0),120(%0), 96(%1),paddd (%2), 11, 3f)



        "movq " #src0 ", %%mm0          \n\t"  \

        "movq " #src1 ", %%mm2          \n\t"  \

        "movq " #src5 ", %%mm3          \n\t"  \

        "movq 16(%2), %%mm4             \n\t"  \

        "pmaddwd %%mm0, %%mm4           \n\t"  \

        "movq 24(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm5, %%mm0           \n\t"  \


        "movq %%mm4, %%mm6              \n\t"  \

        "movq 48(%2), %%mm7             \n\t"  \


        "pmaddwd %%mm2, %%mm7           \n\t"  \

        "movq %%mm0, %%mm5              \n\t"  \

        "movq 56(%2), %%mm1             \n\t"  \

        "pmaddwd %%mm3, %%mm1           \n\t"  \

        "pmaddwd 64(%2), %%mm2          \n\t"  \

        "paddd %%mm1, %%mm7             \n\t"  \

        "movq 72(%2), %%mm1             \n\t"  \

        "pmaddwd %%mm3, %%mm1           \n\t"  \

        "paddd %%mm4, %%mm7             \n\t"  \

        "paddd %%mm4, %%mm4             \n\t"  \

        "psubd %%mm7, %%mm4             \n\t"  \

        "paddd %%mm2, %%mm1             \n\t"  \

        "psrad $" #shift ", %%mm7       \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "movq %%mm0, %%mm2              \n\t"  \

        "paddd %%mm1, %%mm0             \n\t"  \

        "psubd %%mm1, %%mm2             \n\t"  \

        "psrad $" #shift ", %%mm0       \n\t"\

        "psrad $" #shift ", %%mm2       \n\t"\

        "packssdw %%mm7, %%mm7          \n\t"  \

        "movd %%mm7, " #dst "           \n\t"\

        "packssdw %%mm0, %%mm0          \n\t"  \

        "movd %%mm0, 16+" #dst "        \n\t"\

        "packssdw %%mm2, %%mm2          \n\t"  \

        "movd %%mm2, 96+" #dst "        \n\t"\

        "packssdw %%mm4, %%mm4          \n\t"  \

        "movd %%mm4, 112+" #dst "       \n\t"\

        "movq " #src1 ", %%mm0          \n\t"  \

        "movq 80(%2), %%mm4             \n\t"  \

        "pmaddwd %%mm0, %%mm4           \n\t"  \

        "movq 88(%2), %%mm7             \n\t"  \

        "pmaddwd 96(%2), %%mm0          \n\t"  \

        "pmaddwd %%mm3, %%mm7           \n\t"  \

        "movq %%mm5, %%mm2              \n\t"  \

        "pmaddwd 104(%2), %%mm3         \n\t"  \

        "paddd %%mm7, %%mm4             \n\t"  \

        "paddd %%mm4, %%mm2             \n\t"  \

        "psubd %%mm4, %%mm5             \n\t"  \

        "psrad $" #shift ", %%mm2       \n\t"\

        "psrad $" #shift ", %%mm5       \n\t"\

        "movq %%mm6, %%mm4              \n\t"  \

        "paddd %%mm0, %%mm3             \n\t"  \

        "paddd %%mm3, %%mm6             \n\t"  \

        "psubd %%mm3, %%mm4             \n\t"  \

        "psrad $" #shift ", %%mm6       \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "packssdw %%mm2, %%mm2          \n\t"  \

        "packssdw %%mm6, %%mm6          \n\t"  \

        "movd %%mm2, 32+" #dst "        \n\t"\

        "packssdw %%mm4, %%mm4          \n\t"  \

        "packssdw %%mm5, %%mm5          \n\t"  \

        "movd %%mm6, 48+" #dst "        \n\t"\

        "movd %%mm4, 64+" #dst "        \n\t"\

        "movd %%mm5, 80+" #dst "        \n\t"



 

IDCT(    (%1), 64(%1), 32(%1),  96(%1),  0(%0),/nop, 20)

IDCT(   8(%1), 72(%1), 40(%1), 104(%1),  4(%0),/nop, 20)

IDCT(  16(%1), 80(%1), 48(%1), 112(%1),  8(%0),/nop, 20)

IDCT(  24(%1), 88(%1), 56(%1), 120(%1), 12(%0),/nop, 20)

        "jmp 9f                         \n\t"



        "#.balign 16                    \n\t"\

        "3:                             \n\t"



        "movq " #src0 ", %%mm0          \n\t"  \

        "movq " #src1 ", %%mm2          \n\t"  \

        "movq 16(%2), %%mm4             \n\t"  \

        "pmaddwd %%mm0, %%mm4           \n\t"  \

        "movq 24(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm5, %%mm0           \n\t"  \


        "movq %%mm4, %%mm6              \n\t"  \

        "movq 48(%2), %%mm7             \n\t"  \


        "pmaddwd %%mm2, %%mm7           \n\t"  \

        "movq %%mm0, %%mm5              \n\t"  \

        "movq 64(%2), %%mm3             \n\t"\

        "pmaddwd %%mm2, %%mm3           \n\t"  \

        "paddd %%mm4, %%mm7             \n\t"  \

        "paddd %%mm4, %%mm4             \n\t"  \

        "psubd %%mm7, %%mm4             \n\t"  \

        "psrad $" #shift ", %%mm7       \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "movq %%mm0, %%mm1              \n\t"  \

        "paddd %%mm3, %%mm0             \n\t"  \

        "psubd %%mm3, %%mm1             \n\t"  \

        "psrad $" #shift ", %%mm0       \n\t"\

        "psrad $" #shift ", %%mm1       \n\t"\

        "packssdw %%mm7, %%mm7          \n\t"  \

        "movd %%mm7, " #dst "           \n\t"\

        "packssdw %%mm0, %%mm0          \n\t"  \

        "movd %%mm0, 16+" #dst "        \n\t"\

        "packssdw %%mm1, %%mm1          \n\t"  \

        "movd %%mm1, 96+" #dst "        \n\t"\

        "packssdw %%mm4, %%mm4          \n\t"  \

        "movd %%mm4, 112+" #dst "       \n\t"\

        "movq 80(%2), %%mm4             \n\t"  \

        "pmaddwd %%mm2, %%mm4           \n\t"  \

        "pmaddwd 96(%2), %%mm2          \n\t"  \

        "movq %%mm5, %%mm1              \n\t"  \

        "paddd %%mm4, %%mm1             \n\t"  \

        "psubd %%mm4, %%mm5             \n\t"  \

        "psrad $" #shift ", %%mm1       \n\t"\

        "psrad $" #shift ", %%mm5       \n\t"\

        "movq %%mm6, %%mm4              \n\t"  \

        "paddd %%mm2, %%mm6             \n\t"  \

        "psubd %%mm2, %%mm4             \n\t"  \

        "psrad $" #shift ", %%mm6       \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "packssdw %%mm1, %%mm1          \n\t"  \

        "packssdw %%mm6, %%mm6          \n\t"  \

        "movd %%mm1, 32+" #dst "        \n\t"\

        "packssdw %%mm4, %%mm4          \n\t"  \

        "packssdw %%mm5, %%mm5          \n\t"  \

        "movd %%mm6, 48+" #dst "        \n\t"\

        "movd %%mm4, 64+" #dst "        \n\t"\

        "movd %%mm5, 80+" #dst "        \n\t"





 

IDCT(    (%1), 64(%1), 32(%1),  96(%1),  0(%0),/nop, 20)

IDCT(   8(%1), 72(%1), 40(%1), 104(%1),  4(%0),/nop, 20)

IDCT(  16(%1), 80(%1), 48(%1), 112(%1),  8(%0),/nop, 20)

IDCT(  24(%1), 88(%1), 56(%1), 120(%1), 12(%0),/nop, 20)

        "jmp 9f                         \n\t"



        "#.balign 16                    \n\t"\

        "5:                             \n\t"



        "movq " #src0 ", %%mm0          \n\t"  \

        "movq " #src4 ", %%mm1          \n\t"  \

        "movq 16(%2), %%mm4             \n\t"  \

        "pmaddwd %%mm0, %%mm4           \n\t"  \

        "movq 24(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm5, %%mm0           \n\t"  \

        "movq 32(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm1, %%mm5           \n\t"  \

        "movq 40(%2), %%mm6             \n\t"  \

        "pmaddwd %%mm6, %%mm1           \n\t"  \


        "movq %%mm4, %%mm6              \n\t"  \

        "paddd %%mm5, %%mm4             \n\t"  \


        "psubd %%mm5, %%mm6             \n\t"  \

        "movq %%mm0, %%mm5              \n\t"  \

        "paddd %%mm1, %%mm0             \n\t"  \

        "psubd %%mm1, %%mm5             \n\t"  \

        "movq 8+" #src0 ", %%mm2        \n\t"  \

        "movq 8+" #src4 ", %%mm3        \n\t"  \

        "movq 16(%2), %%mm1             \n\t"  \

        "pmaddwd %%mm2, %%mm1           \n\t"  \

        "movq 24(%2), %%mm7             \n\t"  \

        "pmaddwd %%mm7, %%mm2           \n\t"  \

        "movq 32(%2), %%mm7             \n\t"  \

        "pmaddwd %%mm3, %%mm7           \n\t"  \

        "pmaddwd 40(%2), %%mm3          \n\t"  \


        "paddd %%mm1, %%mm7             \n\t"  \

        "paddd %%mm1, %%mm1             \n\t"  \


        "psubd %%mm7, %%mm1             \n\t"  \

        "paddd %%mm2, %%mm3             \n\t"  \

        "paddd %%mm2, %%mm2             \n\t"  \

        "psubd %%mm3, %%mm2             \n\t"  \

        "psrad $" #shift ", %%mm4       \n\t"\

        "psrad $" #shift ", %%mm7       \n\t"\

        "psrad $" #shift ", %%mm3       \n\t"\

        "packssdw %%mm7, %%mm4          \n\t"  \

        "movq %%mm4, " #dst "           \n\t"\

        "psrad $" #shift ", %%mm0       \n\t"\

        "packssdw %%mm3, %%mm0          \n\t"  \

        "movq %%mm0, 16+" #dst "        \n\t"\

        "movq %%mm0, 96+" #dst "        \n\t"\

        "movq %%mm4, 112+" #dst "       \n\t"\

        "psrad $" #shift ", %%mm5       \n\t"\

        "psrad $" #shift ", %%mm6       \n\t"\

        "psrad $" #shift ", %%mm2       \n\t"\

        "packssdw %%mm2, %%mm5          \n\t"  \

        "movq %%mm5, 32+" #dst "        \n\t"\

        "psrad $" #shift ", %%mm1       \n\t"\

        "packssdw %%mm1, %%mm6          \n\t"  \

        "movq %%mm6, 48+" #dst "        \n\t"\

        "movq %%mm6, 64+" #dst "        \n\t"\

        "movq %%mm5, 80+" #dst "        \n\t"





 

IDCT(    0(%1), 64(%1), 32(%1),  96(%1),  0(%0),/nop, 20)

 

IDCT(  16(%1), 80(%1), 48(%1), 112(%1),  8(%0),/nop, 20)

 

        "jmp 9f                         \n\t"





        "#.balign 16                    \n\t"\

        "1:                             \n\t"



        "movq " #src0 ", %%mm0          \n\t"  \

        "movq " #src4 ", %%mm1          \n\t"  \

        "movq " #src1 ", %%mm2          \n\t"  \

        "movq 16(%2), %%mm4             \n\t"  \

        "pmaddwd %%mm0, %%mm4           \n\t"  \

        "movq 24(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm5, %%mm0           \n\t"  \

        "movq 32(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm1, %%mm5           \n\t"  \

        "movq 40(%2), %%mm6             \n\t"  \

        "pmaddwd %%mm6, %%mm1           \n\t"  \


        "movq %%mm4, %%mm6              \n\t"  \

        "movq 48(%2), %%mm7             \n\t"  \


        "pmaddwd %%mm2, %%mm7           \n\t"  \

        "paddd %%mm5, %%mm4             \n\t"  \

        "psubd %%mm5, %%mm6             \n\t"  \

        "movq %%mm0, %%mm5              \n\t"  \

        "paddd %%mm1, %%mm0             \n\t"  \

        "psubd %%mm1, %%mm5             \n\t"  \

        "movq 64(%2), %%mm1             \n\t"\

        "pmaddwd %%mm2, %%mm1           \n\t"  \

        "paddd %%mm4, %%mm7             \n\t"  \

        "paddd %%mm4, %%mm4             \n\t"  \

        "psubd %%mm7, %%mm4             \n\t"  \

        "psrad $" #shift ", %%mm7       \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "movq %%mm0, %%mm3              \n\t"  \

        "paddd %%mm1, %%mm0             \n\t"  \

        "psubd %%mm1, %%mm3             \n\t"  \

        "psrad $" #shift ", %%mm0       \n\t"\

        "psrad $" #shift ", %%mm3       \n\t"\

        "packssdw %%mm7, %%mm7          \n\t"  \

        "movd %%mm7, " #dst "           \n\t"\

        "packssdw %%mm0, %%mm0          \n\t"  \

        "movd %%mm0, 16+" #dst "        \n\t"\

        "packssdw %%mm3, %%mm3          \n\t"  \

        "movd %%mm3, 96+" #dst "        \n\t"\

        "packssdw %%mm4, %%mm4          \n\t"  \

        "movd %%mm4, 112+" #dst "       \n\t"\

        "movq 80(%2), %%mm4             \n\t"  \

        "pmaddwd %%mm2, %%mm4           \n\t"  \

        "pmaddwd 96(%2), %%mm2          \n\t"  \

        "movq %%mm5, %%mm3              \n\t"  \

        "paddd %%mm4, %%mm3             \n\t"  \

        "psubd %%mm4, %%mm5             \n\t"  \

        "psrad $" #shift ", %%mm3       \n\t"\

        "psrad $" #shift ", %%mm5       \n\t"\

        "movq %%mm6, %%mm4              \n\t"  \

        "paddd %%mm2, %%mm6             \n\t"  \

        "psubd %%mm2, %%mm4             \n\t"  \

        "psrad $" #shift ", %%mm6       \n\t"\

        "packssdw %%mm3, %%mm3          \n\t"  \

        "movd %%mm3, 32+" #dst "        \n\t"\

        "psrad $" #shift ", %%mm4       \n\t"\

        "packssdw %%mm6, %%mm6          \n\t"  \

        "movd %%mm6, 48+" #dst "        \n\t"\

        "packssdw %%mm4, %%mm4          \n\t"  \

        "packssdw %%mm5, %%mm5          \n\t"  \

        "movd %%mm4, 64+" #dst "        \n\t"\

        "movd %%mm5, 80+" #dst "        \n\t"





 

IDCT(    (%1), 64(%1), 32(%1),  96(%1),  0(%0),/nop, 20)

IDCT(   8(%1), 72(%1), 40(%1), 104(%1),  4(%0),/nop, 20)

IDCT(  16(%1), 80(%1), 48(%1), 112(%1),  8(%0),/nop, 20)

IDCT(  24(%1), 88(%1), 56(%1), 120(%1), 12(%0),/nop, 20)

        "jmp 9f                         \n\t"





        "#.balign 16                    \n\t"

        "7:                             \n\t"



        "movq " #src0 ", %%mm0          \n\t"  \

        "movq 16(%2), %%mm4             \n\t"  \

        "pmaddwd %%mm0, %%mm4           \n\t"  \

        "movq 24(%2), %%mm5             \n\t"  \

        "pmaddwd %%mm5, %%mm0           \n\t"  \



        "psrad $" #shift ", %%mm4       \n\t"\

        "psrad $" #shift ", %%mm0       \n\t"\

        "movq 8+" #src0 ", %%mm2        \n\t"  \

        "movq 16(%2), %%mm1             \n\t"  \

        "pmaddwd %%mm2, %%mm1           \n\t"  \

        "movq 24(%2), %%mm7             \n\t"  \

        "pmaddwd %%mm7, %%mm2           \n\t"  \

        "movq 32(%2), %%mm7             \n\t"  \



        "psrad $" #shift ", %%mm1       \n\t"\

        "packssdw %%mm1, %%mm4          \n\t"  \

        "movq %%mm4, " #dst "           \n\t"\

        "psrad $" #shift ", %%mm2       \n\t"\

        "packssdw %%mm2, %%mm0          \n\t"  \

        "movq %%mm0, 16+" #dst "        \n\t"\

        "movq %%mm0, 96+" #dst "        \n\t"\

        "movq %%mm4, 112+" #dst "       \n\t"\

        "movq %%mm0, 32+" #dst "        \n\t"\

        "movq %%mm4, 48+" #dst "        \n\t"\

        "movq %%mm4, 64+" #dst "        \n\t"\

        "movq %%mm0, 80+" #dst "        \n\t"



 

IDCT(   0(%1), 64(%1), 32(%1),  96(%1),  0(%0),/nop, 20)

 

IDCT(  16(%1), 80(%1), 48(%1), 112(%1),  8(%0),/nop, 20)




 



"9: \n\t"

                :: "r" (block), "r" (temp), "r" (coeffs)

                : "%eax"

        );

}
