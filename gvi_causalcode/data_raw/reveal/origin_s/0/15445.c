static UBool isNewline ( UChar32 c ) {
 switch ( c ) {
 case 0x000A : case 0x2029 : lineCount ++ ;
 case 0x000D : return TRUE ;
 default : return FALSE ;
 }
 }