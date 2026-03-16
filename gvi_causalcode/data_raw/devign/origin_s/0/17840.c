static void body(uint32_t ABCD[4], uint32_t X[16])

{

    int i av_unused;

    uint32_t t;

    uint32_t a = ABCD[3];

    uint32_t b = ABCD[2];

    uint32_t c = ABCD[1];

    uint32_t d = ABCD[0];


    for (i = 0; i < 16; i++)

        X[i] = av_bswap32(X[i]);



    for (i = 0; i < 64; i++) {

        CORE(i, a, b, c, d);

        t = d;

        d = c;

        c = b;

        b = a;

        a = t;

    }



    CORE( i,   a,b,c,d); CORE((i+1),d,a,b,c);                           \

    CORE((i+2),c,d,a,b); CORE((i+3),b,c,d,a)


    CORE4(0); CORE4(16); CORE4(32); CORE4(48);




    ABCD[0] += d;

    ABCD[1] += c;

    ABCD[2] += b;

    ABCD[3] += a;

}
