static void qpeg_decode_intra ( QpegContext * qctx , uint8_t * dst , int stride , int width , int height ) {
 int i ;
 int code ;
 int c0 , c1 ;
 int run , copy ;
 int filled = 0 ;
 int rows_to_go ;
 rows_to_go = height ;
 height -- ;
 dst = dst + height * stride ;
 while ( ( bytestream2_get_bytes_left ( & qctx -> buffer ) > 0 ) && ( rows_to_go > 0 ) ) {
 code = bytestream2_get_byte ( & qctx -> buffer ) ;
 run = copy = 0 ;
 if ( code == 0xFC ) break ;
 if ( code >= 0xF8 ) {
 c0 = bytestream2_get_byte ( & qctx -> buffer ) ;
 c1 = bytestream2_get_byte ( & qctx -> buffer ) ;
 run = ( ( code & 0x7 ) << 16 ) + ( c0 << 8 ) + c1 + 2 ;
 }
 else if ( code >= 0xF0 ) {
 c0 = bytestream2_get_byte ( & qctx -> buffer ) ;
 run = ( ( code & 0xF ) << 8 ) + c0 + 2 ;
 }
 else if ( code >= 0xE0 ) {
 run = ( code & 0x1F ) + 2 ;
 }
 else if ( code >= 0xC0 ) {
 c0 = bytestream2_get_byte ( & qctx -> buffer ) ;
 c1 = bytestream2_get_byte ( & qctx -> buffer ) ;
 copy = ( ( code & 0x3F ) << 16 ) + ( c0 << 8 ) + c1 + 1 ;
 }
 else if ( code >= 0x80 ) {
 c0 = bytestream2_get_byte ( & qctx -> buffer ) ;
 copy = ( ( code & 0x7F ) << 8 ) + c0 + 1 ;
 }
 else {
 copy = code + 1 ;
 }
 if ( run ) {
 int p ;
 p = bytestream2_get_byte ( & qctx -> buffer ) ;
 for ( i = 0 ;
 i < run ;
 i ++ ) {
 dst [ filled ++ ] = p ;
 if ( filled >= width ) {
 filled = 0 ;
 dst -= stride ;
 rows_to_go -- ;
 if ( rows_to_go <= 0 ) break ;
 }
 }
 }
 else {
 for ( i = 0 ;
 i < copy ;
 i ++ ) {
 dst [ filled ++ ] = bytestream2_get_byte ( & qctx -> buffer ) ;
 if ( filled >= width ) {
 filled = 0 ;
 dst -= stride ;
 rows_to_go -- ;
 if ( rows_to_go <= 0 ) break ;
 }
 }
 }
 }
 }