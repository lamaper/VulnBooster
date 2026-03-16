int init_sets ( REP_SETS * sets , uint states ) {
 bzero ( ( char * ) sets , sizeof ( * sets ) ) ;
 sets -> size_of_bits = ( ( states + 7 ) / 8 ) ;
 if ( ! ( sets -> set_buffer = ( REP_SET * ) my_malloc ( sizeof ( REP_SET ) * SET_MALLOC_HUNC , MYF ( MY_WME ) ) ) ) return 1 ;
 if ( ! ( sets -> bit_buffer = ( uint * ) my_malloc ( sizeof ( uint ) * sets -> size_of_bits * SET_MALLOC_HUNC , MYF ( MY_WME ) ) ) ) {
 my_free ( sets -> set ) ;
 return 1 ;
 }
 return 0 ;
 }