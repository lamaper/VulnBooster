void printTextRange ( UChar * str , int32_t start , int32_t end ) {
 char charBuf [ 1000 ] ;
 UChar savedEndChar ;
 savedEndChar = str [ end ] ;
 str [ end ] = 0 ;
 u_austrncpy ( charBuf , str + start , sizeof ( charBuf ) - 1 ) ;
 charBuf [ sizeof ( charBuf ) - 1 ] = 0 ;
 printf ( "string[%2d..%2d] \"%s\"\n" , start , end - 1 , charBuf ) ;
 str [ end ] = savedEndChar ;
 }