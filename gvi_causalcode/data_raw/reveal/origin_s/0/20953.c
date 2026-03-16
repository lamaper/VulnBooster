static int next ( struct vars * v ) {
 chr c ;
 if ( ISERR ( ) ) return 0 ;
 v -> lasttype = v -> nexttype ;
 if ( v -> nexttype == EMPTY && ( v -> cflags & REG_BOSONLY ) ) {
 RETV ( SBEGIN , 0 ) ;
 }
 if ( v -> savenow != NULL && ATEOS ( ) ) {
 v -> now = v -> savenow ;
 v -> stop = v -> savestop ;
 v -> savenow = v -> savestop = NULL ;
 }
 if ( v -> cflags & REG_EXPANDED ) switch ( v -> lexcon ) {
 case L_ERE : case L_BRE : case L_EBND : case L_BBND : skip ( v ) ;
 break ;
 }
 if ( ATEOS ( ) ) {
 switch ( v -> lexcon ) {
 case L_ERE : case L_BRE : case L_Q : RET ( EOS ) ;
 break ;
 case L_EBND : case L_BBND : FAILW ( REG_EBRACE ) ;
 break ;
 case L_BRACK : case L_CEL : case L_ECL : case L_CCL : FAILW ( REG_EBRACK ) ;
 break ;
 }
 assert ( NOTREACHED ) ;
 }
 c = * v -> now ++ ;
 switch ( v -> lexcon ) {
 case L_BRE : return brenext ( v , c ) ;
 break ;
 case L_ERE : break ;
 case L_Q : RETV ( PLAIN , c ) ;
 break ;
 case L_BBND : case L_EBND : switch ( c ) {
 case CHR ( '0' ) : case CHR ( '1' ) : case CHR ( '2' ) : case CHR ( '3' ) : case CHR ( '4' ) : case CHR ( '5' ) : case CHR ( '6' ) : case CHR ( '7' ) : case CHR ( '8' ) : case CHR ( '9' ) : RETV ( DIGIT , ( chr ) DIGITVAL ( c ) ) ;
 break ;
 case CHR ( ',' ) : RET ( ',' ) ;
 break ;
 case CHR ( '}
' ) : if ( INCON ( L_EBND ) ) {
 INTOCON ( L_ERE ) ;
 if ( ( v -> cflags & REG_ADVF ) && NEXT1 ( '?' ) ) {
 v -> now ++ ;
 NOTE ( REG_UNONPOSIX ) ;
 RETV ( '}
' , 0 ) ;
 }
 RETV ( '}
' , 1 ) ;
 }
 else FAILW ( REG_BADBR ) ;
 break ;
 case CHR ( '\\' ) : if ( INCON ( L_BBND ) && NEXT1 ( '}
' ) ) {
 v -> now ++ ;
 INTOCON ( L_BRE ) ;
 RET ( '}
' ) ;
 }
 else FAILW ( REG_BADBR ) ;
 break ;
 default : FAILW ( REG_BADBR ) ;
 break ;
 }
 assert ( NOTREACHED ) ;
 break ;
 case L_BRACK : switch ( c ) {
 case CHR ( ']' ) : if ( LASTTYPE ( '[' ) ) RETV ( PLAIN , c ) ;
 else {
 INTOCON ( ( v -> cflags & REG_EXTENDED ) ? L_ERE : L_BRE ) ;
 RET ( ']' ) ;
 }
 break ;
 case CHR ( '\\' ) : NOTE ( REG_UBBS ) ;
 if ( ! ( v -> cflags & REG_ADVF ) ) RETV ( PLAIN , c ) ;
 NOTE ( REG_UNONPOSIX ) ;
 if ( ATEOS ( ) ) FAILW ( REG_EESCAPE ) ;
 ( DISCARD ) lexescape ( v ) ;
 switch ( v -> nexttype ) {
 case PLAIN : return 1 ;
 break ;
 case CCLASS : switch ( v -> nextvalue ) {
 case 'd' : lexnest ( v , brbackd , ENDOF ( brbackd ) ) ;
 break ;
 case 's' : lexnest ( v , brbacks , ENDOF ( brbacks ) ) ;
 break ;
 case 'w' : lexnest ( v , brbackw , ENDOF ( brbackw ) ) ;
 break ;
 default : FAILW ( REG_EESCAPE ) ;
 break ;
 }
 v -> nexttype = v -> lasttype ;
 return next ( v ) ;
 break ;
 }
 FAILW ( REG_EESCAPE ) ;
 break ;
 case CHR ( '-' ) : if ( LASTTYPE ( '[' ) || NEXT1 ( ']' ) ) RETV ( PLAIN , c ) ;
 else RETV ( RANGE , c ) ;
 break ;
 case CHR ( '[' ) : if ( ATEOS ( ) ) FAILW ( REG_EBRACK ) ;
 switch ( * v -> now ++ ) {
 case CHR ( '.' ) : INTOCON ( L_CEL ) ;
 RET ( COLLEL ) ;
 break ;
 case CHR ( '=' ) : INTOCON ( L_ECL ) ;
 NOTE ( REG_ULOCALE ) ;
 RET ( ECLASS ) ;
 break ;
 case CHR ( ':' ) : INTOCON ( L_CCL ) ;
 NOTE ( REG_ULOCALE ) ;
 RET ( CCLASS ) ;
 break ;
 default : v -> now -- ;
 RETV ( PLAIN , c ) ;
 break ;
 }
 assert ( NOTREACHED ) ;
 break ;
 default : RETV ( PLAIN , c ) ;
 break ;
 }
 assert ( NOTREACHED ) ;
 break ;
 case L_CEL : if ( c == CHR ( '.' ) && NEXT1 ( ']' ) ) {
 v -> now ++ ;
 INTOCON ( L_BRACK ) ;
 RETV ( END , '.' ) ;
 }
 else RETV ( PLAIN , c ) ;
 break ;
 case L_ECL : if ( c == CHR ( '=' ) && NEXT1 ( ']' ) ) {
 v -> now ++ ;
 INTOCON ( L_BRACK ) ;
 RETV ( END , '=' ) ;
 }
 else RETV ( PLAIN , c ) ;
 break ;
 case L_CCL : if ( c == CHR ( ':' ) && NEXT1 ( ']' ) ) {
 v -> now ++ ;
 INTOCON ( L_BRACK ) ;
 RETV ( END , ':' ) ;
 }
 else RETV ( PLAIN , c ) ;
 break ;
 default : assert ( NOTREACHED ) ;
 break ;
 }
 assert ( INCON ( L_ERE ) ) ;
 switch ( c ) {
 case CHR ( '|' ) : RET ( '|' ) ;
 break ;
 case CHR ( '*' ) : if ( ( v -> cflags & REG_ADVF ) && NEXT1 ( '?' ) ) {
 v -> now ++ ;
 NOTE ( REG_UNONPOSIX ) ;
 RETV ( '*' , 0 ) ;
 }
 RETV ( '*' , 1 ) ;
 break ;
 case CHR ( '+' ) : if ( ( v -> cflags & REG_ADVF ) && NEXT1 ( '?' ) ) {
 v -> now ++ ;
 NOTE ( REG_UNONPOSIX ) ;
 RETV ( '+' , 0 ) ;
 }
 RETV ( '+' , 1 ) ;
 break ;
 case CHR ( '?' ) : if ( ( v -> cflags & REG_ADVF ) && NEXT1 ( '?' ) ) {
 v -> now ++ ;
 NOTE ( REG_UNONPOSIX ) ;
 RETV ( '?' , 0 ) ;
 }
 RETV ( '?' , 1 ) ;
 break ;
 case CHR ( '{
' ) : if ( v -> cflags & REG_EXPANDED ) skip ( v ) ;
 if ( ATEOS ( ) || ! iscdigit ( * v -> now ) ) {
 NOTE ( REG_UBRACES ) ;
 NOTE ( REG_UUNSPEC ) ;
 RETV ( PLAIN , c ) ;
 }
 else {
 NOTE ( REG_UBOUNDS ) ;
 INTOCON ( L_EBND ) ;
 RET ( '{
' ) ;
 }
 assert ( NOTREACHED ) ;
 break ;
 case CHR ( '(' ) : if ( ( v -> cflags & REG_ADVF ) && NEXT1 ( '?' ) ) {
 NOTE ( REG_UNONPOSIX ) ;
 v -> now ++ ;
 if ( ATEOS ( ) ) FAILW ( REG_BADRPT ) ;
 switch ( * v -> now ++ ) {
 case CHR ( ':' ) : RETV ( '(' , 0 ) ;
 break ;
 case CHR ( '#' ) : while ( ! ATEOS ( ) && * v -> now != CHR ( ')' ) ) v -> now ++ ;
 if ( ! ATEOS ( ) ) v -> now ++ ;
 assert ( v -> nexttype == v -> lasttype ) ;
 return next ( v ) ;
 break ;
 case CHR ( '=' ) : NOTE ( REG_ULOOKAROUND ) ;
 RETV ( LACON , LATYPE_AHEAD_POS ) ;
 break ;
 case CHR ( '!' ) : NOTE ( REG_ULOOKAROUND ) ;
 RETV ( LACON , LATYPE_AHEAD_NEG ) ;
 break ;
 case CHR ( '<' ) : if ( ATEOS ( ) ) FAILW ( REG_BADRPT ) ;
 switch ( * v -> now ++ ) {
 case CHR ( '=' ) : NOTE ( REG_ULOOKAROUND ) ;
 RETV ( LACON , LATYPE_BEHIND_POS ) ;
 break ;
 case CHR ( '!' ) : NOTE ( REG_ULOOKAROUND ) ;
 RETV ( LACON , LATYPE_BEHIND_NEG ) ;
 break ;
 default : FAILW ( REG_BADRPT ) ;
 break ;
 }
 assert ( NOTREACHED ) ;
 break ;
 default : FAILW ( REG_BADRPT ) ;
 break ;
 }
 assert ( NOTREACHED ) ;
 }
 if ( v -> cflags & REG_NOSUB ) RETV ( '(' , 0 ) ;
 else RETV ( '(' , 1 ) ;
 break ;
 case CHR ( ')' ) : if ( LASTTYPE ( '(' ) ) NOTE ( REG_UUNSPEC ) ;
 RETV ( ')' , c ) ;
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
 case CHR ( '^' ) : RET ( '^' ) ;
 break ;
 case CHR ( '$' ) : RET ( '$' ) ;
 break ;
 case CHR ( '\\' ) : if ( ATEOS ( ) ) FAILW ( REG_EESCAPE ) ;
 break ;
 default : RETV ( PLAIN , c ) ;
 break ;
 }
 assert ( ! ATEOS ( ) ) ;
 if ( ! ( v -> cflags & REG_ADVF ) ) {
 if ( iscalnum ( * v -> now ) ) {
 NOTE ( REG_UBSALNUM ) ;
 NOTE ( REG_UUNSPEC ) ;
 }
 RETV ( PLAIN , * v -> now ++ ) ;
 }
 ( DISCARD ) lexescape ( v ) ;
 if ( ISERR ( ) ) FAILW ( REG_EESCAPE ) ;
 if ( v -> nexttype == CCLASS ) {
 switch ( v -> nextvalue ) {
 case 'd' : lexnest ( v , backd , ENDOF ( backd ) ) ;
 break ;
 case 'D' : lexnest ( v , backD , ENDOF ( backD ) ) ;
 break ;
 case 's' : lexnest ( v , backs , ENDOF ( backs ) ) ;
 break ;
 case 'S' : lexnest ( v , backS , ENDOF ( backS ) ) ;
 break ;
 case 'w' : lexnest ( v , backw , ENDOF ( backw ) ) ;
 break ;
 case 'W' : lexnest ( v , backW , ENDOF ( backW ) ) ;
 break ;
 default : assert ( NOTREACHED ) ;
 FAILW ( REG_ASSERT ) ;
 break ;
 }
 v -> nexttype = v -> lasttype ;
 return next ( v ) ;
 }
 return ! ISERR ( ) ;
 }