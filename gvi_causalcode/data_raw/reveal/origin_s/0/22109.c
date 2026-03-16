int ttfcopyfile ( FILE * ttf , FILE * other , int pos , const char * tab_name ) {
 int ch ;
 int ret = 1 ;
 if ( ferror ( ttf ) || ferror ( other ) ) {
 IError ( "Disk error of some nature. Perhaps no space on device?\nGenerated font will be unusable" ) ;
 }
 else if ( pos != ftell ( ttf ) ) {
 IError ( "File Offset wrong for ttf table (%s), %d expected %d" , tab_name , ftell ( ttf ) , pos ) ;
 }
 rewind ( other ) ;
 while ( ( ch = getc ( other ) ) != EOF ) putc ( ch , ttf ) ;
 if ( ferror ( other ) ) ret = 0 ;
 if ( fclose ( other ) ) ret = 0 ;
 return ( ret ) ;
 }