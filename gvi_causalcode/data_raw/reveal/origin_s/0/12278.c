static void print_days ( UChar * days [ ] , FILE * f , UErrorCode * status ) {
 int32_t i ;
 if ( U_FAILURE ( * status ) ) return ;
 for ( i = 0 ;
 i < DAY_COUNT ;
 ++ i ) {
 uprint ( days [ i ] , f , status ) ;
 putc ( ' ' , f ) ;
 }
 }