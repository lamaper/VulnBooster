static const char * _UTF16LEGetName ( const UConverter * cnv ) {
 if ( UCNV_GET_VERSION ( cnv ) == 0 ) {
 return "UTF-16LE" ;
 }
 else {
 return "UTF-16LE,version=1" ;
 }
 }