void helper_divl_EAX_T0(void)

{

    unsigned int den, q, r;

    uint64_t num;

    

    num = ((uint32_t)EAX) | ((uint64_t)((uint32_t)EDX) << 32);

    den = T0;

    if (den == 0) {

        raise_exception(EXCP00_DIVZ);

    }


    r = div32(&q, num, den);


    q = (num / den);

    r = (num % den);


    EAX = (uint32_t)q;

    EDX = (uint32_t)r;

}
