static inline uint64_t replicate64 ( uint64_t a ) {

 a |= a >> 8 ;

 a |= a << 8 ;

 }