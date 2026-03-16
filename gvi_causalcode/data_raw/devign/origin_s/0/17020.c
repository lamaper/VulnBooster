DECLARE_WEIGHT(sse2)

DECLARE_WEIGHT(ssse3)


static void OP ## rv40_qpel ##SIZE ##_mc ##PH ##PV ##OPT(uint8_t *dst,  \

                                                         uint8_t *src,  \

                                                         int stride)    \

{                                                                       \

    int i;                                                              \

    if (PH && PV) {                                                     \

        DECLARE_ALIGNED(16, uint8_t, tmp)[SIZE * (SIZE + 5)];           \

        uint8_t *tmpptr = tmp + SIZE * 2;                               \

        src -= stride * 2;                                              \

                                                                        \

        for (i = 0; i < SIZE; i += LOOPSIZE)                            \

            ff_put_rv40_qpel_h ##OPT(tmp + i, SIZE, src + i, stride,    \

                                     SIZE + 5, HCOFF(PH));              \

        for (i = 0; i < SIZE; i += LOOPSIZE)                            \

            ff_ ##OP ##rv40_qpel_v ##OPT(dst + i, stride, tmpptr + i,   \

                                         SIZE, SIZE, VCOFF(PV));        \

    } else if (PV) {                                                    \

        for (i = 0; i < SIZE; i += LOOPSIZE)                            \

            ff_ ##OP ##rv40_qpel_v ## OPT(dst + i, stride, src + i,     \

                                          stride, SIZE, VCOFF(PV));     \

    } else {                                                            \

        for (i = 0; i < SIZE; i += LOOPSIZE)                            \

            ff_ ##OP ##rv40_qpel_h ## OPT(dst + i, stride, src + i,     \

                                          stride, SIZE, HCOFF(PH));     \

    }                                                                   \

};


    QPEL_FUNC_DECL(OP,  8, PH, PV, OPT)  \

    QPEL_FUNC_DECL(OP, 16, PH, PV, OPT)


void ff_ ##OP ##rv40_qpel_h ##OPT(uint8_t *dst, ptrdiff_t dstStride,    \

                                  const uint8_t *src,                   \

                                  ptrdiff_t srcStride,                  \

                                  int len, int m);                      \

void ff_ ##OP ##rv40_qpel_v ##OPT(uint8_t *dst, ptrdiff_t dstStride,    \

                                  const uint8_t *src,                   \

                                  ptrdiff_t srcStride,                  \

                                  int len, int m);                      \

QPEL_FUNCS_DECL(OP, 0, 1, OPT)                                          \

QPEL_FUNCS_DECL(OP, 0, 3, OPT)                                          \

QPEL_FUNCS_DECL(OP, 1, 0, OPT)                                          \

QPEL_FUNCS_DECL(OP, 1, 1, OPT)                                          \

QPEL_FUNCS_DECL(OP, 1, 2, OPT)                                          \

QPEL_FUNCS_DECL(OP, 1, 3, OPT)                                          \

QPEL_FUNCS_DECL(OP, 2, 1, OPT)                                          \

QPEL_FUNCS_DECL(OP, 2, 2, OPT)                                          \

QPEL_FUNCS_DECL(OP, 2, 3, OPT)                                          \

QPEL_FUNCS_DECL(OP, 3, 0, OPT)                                          \

QPEL_FUNCS_DECL(OP, 3, 1, OPT)                                          \

QPEL_FUNCS_DECL(OP, 3, 2, OPT)




QPEL_MC_DECL(put_, _ssse3)

QPEL_MC_DECL(avg_, _ssse3)







QPEL_MC_DECL(put_, _sse2)

QPEL_MC_DECL(avg_, _sse2)










QPEL_MC_DECL(put_, _mmx)



QPEL_MC_DECL(avg_, _mmx2)



QPEL_MC_DECL(avg_, _3dnow)



    c-> OP ## pixels_tab[2 - SIZE / 8][4 * PV + PH] = OP ## rv40_qpel ##SIZE ## _mc ##PH ##PV ##OPT;


    QPEL_FUNC_SET(OP,  8, PH, PV, OPT)          \

    QPEL_FUNC_SET(OP, 16, PH, PV, OPT)


QPEL_FUNCS_SET (OP, 0, 1, OPT) \

QPEL_FUNCS_SET (OP, 0, 3, OPT) \

QPEL_FUNCS_SET (OP, 1, 0, OPT) \

QPEL_FUNCS_SET (OP, 1, 1, OPT) \

QPEL_FUNCS_SET (OP, 1, 2, OPT) \

QPEL_FUNCS_SET (OP, 1, 3, OPT) \

QPEL_FUNCS_SET (OP, 2, 1, OPT) \

QPEL_FUNCS_SET (OP, 2, 2, OPT) \

QPEL_FUNCS_SET (OP, 2, 3, OPT) \

QPEL_FUNCS_SET (OP, 3, 0, OPT) \

QPEL_FUNCS_SET (OP, 3, 1, OPT) \

QPEL_FUNCS_SET (OP, 3, 2, OPT)




void ff_rv40dsp_init_x86(RV34DSPContext *c, DSPContext *dsp)

{


    int mm_flags = av_get_cpu_flags();



    if (mm_flags & AV_CPU_FLAG_MMX) {

        c->put_chroma_pixels_tab[0] = ff_put_rv40_chroma_mc8_mmx;

        c->put_chroma_pixels_tab[1] = ff_put_rv40_chroma_mc4_mmx;


        c->put_pixels_tab[0][15] = ff_put_rv40_qpel16_mc33_mmx;

        c->put_pixels_tab[1][15] = ff_put_rv40_qpel8_mc33_mmx;

        c->avg_pixels_tab[0][15] = ff_avg_rv40_qpel16_mc33_mmx;

        c->avg_pixels_tab[1][15] = ff_avg_rv40_qpel8_mc33_mmx;



        QPEL_MC_SET(put_, _mmx)


    }

    if (mm_flags & AV_CPU_FLAG_MMXEXT) {

        c->avg_chroma_pixels_tab[0] = ff_avg_rv40_chroma_mc8_mmx2;

        c->avg_chroma_pixels_tab[1] = ff_avg_rv40_chroma_mc4_mmx2;

        c->rv40_weight_pixels_tab[0][0] = ff_rv40_weight_func_rnd_16_mmx2;

        c->rv40_weight_pixels_tab[0][1] = ff_rv40_weight_func_rnd_8_mmx2;

        c->rv40_weight_pixels_tab[1][0] = ff_rv40_weight_func_nornd_16_mmx2;

        c->rv40_weight_pixels_tab[1][1] = ff_rv40_weight_func_nornd_8_mmx2;


        QPEL_MC_SET(avg_, _mmx2)


    } else if (mm_flags & AV_CPU_FLAG_3DNOW) {

        c->avg_chroma_pixels_tab[0] = ff_avg_rv40_chroma_mc8_3dnow;

        c->avg_chroma_pixels_tab[1] = ff_avg_rv40_chroma_mc4_3dnow;


        QPEL_MC_SET(avg_, _3dnow)


    }

    if (mm_flags & AV_CPU_FLAG_SSE2) {

        c->rv40_weight_pixels_tab[0][0] = ff_rv40_weight_func_rnd_16_sse2;

        c->rv40_weight_pixels_tab[0][1] = ff_rv40_weight_func_rnd_8_sse2;

        c->rv40_weight_pixels_tab[1][0] = ff_rv40_weight_func_nornd_16_sse2;

        c->rv40_weight_pixels_tab[1][1] = ff_rv40_weight_func_nornd_8_sse2;

        QPEL_MC_SET(put_, _sse2)

        QPEL_MC_SET(avg_, _sse2)

    }

    if (mm_flags & AV_CPU_FLAG_SSSE3) {

        c->rv40_weight_pixels_tab[0][0] = ff_rv40_weight_func_rnd_16_ssse3;

        c->rv40_weight_pixels_tab[0][1] = ff_rv40_weight_func_rnd_8_ssse3;

        c->rv40_weight_pixels_tab[1][0] = ff_rv40_weight_func_nornd_16_ssse3;

        c->rv40_weight_pixels_tab[1][1] = ff_rv40_weight_func_nornd_8_ssse3;

        QPEL_MC_SET(put_, _ssse3)

        QPEL_MC_SET(avg_, _ssse3)

    }


}
