static int64_t get_clock(void)

{


	|| defined(__DragonFly__)

    if (use_rt_clock) {

        struct timespec ts;

        clock_gettime(CLOCK_MONOTONIC, &ts);

        return ts.tv_sec * 1000000000LL + ts.tv_nsec;

    } else


    {

         

        struct timeval tv;

        gettimeofday(&tv, NULL);

        return tv.tv_sec * 1000000000LL + (tv.tv_usec * 1000);

    }

}
