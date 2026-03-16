static ssize_t compress_filter_read ( struct archive_read_filter * self , const void * * pblock ) {
 struct private_data * state ;
 unsigned char * p , * start , * end ;
 int ret ;
 state = ( struct private_data * ) self -> data ;
 if ( state -> end_of_stream ) {
 * pblock = NULL ;
 return ( 0 ) ;
 }
 p = start = ( unsigned char * ) state -> out_block ;
 end = start + state -> out_block_size ;
 while ( p < end && ! state -> end_of_stream ) {
 if ( state -> stackp > state -> stack ) {
 * p ++ = * -- state -> stackp ;
 }
 else {
 ret = next_code ( self ) ;
 if ( ret == - 1 ) state -> end_of_stream = ret ;
 else if ( ret != ARCHIVE_OK ) return ( ret ) ;
 }
 }
 * pblock = start ;
 return ( p - start ) ;
 }