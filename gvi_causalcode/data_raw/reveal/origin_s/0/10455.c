void TSDebugSpecific ( int debug_flag , const char * tag , const char * format_str , ... ) {
 if ( is_debug_tag_set ( tag ) || ( debug_flag && diags -> on ( ) ) ) {
 va_list ap ;
 va_start ( ap , format_str ) ;
 diags -> print_va ( tag , DL_Diag , nullptr , format_str , ap ) ;
 va_end ( ap ) ;
 }
 }