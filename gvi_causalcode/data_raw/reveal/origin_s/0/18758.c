static void prefixes ( struct vars * v ) {
 if ( v -> cflags & REG_QUOTE ) return ;
 if ( HAVE ( 4 ) && NEXT3 ( '*' , '*' , '*' ) ) switch ( * ( v -> now + 3 ) ) {
 case CHR ( '?' ) : ERR ( REG_BADPAT ) ;
 return ;
 break ;
 case CHR ( '=' ) : NOTE ( REG_UNONPOSIX ) ;
 v -> cflags |= REG_QUOTE ;
 v -> cflags &= ~ ( REG_ADVANCED | REG_EXPANDED | REG_NEWLINE ) ;
 v -> now += 4 ;
 return ;
 break ;
 case CHR ( ':' ) : NOTE ( REG_UNONPOSIX ) ;
 v -> cflags |= REG_ADVANCED ;
 v -> now += 4 ;
 break ;
 default : ERR ( REG_BADRPT ) ;
 return ;
 break ;
 }
 if ( ( v -> cflags & REG_ADVANCED ) != REG_ADVANCED ) return ;
 if ( HAVE ( 3 ) && NEXT2 ( '(' , '?' ) && iscalpha ( * ( v -> now + 2 ) ) ) {
 NOTE ( REG_UNONPOSIX ) ;
 v -> now += 2 ;
 for ( ;
 ! ATEOS ( ) && iscalpha ( * v -> now ) ;
 v -> now ++ ) switch ( * v -> now ) {
 case CHR ( 'b' ) : v -> cflags &= ~ ( REG_ADVANCED | REG_QUOTE ) ;
 break ;
 case CHR ( 'c' ) : v -> cflags &= ~ REG_ICASE ;
 break ;
 case CHR ( 'e' ) : v -> cflags |= REG_EXTENDED ;
 v -> cflags &= ~ ( REG_ADVF | REG_QUOTE ) ;
 break ;
 case CHR ( 'i' ) : v -> cflags |= REG_ICASE ;
 break ;
 case CHR ( 'm' ) : case CHR ( 'n' ) : v -> cflags |= REG_NEWLINE ;
 break ;
 case CHR ( 'p' ) : v -> cflags |= REG_NLSTOP ;
 v -> cflags &= ~ REG_NLANCH ;
 break ;
 case CHR ( 'q' ) : v -> cflags |= REG_QUOTE ;
 v -> cflags &= ~ REG_ADVANCED ;
 break ;
 case CHR ( 's' ) : v -> cflags &= ~ REG_NEWLINE ;
 break ;
 case CHR ( 't' ) : v -> cflags &= ~ REG_EXPANDED ;
 break ;
 case CHR ( 'w' ) : v -> cflags &= ~ REG_NLSTOP ;
 v -> cflags |= REG_NLANCH ;
 break ;
 case CHR ( 'x' ) : v -> cflags |= REG_EXPANDED ;
 break ;
 default : ERR ( REG_BADOPT ) ;
 return ;
 }
 if ( ! NEXT1 ( ')' ) ) {
 ERR ( REG_BADOPT ) ;
 return ;
 }
 v -> now ++ ;
 if ( v -> cflags & REG_QUOTE ) v -> cflags &= ~ ( REG_EXPANDED | REG_NEWLINE ) ;
 }
 }