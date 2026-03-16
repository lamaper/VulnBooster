int BrotliStateIsStreamStart ( const BrotliState * s ) {
 return ( s -> state == BROTLI_STATE_UNINITED && BrotliGetAvailableBits ( & s -> br ) == 0 ) ;
 }