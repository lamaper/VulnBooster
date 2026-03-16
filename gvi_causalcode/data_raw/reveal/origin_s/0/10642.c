static UBool isWhitespace ( UChar32 c ) {
 switch ( c ) {
 case 0x000A : case 0x2029 : lineCount ++ ;
 case 0x000D : case 0x0020 : case 0x0009 : case 0xFEFF : return TRUE ;
 default : return FALSE ;
 }
 }