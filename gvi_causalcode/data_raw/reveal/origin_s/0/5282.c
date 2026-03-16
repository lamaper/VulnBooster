inline static uint32 adjust_max_effective_column_length ( Field * field_par , uint32 max_length ) {
 uint32 new_max_length = field_par -> max_display_length ( ) ;
 uint32 sign_length = ( field_par -> flags & UNSIGNED_FLAG ) ? 0 : 1 ;
 switch ( field_par -> type ( ) ) {
 case MYSQL_TYPE_INT24 : new_max_length += 1 ;
 case MYSQL_TYPE_LONG : case MYSQL_TYPE_TINY : case MYSQL_TYPE_SHORT : new_max_length = new_max_length - 1 + sign_length ;
 break ;
 case MYSQL_TYPE_LONGLONG : default : break ;
 }
 return new_max_length > max_length ? new_max_length : max_length ;
 }