static void VGA_printf ( uint8_t * s ) {
 uint16_t * arg_ptr ;
 unsigned int format_width , i ;
 int in_format ;
 uint16_t arg , digit , nibble ;
 uint8_t c ;
 arg_ptr = ( uint16_t * ) ( ( void * ) & s ) ;
 in_format = 0 ;
 format_width = 0 ;
 while ( ( c = * s ) != '\0' ) {
 if ( c == '%' ) {
 in_format = 1 ;
 format_width = 0 ;
 }
 else if ( in_format ) {
 if ( ( c >= '0' ) && ( c <= '9' ) ) {
 format_width = ( format_width * 10 ) + ( c - '0' ) ;
 }
 else if ( c == 'x' ) {
 arg_ptr ++ ;
 arg = * arg_ptr ;
 if ( format_width == 0 ) format_width = 4 ;
 digit = format_width - 1 ;
 for ( i = 0 ;
 i < format_width ;
 i ++ ) {
 nibble = ( arg >> ( 4 * digit ) ) & 0x000f ;
 if ( nibble <= 9 ) PPC_io_writeb ( PPC_IO_BASE + 0x500 , nibble + '0' ) ;
 else PPC_io_writeb ( PPC_IO_BASE + 0x500 , nibble + 'A' ) ;
 digit -- ;
 }
 in_format = 0 ;
 }
 }
 else {
 PPC_io_writeb ( PPC_IO_BASE + 0x500 , c ) ;
 }
 s ++ ;
 }
 }