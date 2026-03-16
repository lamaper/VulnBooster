static inline int16_t mace_broken_clip_int16 ( int n ) {
 if ( n > 32767 ) return 32767 ;
 else if ( n < - 32768 ) return - 32767 ;
 else return n ;
 }