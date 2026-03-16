static void cinepak_decode_codebook ( cvid_codebook * codebook , int chunk_id , int size , const uint8_t * data ) {
 const uint8_t * eod = ( data + size ) ;
 uint32_t flag , mask ;
 int i , n ;
 n = ( chunk_id & 0x04 ) ? 4 : 6 ;
 flag = 0 ;
 mask = 0 ;
 for ( i = 0 ;
 i < 256 ;
 i ++ ) {
 if ( ( chunk_id & 0x01 ) && ! ( mask >>= 1 ) ) {
 if ( ( data + 4 ) > eod ) break ;
 flag = AV_RB32 ( data ) ;
 data += 4 ;
 mask = 0x80000000 ;
 }
 if ( ! ( chunk_id & 0x01 ) || ( flag & mask ) ) {
 if ( ( data + n ) > eod ) break ;
 if ( n == 6 ) {
 codebook [ i ] . y0 = * data ++ ;
 codebook [ i ] . y1 = * data ++ ;
 codebook [ i ] . y2 = * data ++ ;
 codebook [ i ] . y3 = * data ++ ;
 codebook [ i ] . u = 128 + * data ++ ;
 codebook [ i ] . v = 128 + * data ++ ;
 }
 else {
 codebook [ i ] . y0 = * data ++ ;
 codebook [ i ] . y1 = * data ++ ;
 codebook [ i ] . y2 = * data ++ ;
 codebook [ i ] . y3 = * data ++ ;
 codebook [ i ] . u = 128 ;
 codebook [ i ] . v = 128 ;
 }
 }
 }
 }