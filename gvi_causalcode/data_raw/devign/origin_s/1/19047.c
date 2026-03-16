void ff_hyscale_fast_mmxext(SwsContext *c, int16_t *dst,

                                 int dstWidth, const uint8_t *src,

                                 int srcW, int xInc)

{

    int32_t *filterPos = c->hLumFilterPos;

    int16_t *filter    = c->hLumFilter;

    void    *mmxextFilterCode = c->lumMmxextFilterCode;

    int i;


    uint64_t retsave;



    uint64_t ebxsave;





    __asm__ volatile(


        "mov               -8(%%rsp), %%"FF_REG_a"    \n\t"

        "mov            %%"FF_REG_a", %5              \n\t"   



        "mov            %%"FF_REG_b", %5              \n\t"   



        "pxor                  %%mm7, %%mm7           \n\t"

        "mov                      %0, %%"FF_REG_c"    \n\t"

        "mov                      %1, %%"FF_REG_D"    \n\t"

        "mov                      %2, %%"FF_REG_d"    \n\t"

        "mov                      %3, %%"FF_REG_b"    \n\t"

        "xor            %%"FF_REG_a", %%"FF_REG_a"    \n\t"  

        PREFETCH"      (%%"FF_REG_c")                 \n\t"

        PREFETCH"    32(%%"FF_REG_c")                 \n\t"

        PREFETCH"    64(%%"FF_REG_c")                 \n\t"



        "movl               (%%"FF_REG_b"), %%esi        \n\t"\

        "call                          *%4               \n\t"\

        "movl (%%"FF_REG_b", %%"FF_REG_a"), %%esi        \n\t"\

        "add                  %%"FF_REG_S", %%"FF_REG_c" \n\t"\

        "add                  %%"FF_REG_a", %%"FF_REG_D" \n\t"\

        "xor                  %%"FF_REG_a", %%"FF_REG_a" \n\t"\



        "movl               (%%"FF_REG_b"), %%esi        \n\t"\

        "call                          *%4               \n\t"\

        "addl (%%"FF_REG_b", %%"FF_REG_a"), %%"FF_REG_c" \n\t"\

        "add                  %%"FF_REG_a", %%"FF_REG_D" \n\t"\

        "xor                  %%"FF_REG_a", %%"FF_REG_a" \n\t"\




        CALL_MMXEXT_FILTER_CODE

        CALL_MMXEXT_FILTER_CODE

        CALL_MMXEXT_FILTER_CODE

        CALL_MMXEXT_FILTER_CODE

        CALL_MMXEXT_FILTER_CODE

        CALL_MMXEXT_FILTER_CODE

        CALL_MMXEXT_FILTER_CODE

        CALL_MMXEXT_FILTER_CODE


        "mov                      %5, %%"FF_REG_a" \n\t"

        "mov            %%"FF_REG_a", -8(%%rsp)    \n\t"



        "mov                      %5, %%"FF_REG_b" \n\t"



        :: "m" (src), "m" (dst), "m" (filter), "m" (filterPos),

           "m" (mmxextFilterCode)


          ,"m"(retsave)



          ,"m" (ebxsave)



        : "%"FF_REG_a, "%"FF_REG_c, "%"FF_REG_d, "%"FF_REG_S, "%"FF_REG_D


         ,"%"FF_REG_b


    );



    for (i=dstWidth-1; (i*xInc)>>16 >=srcW-1; i--)

        dst[i] = src[srcW-1]*128;

}
