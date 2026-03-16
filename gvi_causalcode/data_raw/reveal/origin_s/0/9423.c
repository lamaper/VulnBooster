static void tee_print_sized_data ( const char * data , unsigned int data_length , unsigned int total_bytes_to_send , bool right_justified ) {
 unsigned int i ;
 const char * p ;
 if ( right_justified ) for ( i = data_length ;
 i < total_bytes_to_send ;
 i ++ ) tee_putc ( ( int ) ' ' , PAGER ) ;
 for ( i = 0 , p = data ;
 i < data_length ;
 i += 1 , p += 1 ) {
 if ( * p == '\0' ) tee_putc ( ( int ) ' ' , PAGER ) ;
 else tee_putc ( ( int ) * p , PAGER ) ;
 }
 if ( ! right_justified ) for ( i = data_length ;
 i < total_bytes_to_send ;
 i ++ ) tee_putc ( ( int ) ' ' , PAGER ) ;
 }