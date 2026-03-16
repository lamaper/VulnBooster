void TSDebug ( const char * tag , const char * format_str , ... ) {
 if ( is_debug_tag_set ( tag ) ) {
 va_list ap ;
 va_start ( ap , format_str ) ;
 diags -> print_va ( tag , DL_Diag , nullptr , format_str , ap ) ;
 va_end ( ap ) ;
 }
 }