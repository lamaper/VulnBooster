static int64_t getutime(void)

{


    struct rusage rusage;



    getrusage(RUSAGE_SELF, &rusage);

    return (rusage.ru_utime.tv_sec * 1000000LL) + rusage.ru_utime.tv_usec;


  return av_gettime();


}
