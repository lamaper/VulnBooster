void host_cpuid(uint32_t function, uint32_t count,

                uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx)

{


    uint32_t vec[4];


    asm volatile("cpuid"

                 : "=a"(vec[0]), "=b"(vec[1]),

                   "=c"(vec[2]), "=d"(vec[3])

                 : "0"(function), "c"(count) : "cc");


    asm volatile("pusha \n\t"

                 "cpuid \n\t"

                 "mov %%eax, 0(%2) \n\t"

                 "mov %%ebx, 4(%2) \n\t"

                 "mov %%ecx, 8(%2) \n\t"

                 "mov %%edx, 12(%2) \n\t"

                 "popa"

                 : : "a"(function), "c"(count), "S"(vec)

                 : "memory", "cc");




    if (eax)

        *eax = vec[0];

    if (ebx)

        *ebx = vec[1];

    if (ecx)

        *ecx = vec[2];

    if (edx)

        *edx = vec[3];


}
