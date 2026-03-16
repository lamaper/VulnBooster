void putshort ( FILE * file , int sval ) {
 if ( sval < - 32768 || sval > 65535 ) if ( ! short_too_long_warned ) {
 IError ( _ ( "Attempt to output %d into a 16-bit field. It will be truncated and the file may not be useful." ) , sval ) ;
 short_too_long_warned = 1 ;
 }
 putc ( ( sval >> 8 ) & 0xff , file ) ;
 putc ( sval & 0xff , file ) ;
 }