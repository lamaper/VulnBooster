static void print_month ( UCalendar * c , UChar * days [ ] , UBool useLongNames , int32_t fdow , UErrorCode * status ) {
 int32_t width , pad , i , day ;
 int32_t lens [ DAY_COUNT ] ;
 int32_t firstday , current ;
 UNumberFormat * nfmt ;
 UDateFormat * dfmt ;
 UChar s [ BUF_SIZE ] ;
 const UChar * pat = ( useLongNames ? sLongPat : sShortPat ) ;
 int32_t len = ( useLongNames ? 9 : 8 ) ;
 if ( U_FAILURE ( * status ) ) return ;
 dfmt = udat_open ( UDAT_PATTERN , UDAT_PATTERN , NULL , NULL , 0 , pat , len , status ) ;
 udat_format ( dfmt , ucal_getMillis ( c , status ) , s , BUF_SIZE , 0 , status ) ;
 get_days ( dfmt , days , useLongNames , fdow , status ) ;
 width = 6 ;
 for ( i = 0 ;
 i < DAY_COUNT ;
 ++ i ) {
 lens [ i ] = u_strlen ( days [ i ] ) ;
 width += lens [ i ] ;
 }
 pad = width - u_strlen ( s ) ;
 indent ( pad / 2 , stdout ) ;
 uprint ( s , stdout , status ) ;
 putc ( '\n' , stdout ) ;
 print_days ( days , stdout , status ) ;
 putc ( '\n' , stdout ) ;
 ucal_set ( c , UCAL_DATE , 1 ) ;
 firstday = ucal_get ( c , UCAL_DAY_OF_WEEK , status ) ;
 firstday -= fdow ;
 nfmt = unum_open ( UNUM_DECIMAL , NULL , 0 , NULL , NULL , status ) ;
 current = firstday ;
 if ( current < 0 ) {
 current += 7 ;
 }
 for ( i = 0 ;
 i < current ;
 ++ i ) indent ( lens [ i ] + 1 , stdout ) ;
 day = ucal_get ( c , UCAL_DATE , status ) ;
 do {
 unum_format ( nfmt , day , s , BUF_SIZE , 0 , status ) ;
 pad = lens [ current ] - u_strlen ( s ) ;
 indent ( pad , stdout ) ;
 uprint ( s , stdout , status ) ;
 putc ( ' ' , stdout ) ;
 ++ current ;
 current %= DAY_COUNT ;
 if ( current == 0 ) {
 putc ( '\n' , stdout ) ;
 }
 ucal_add ( c , UCAL_DATE , 1 , status ) ;
 day = ucal_get ( c , UCAL_DATE , status ) ;
 }
 while ( day != 1 ) ;
 putc ( '\n' , stdout ) ;
 free_days ( days ) ;
 unum_close ( nfmt ) ;
 udat_close ( dfmt ) ;
 }