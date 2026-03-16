static int compress_bidder_init ( struct archive_read_filter * self ) {
 struct private_data * state ;
 static const size_t out_block_size = 64 * 1024 ;
 void * out_block ;
 int code ;
 self -> code = ARCHIVE_FILTER_COMPRESS ;
 self -> name = "compress (.Z)" ;
 state = ( struct private_data * ) calloc ( sizeof ( * state ) , 1 ) ;
 out_block = malloc ( out_block_size ) ;
 if ( state == NULL || out_block == NULL ) {
 free ( out_block ) ;
 free ( state ) ;
 archive_set_error ( & self -> archive -> archive , ENOMEM , "Can't allocate data for %s decompression" , self -> name ) ;
 return ( ARCHIVE_FATAL ) ;
 }
 self -> data = state ;
 state -> out_block_size = out_block_size ;
 state -> out_block = out_block ;
 self -> read = compress_filter_read ;
 self -> skip = NULL ;
 self -> close = compress_filter_close ;
 ( void ) getbits ( self , 8 ) ;
 ( void ) getbits ( self , 8 ) ;
 code = getbits ( self , 8 ) ;
 if ( ( code & 0x1f ) > 16 ) {
 archive_set_error ( & self -> archive -> archive , - 1 , "Invalid compressed data" ) ;
 return ( ARCHIVE_FATAL ) ;
 }
 state -> maxcode_bits = code & 0x1f ;
 state -> maxcode = ( 1 << state -> maxcode_bits ) ;
 state -> use_reset_code = code & 0x80 ;
 state -> free_ent = 256 ;
 state -> stackp = state -> stack ;
 if ( state -> use_reset_code ) state -> free_ent ++ ;
 state -> bits = 9 ;
 state -> section_end_code = ( 1 << state -> bits ) - 1 ;
 state -> oldcode = - 1 ;
 for ( code = 255 ;
 code >= 0 ;
 code -- ) {
 state -> prefix [ code ] = 0 ;
 state -> suffix [ code ] = code ;
 }
 next_code ( self ) ;
 return ( ARCHIVE_OK ) ;
 }