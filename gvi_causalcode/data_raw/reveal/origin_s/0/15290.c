static inline int cng_rand ( int * state , int base ) {
 * state = ( * state * 521 + 259 ) & 0xFFFF ;
 return ( * state & 0x7FFF ) * base >> 15 ;
 }