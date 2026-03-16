static int32_t u_scanf_parse_spec ( const UChar * fmt , u_scanf_spec * spec ) {
 const UChar * s = fmt ;
 const UChar * backup ;
 u_scanf_spec_info * info = & ( spec -> fInfo ) ;
 spec -> fArgPos = - 1 ;
 info -> fWidth = - 1 ;
 info -> fSpec = 0x0000 ;
 info -> fPadChar = 0x0020 ;
 info -> fSkipArg = FALSE ;
 info -> fIsLongDouble = FALSE ;
 info -> fIsShort = FALSE ;
 info -> fIsLong = FALSE ;
 info -> fIsLongLong = FALSE ;
 info -> fIsString = TRUE ;
 s ++ ;
 if ( ISDIGIT ( * s ) ) {
 backup = s ;
 if ( ISDIGIT ( * s ) ) {
 spec -> fArgPos = ( int ) ( * s ++ - DIGIT_ZERO ) ;
 while ( ISDIGIT ( * s ) ) {
 spec -> fArgPos *= 10 ;
 spec -> fArgPos += ( int ) ( * s ++ - DIGIT_ZERO ) ;
 }
 }
 if ( * s != SPEC_DOLLARSIGN ) {
 spec -> fArgPos = - 1 ;
 s = backup ;
 }
 else s ++ ;
 }
 while ( ISFLAG ( * s ) ) {
 switch ( * s ++ ) {
 case FLAG_ASTERISK : info -> fSkipArg = TRUE ;
 break ;
 case FLAG_PAREN : info -> fPadChar = ( UChar ) ufmt_digitvalue ( * s ++ ) ;
 info -> fPadChar = ( UChar ) ( ( info -> fPadChar * 16 ) + ufmt_digitvalue ( * s ++ ) ) ;
 info -> fPadChar = ( UChar ) ( ( info -> fPadChar * 16 ) + ufmt_digitvalue ( * s ++ ) ) ;
 info -> fPadChar = ( UChar ) ( ( info -> fPadChar * 16 ) + ufmt_digitvalue ( * s ++ ) ) ;
 s ++ ;
 break ;
 }
 }
 if ( ISDIGIT ( * s ) ) {
 info -> fWidth = ( int ) ( * s ++ - DIGIT_ZERO ) ;
 while ( ISDIGIT ( * s ) ) {
 info -> fWidth *= 10 ;
 info -> fWidth += ( int ) ( * s ++ - DIGIT_ZERO ) ;
 }
 }
 if ( ISMOD ( * s ) ) {
 switch ( * s ++ ) {
 case MOD_H : info -> fIsShort = TRUE ;
 break ;
 case MOD_LOWERL : if ( * s == MOD_LOWERL ) {
 info -> fIsLongLong = TRUE ;
 s ++ ;
 }
 else info -> fIsLong = TRUE ;
 break ;
 case MOD_L : info -> fIsLongDouble = TRUE ;
 break ;
 }
 }
 info -> fSpec = * s ++ ;
 return ( int32_t ) ( s - fmt ) ;
 }