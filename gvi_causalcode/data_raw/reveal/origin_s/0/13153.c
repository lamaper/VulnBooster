static inline uint32_t replicate32 ( uint32_t a ) {

 a |= a >> 8 ;

 a |= a << 8 ;

 }