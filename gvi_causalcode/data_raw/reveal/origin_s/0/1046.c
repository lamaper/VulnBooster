static const char * U_CALLCONV _UTF7GetName ( const UConverter * cnv ) {
 switch ( cnv -> fromUnicodeStatus >> 28 ) {
 case 1 : return "UTF-7,version=1" ;
 default : return "UTF-7" ;
 }
 }