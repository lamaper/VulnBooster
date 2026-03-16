void ff_pngdsp_init_x86(PNGDSPContext *dsp)

{


    int flags = av_get_cpu_flags();


    if (flags & AV_CPU_FLAG_MMX)

        dsp->add_bytes_l2         = ff_add_bytes_l2_mmx;


    if (flags & AV_CPU_FLAG_MMXEXT)

        dsp->add_paeth_prediction = ff_add_png_paeth_prediction_mmx2;

    if (flags & AV_CPU_FLAG_SSE2)

        dsp->add_bytes_l2         = ff_add_bytes_l2_sse2;

    if (flags & AV_CPU_FLAG_SSSE3)

        dsp->add_paeth_prediction = ff_add_png_paeth_prediction_ssse3;


}
