static void get_days ( const UDateFormat * fmt , UChar * days [ ] , UBool useLongNames , int32_t fdow , UErrorCode * status ) {
 UDateFormatSymbolType dayType = ( useLongNames ? UDAT_WEEKDAYS : UDAT_SHORT_WEEKDAYS ) ;
 if ( U_FAILURE ( * status ) ) return ;
 -- fdow ;
 get_symbols ( fmt , dayType , days , DAY_COUNT , 1 , fdow , status ) ;
 }