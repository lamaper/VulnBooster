qcms_bool compute_precache ( struct curveType * trc , uint8_t * output ) {
 if ( trc -> type == PARAMETRIC_CURVE_TYPE ) {
 float gamma_table [ 256 ] ;
 uint16_t gamma_table_uint [ 256 ] ;
 uint16_t i ;
 uint16_t * inverted ;
 int inverted_size = 256 ;
 compute_curve_gamma_table_type_parametric ( gamma_table , trc -> parameter , trc -> count ) ;
 for ( i = 0 ;
 i < 256 ;
 i ++ ) {
 gamma_table_uint [ i ] = ( uint16_t ) ( gamma_table [ i ] * 65535 ) ;
 }
 if ( inverted_size < 256 ) inverted_size = 256 ;
 inverted = invert_lut ( gamma_table_uint , 256 , inverted_size ) ;
 if ( ! inverted ) return false ;
 compute_precache_lut ( output , inverted , inverted_size ) ;
 free ( inverted ) ;
 }
 else {
 if ( trc -> count == 0 ) {
 compute_precache_linear ( output ) ;
 }
 else if ( trc -> count == 1 ) {
 compute_precache_pow ( output , 1. / u8Fixed8Number_to_float ( trc -> data [ 0 ] ) ) ;
 }
 else {
 uint16_t * inverted ;
 int inverted_size = trc -> count ;
 if ( inverted_size < 256 ) inverted_size = 256 ;
 inverted = invert_lut ( trc -> data , trc -> count , inverted_size ) ;
 if ( ! inverted ) return false ;
 compute_precache_lut ( output , inverted , inverted_size ) ;
 free ( inverted ) ;
 }
 }
 return true ;
 }