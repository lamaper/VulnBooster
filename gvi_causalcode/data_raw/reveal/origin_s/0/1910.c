static int kex_string_pair ( unsigned char * * sp , unsigned char * data , size_t data_len , size_t * lenp , unsigned char * * strp ) {
 unsigned char * s = * sp ;
 * lenp = _libssh2_ntohu32 ( s ) ;
 if ( * lenp > ( data_len - ( s - data ) - 4 ) ) return 1 ;
 * strp = s + 4 ;
 s += 4 + * lenp ;
 * sp = s ;
 return 0 ;
 }