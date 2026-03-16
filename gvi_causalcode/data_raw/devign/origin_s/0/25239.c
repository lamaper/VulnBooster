av_cold void ff_vorbisdsp_init_x86(VorbisDSPContext *dsp)

{


    int cpu_flags = av_get_cpu_flags();


    if (cpu_flags & AV_CPU_FLAG_3DNOW)

        dsp->vorbis_inverse_coupling = ff_vorbis_inverse_coupling_3dnow;


    if (cpu_flags & AV_CPU_FLAG_SSE)

        dsp->vorbis_inverse_coupling = ff_vorbis_inverse_coupling_sse;


}
