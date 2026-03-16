static void get_months ( const UDateFormat * fmt , UChar * months [ ] , UBool useLongNames , UErrorCode * status ) {
 UDateFormatSymbolType monthType = ( useLongNames ? UDAT_MONTHS : UDAT_SHORT_MONTHS ) ;
 if ( U_FAILURE ( * status ) ) return ;
 get_symbols ( fmt , monthType , months , MONTH_COUNT - 1 , 0 , 0 , status ) ;
 }