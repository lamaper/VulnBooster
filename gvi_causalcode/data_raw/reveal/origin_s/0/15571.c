static void astream_try_base64_decode ( struct attachment_istream_part * part , const unsigned char * data , size_t size ) {
 size_t i ;
 int ret ;
 if ( part -> base64_failed || part -> base64_state == BASE64_STATE_EOM ) return ;
 for ( i = 0 ;
 i < size ;
 i ++ ) {
 ret = astream_try_base64_decode_char ( part , i , ( char ) data [ i ] ) ;
 if ( ret <= 0 ) {
 if ( ret < 0 ) part -> base64_failed = TRUE ;
 break ;
 }
 }
 }