static void __attribute__((constructor)) init_cpuid_cache(void)

{

    int max = __get_cpuid_max(0, NULL);

    int a, b, c, d;

    unsigned cache = 0;



    if (max >= 1) {

        __cpuid(1, a, b, c, d);

        if (d & bit_SSE2) {

            cache |= CACHE_SSE2;

        }


        if (c & bit_SSE4_1) {

            cache |= CACHE_SSE4;

        }



         

        if ((c & bit_OSXSAVE) && (c & bit_AVX)) {

            __asm("xgetbv" : "=a"(a), "=d"(d) : "c"(0));

            if ((a & 6) == 6) {

                cache |= CACHE_AVX1;

                if (max >= 7) {

                    __cpuid_count(7, 0, a, b, c, d);

                    if (b & bit_AVX2) {

                        cache |= CACHE_AVX2;

                    }

                }

            }

        }


    }

    cpuid_cache = cache;

}
