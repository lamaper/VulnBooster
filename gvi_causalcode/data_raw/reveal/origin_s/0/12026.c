static int generate_bits_table ( uint32_t * dst , const uint8_t * len_table ) {
 int len , index ;
 uint32_t bits = 0 ;
 for ( len = 32 ;
 len > 0 ;
 len -- ) {
 for ( index = 0 ;
 index < 256 ;
 index ++ ) {
 if ( len_table [ index ] == len ) dst [ index ] = bits ++ ;
 }
 if ( bits & 1 ) {
 av_log ( NULL , AV_LOG_ERROR , "Error generating huffman table\n" ) ;
 return - 1 ;
 }
 bits >>= 1 ;
 }
 return 0 ;
 }