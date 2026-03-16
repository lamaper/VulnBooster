int BrotliStateIsStreamEnd ( const BrotliState * s ) {
 return s -> state == BROTLI_STATE_DONE ;
 }