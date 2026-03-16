static inline void decode_subblock1 ( int16_t * dst , int code , GetBitContext * gb , VLC * vlc , int q ) {
 int coeff = modulo_three_table [ code ] >> 6 ;
 decode_coeff ( dst , coeff , 3 , gb , vlc , q ) ;
 }