static int brenext ( struct vars * v , chr pc ) {
 chr c = ( chr ) pc ;
 switch ( c ) {
 case CHR ( '*' ) : if ( LASTTYPE ( EMPTY ) || LASTTYPE ( '(' ) || LASTTYPE ( '^' ) ) RETV ( PLAIN , c ) ;
 RET ( '*' ) ;
 break ;
 case CHR ( '[' ) : if ( HAVE ( 6 ) && * ( v -> now + 0 ) == CHR ( '[' ) && * ( v -> now + 1 ) == CHR ( ':' ) && ( * ( v -> now + 2 ) == CHR ( '<' ) || * ( v -> now + 2 ) == CHR ( '>' ) ) && * ( v -> now + 3 ) == CHR ( ':' ) && * ( v -> now + 4 ) == CHR ( ']' ) && * ( v -> now + 5 ) == CHR ( ']' ) ) {
 c = * ( v -> now + 2 ) ;
 v -> now += 6 ;
 NOTE ( REG_UNONPOSIX ) ;
 RET ( ( c == CHR ( '<' ) ) ? '<' : '>' ) ;
 }
 INTOCON ( L_BRACK ) ;
 if ( NEXT1 ( '^' ) ) {
 v -> now ++ ;
 RETV ( '[' , 0 ) ;
 }
 RETV ( '[' , 1 ) ;
 break ;
 case CHR ( '.' ) : RET ( '.' ) ;
 break ;
 case CHR ( '^' ) : if ( LASTTYPE ( EMPTY ) ) RET ( '^' ) ;
 if ( LASTTYPE ( '(' ) ) {
 NOTE ( REG_UUNSPEC ) ;
 RET ( '^' ) ;
 }
 RETV ( PLAIN , c ) ;
 break ;
 case CHR ( '$' ) : if ( v -> cflags & REG_EXPANDED ) skip ( v ) ;
 if ( ATEOS ( ) ) RET ( '$' ) ;
 if ( NEXT2 ( '\\' , ')' ) ) {
 NOTE ( REG_UUNSPEC ) ;
 RET ( '$' ) ;
 }
 RETV ( PLAIN , c ) ;
 break ;
 case CHR ( '\\' ) : break ;
 default : RETV ( PLAIN , c ) ;
 break ;
 }
 assert ( c == CHR ( '\\' ) ) ;
 if ( ATEOS ( ) ) FAILW ( REG_EESCAPE ) ;
 c = * v -> now ++ ;
 switch ( c ) {
 case CHR ( '{
' ) : INTOCON ( L_BBND ) ;
 NOTE ( REG_UBOUNDS ) ;
 RET ( '{
' ) ;
 break ;
 case CHR ( '(' ) : RETV ( '(' , 1 ) ;
 break ;
 case CHR ( ')' ) : RETV ( ')' , c ) ;
 break ;
 case CHR ( '<' ) : NOTE ( REG_UNONPOSIX ) ;
 RET ( '<' ) ;
 break ;
 case CHR ( '>' ) : NOTE ( REG_UNONPOSIX ) ;
 RET ( '>' ) ;
 break ;
 case CHR ( '1' ) : case CHR ( '2' ) : case CHR ( '3' ) : case CHR ( '4' ) : case CHR ( '5' ) : case CHR ( '6' ) : case CHR ( '7' ) : case CHR ( '8' ) : case CHR ( '9' ) : NOTE ( REG_UBACKREF ) ;
 RETV ( BACKREF , ( chr ) DIGITVAL ( c ) ) ;
 break ;
 default : if ( iscalnum ( c ) ) {
 NOTE ( REG_UBSALNUM ) ;
 NOTE ( REG_UUNSPEC ) ;
 }
 RETV ( PLAIN , c ) ;
 break ;
 }
 assert ( NOTREACHED ) ;
 return 0 ;
 }