static void cal ( int32_t month , int32_t year , UBool useLongNames , UErrorCode * status ) {
 UCalendar * c ;
 UChar * days [ DAY_COUNT ] ;
 UChar * months [ MONTH_COUNT ] ;
 int32_t fdow ;
 if ( U_FAILURE ( * status ) ) return ;
 c = ucal_open ( 0 , - 1 , uloc_getDefault ( ) , UCAL_TRADITIONAL , status ) ;
 if ( month == - 1 && year != - 1 ) {
 ucal_set ( c , UCAL_YEAR , year ) ;
 fdow = ucal_getAttribute ( c , UCAL_FIRST_DAY_OF_WEEK ) ;
 print_year ( c , days , months , useLongNames , fdow , status ) ;
 }
 else {
 if ( month != - 1 ) ucal_set ( c , UCAL_MONTH , month ) ;
 if ( year != - 1 ) ucal_set ( c , UCAL_YEAR , year ) ;
 fdow = ucal_getAttribute ( c , UCAL_FIRST_DAY_OF_WEEK ) ;
 print_month ( c , days , useLongNames , fdow , status ) ;
 }
 ucal_close ( c ) ;
 }