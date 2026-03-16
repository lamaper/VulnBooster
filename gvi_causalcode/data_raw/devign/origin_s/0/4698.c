void sws_rgb2rgb_init(int flags)

{


    if (flags & SWS_CPU_CAPS_SSE2)

        rgb2rgb_init_SSE2();

    else if (flags & SWS_CPU_CAPS_MMX2)

        rgb2rgb_init_MMX2();

    else if (flags & SWS_CPU_CAPS_3DNOW)

        rgb2rgb_init_3DNOW();

    else if (flags & SWS_CPU_CAPS_MMX)

        rgb2rgb_init_MMX();

    else


        rgb2rgb_init_C();

}
