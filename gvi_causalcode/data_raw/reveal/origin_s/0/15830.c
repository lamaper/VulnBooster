static bool have_changed_settings ( const struct config_filter_parser * parser , const char * const * modules ) {
 const unsigned char * changes ;
 unsigned int i , j , size ;
 for ( i = 0 ;
 parser -> parsers [ i ] . root != NULL ;
 i ++ ) {
 if ( ! config_module_want_parser ( config_module_parsers , modules , parser -> parsers [ i ] . root ) ) continue ;
 changes = settings_parser_get_changes ( parser -> parsers [ i ] . parser ) ;
 size = parser -> parsers [ i ] . root -> struct_size ;
 for ( j = 0 ;
 j < size ;
 j ++ ) {
 if ( changes [ j ] != 0 ) return TRUE ;
 }
 }
 return FALSE ;
 }