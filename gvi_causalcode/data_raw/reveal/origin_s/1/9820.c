static const char * _UTF16BEGetName ( const UConverter * cnv ) {
 if ( UCNV_GET_VERSION ( cnv ) == 0 ) {
 return "UTF-16BE" ;
 }
 else {
 return "UTF-16BE,version=1" ;
 }
 }