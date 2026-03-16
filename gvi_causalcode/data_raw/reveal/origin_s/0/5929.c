static int SnifferDecompress ( unsigned char * inbuf , size_t inlen , unsigned char * outbuf , size_t outlen , int * err , gchar * * err_info ) {
 unsigned char * pin = inbuf ;
 unsigned char * pout = outbuf ;
 unsigned char * pin_end = pin + inlen ;
 unsigned char * pout_end = pout + outlen ;
 unsigned int bit_mask ;
 unsigned int bit_value = 0 ;
 unsigned int code_type ;
 unsigned int code_low ;
 int length ;
 int offset ;
 if ( inlen > G_MAXUINT16 ) {
 return ( - 1 ) ;
 }
 bit_mask = 0 ;
 while ( pin < pin_end ) {
 bit_mask = bit_mask >> 1 ;
 if ( 0 == bit_mask ) {
 CHECK_INPUT_POINTER ( 3 ) ;
 bit_mask = 0x8000 ;
 bit_value = pletoh16 ( pin ) ;
 pin += 2 ;
 }
 if ( ! ( bit_mask & bit_value ) ) {
 CHECK_OUTPUT_LENGTH ( 1 ) ;
 * ( pout ++ ) = * ( pin ++ ) ;
 }
 else {
 code_type = ( unsigned int ) ( ( * pin ) >> 4 ) & 0xF ;
 code_low = ( unsigned int ) ( ( * pin ) & 0xF ) ;
 pin ++ ;
 switch ( code_type ) {
 case 0 : length = code_low + 3 ;
 APPEND_RLE_BYTE ( length ) ;
 break ;
 case 1 : CHECK_INPUT_POINTER ( 1 ) ;
 length = code_low + ( ( unsigned int ) ( * pin ++ ) << 4 ) + 19 ;
 APPEND_RLE_BYTE ( length ) ;
 break ;
 case 2 : FETCH_OFFSET_HIGH ;
 CHECK_INPUT_POINTER ( 1 ) ;
 length = ( unsigned int ) ( * pin ++ ) + 16 ;
 APPEND_LZW_STRING ( offset , length ) ;
 break ;
 default : FETCH_OFFSET_HIGH ;
 length = code_type ;
 APPEND_LZW_STRING ( offset , length ) ;
 break ;
 }
 }
 }
 return ( int ) ( pout - outbuf ) ;
 }