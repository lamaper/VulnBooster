static inline void decode_1p_track ( int * out , int code , int m , int off ) {
 int pos = BIT_STR ( code , 0 , m ) + off ;
 out [ 0 ] = BIT_POS ( code , m ) ? - pos : pos ;
 }