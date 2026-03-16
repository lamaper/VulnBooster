static void print_year ( UCalendar * c , UChar * days [ ] , UChar * months [ ] , UBool useLongNames , int32_t fdow , UErrorCode * status ) {
 int32_t width , pad , i , j ;
 int32_t lens [ DAY_COUNT ] ;
 UNumberFormat * nfmt ;
 UDateFormat * dfmt ;
 UChar s [ BUF_SIZE ] ;
 const UChar pat [ ] = {
 0x0079 , 0x0079 , 0x0079 , 0x0079 }
 ;
 int32_t len = 4 ;
 UCalendar * left_cal , * right_cal ;
 int32_t left_day , right_day ;
 int32_t left_firstday , right_firstday , left_current , right_current ;
 int32_t left_month , right_month ;
 if ( U_FAILURE ( * status ) ) return ;
 left_cal = c ;
 dfmt = udat_open ( UDAT_PATTERN , UDAT_PATTERN , NULL , NULL , 0 , pat , len , status ) ;
 udat_format ( dfmt , ucal_getMillis ( left_cal , status ) , s , BUF_SIZE , 0 , status ) ;
 get_days ( dfmt , days , useLongNames , fdow , status ) ;
 get_months ( dfmt , months , useLongNames , status ) ;
 width = 6 ;
 for ( i = 0 ;
 i < DAY_COUNT ;
 ++ i ) {
 lens [ i ] = u_strlen ( days [ i ] ) ;
 width += lens [ i ] ;
 }
 pad = 2 * width + MARGIN_WIDTH - u_strlen ( s ) ;
 indent ( pad / 2 , stdout ) ;
 uprint ( s , stdout , status ) ;
 putc ( '\n' , stdout ) ;
 putc ( '\n' , stdout ) ;
 right_cal = ucal_open ( 0 , - 1 , uloc_getDefault ( ) , UCAL_TRADITIONAL , status ) ;
 ucal_setMillis ( right_cal , ucal_getMillis ( left_cal , status ) , status ) ;
 nfmt = unum_open ( UNUM_DECIMAL , NULL , 0 , NULL , NULL , status ) ;
 for ( i = 0 ;
 i < MONTH_COUNT - 1 ;
 i += 2 ) {
 pad = width - u_strlen ( months [ i ] ) ;
 indent ( pad / 2 , stdout ) ;
 uprint ( months [ i ] , stdout , status ) ;
 indent ( pad / 2 + MARGIN_WIDTH , stdout ) ;
 pad = width - u_strlen ( months [ i + 1 ] ) ;
 indent ( pad / 2 , stdout ) ;
 uprint ( months [ i + 1 ] , stdout , status ) ;
 putc ( '\n' , stdout ) ;
 print_days ( days , stdout , status ) ;
 indent ( MARGIN_WIDTH , stdout ) ;
 print_days ( days , stdout , status ) ;
 putc ( '\n' , stdout ) ;
 ucal_set ( left_cal , UCAL_MONTH , i ) ;
 ucal_set ( left_cal , UCAL_DATE , 1 ) ;
 ucal_set ( right_cal , UCAL_MONTH , i + 1 ) ;
 ucal_set ( right_cal , UCAL_DATE , 1 ) ;
 left_firstday = ucal_get ( left_cal , UCAL_DAY_OF_WEEK , status ) ;
 right_firstday = ucal_get ( right_cal , UCAL_DAY_OF_WEEK , status ) ;
 left_firstday += ( DAY_COUNT - fdow ) ;
 left_firstday %= DAY_COUNT ;
 right_firstday += ( DAY_COUNT - fdow ) ;
 right_firstday %= DAY_COUNT ;
 left_current = left_firstday ;
 right_current = right_firstday ;
 left_day = ucal_get ( left_cal , UCAL_DATE , status ) ;
 right_day = ucal_get ( right_cal , UCAL_DATE , status ) ;
 left_month = ucal_get ( left_cal , UCAL_MONTH , status ) ;
 right_month = ucal_get ( right_cal , UCAL_MONTH , status ) ;
 while ( left_month == i || right_month == i + 1 ) {
 if ( left_month != i && right_month == i + 1 ) {
 indent ( width + 1 , stdout ) ;
 left_current = 0 ;
 }
 while ( left_month == i ) {
 if ( left_day == 1 ) {
 for ( j = 0 ;
 j < left_current ;
 ++ j ) indent ( lens [ j ] + 1 , stdout ) ;
 }
 unum_format ( nfmt , left_day , s , BUF_SIZE , 0 , status ) ;
 pad = lens [ left_current ] - u_strlen ( s ) ;
 indent ( pad , stdout ) ;
 uprint ( s , stdout , status ) ;
 putc ( ' ' , stdout ) ;
 ++ left_current ;
 left_current %= DAY_COUNT ;
 ucal_add ( left_cal , UCAL_DATE , 1 , status ) ;
 left_day = ucal_get ( left_cal , UCAL_DATE , status ) ;
 left_month = ucal_get ( left_cal , UCAL_MONTH , status ) ;
 if ( left_current == 0 ) {
 break ;
 }
 }
 ;
 if ( left_current != 0 ) {
 for ( j = left_current ;
 j < DAY_COUNT ;
 ++ j ) indent ( lens [ j ] + 1 , stdout ) ;
 }
 indent ( MARGIN_WIDTH , stdout ) ;
 while ( right_month == i + 1 ) {
 if ( right_day == 1 ) {
 for ( j = 0 ;
 j < right_current ;
 ++ j ) indent ( lens [ j ] + 1 , stdout ) ;
 }
 unum_format ( nfmt , right_day , s , BUF_SIZE , 0 , status ) ;
 pad = lens [ right_current ] - u_strlen ( s ) ;
 indent ( pad , stdout ) ;
 uprint ( s , stdout , status ) ;
 putc ( ' ' , stdout ) ;
 ++ right_current ;
 right_current %= DAY_COUNT ;
 ucal_add ( right_cal , UCAL_DATE , 1 , status ) ;
 right_day = ucal_get ( right_cal , UCAL_DATE , status ) ;
 right_month = ucal_get ( right_cal , UCAL_MONTH , status ) ;
 if ( right_current == 0 ) {
 break ;
 }
 }
 ;
 putc ( '\n' , stdout ) ;
 }
 putc ( '\n' , stdout ) ;
 }
 free_months ( months ) ;
 free_days ( days ) ;
 udat_close ( dfmt ) ;
 unum_close ( nfmt ) ;
 ucal_close ( right_cal ) ;
 }