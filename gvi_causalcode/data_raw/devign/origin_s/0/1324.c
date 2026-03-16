av_cold void ff_videodsp_init_x86(VideoDSPContext *ctx, int bpc)

{


    int cpu_flags = av_get_cpu_flags();


    if (EXTERNAL_MMX(cpu_flags) && bpc <= 8) {

        ctx->emulated_edge_mc = emulated_edge_mc_mmx;

    }

    if (EXTERNAL_AMD3DNOW(cpu_flags)) {

        ctx->prefetch = ff_prefetch_3dnow;

    }


    if (EXTERNAL_MMXEXT(cpu_flags)) {

        ctx->prefetch = ff_prefetch_mmxext;


        if (bpc <= 8)

            ctx->emulated_edge_mc = emulated_edge_mc_mmxext;


    }


    if (EXTERNAL_SSE(cpu_flags) && bpc <= 8) {

        ctx->emulated_edge_mc = emulated_edge_mc_sse;

    }


    if (EXTERNAL_SSE2(cpu_flags) && bpc <= 8) {

        ctx->emulated_edge_mc = emulated_edge_mc_sse2;

    }


}
