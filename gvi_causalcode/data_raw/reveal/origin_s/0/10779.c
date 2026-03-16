static const char * U_CALLCONV _UTF16GetName ( const UConverter * cnv ) {
 if ( UCNV_GET_VERSION ( cnv ) == 0 ) {
 return "UTF-16" ;
 }
 else if ( UCNV_GET_VERSION ( cnv ) == 1 ) {
 return "UTF-16,version=1" ;
 }
 else {
 return "UTF-16,version=2" ;
 }
 }