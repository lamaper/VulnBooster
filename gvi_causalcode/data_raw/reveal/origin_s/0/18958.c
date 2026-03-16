static bool mimefield_value_equal ( MIMEField * field , const char * value , const int value_len ) {
 int field_value_len = 0 ;
 const char * field_value = field -> value_get ( & field_value_len ) ;
 if ( field_value != nullptr && field_value_len == value_len ) {
 return ! strncasecmp ( field_value , value , value_len ) ;
 }
 return false ;
 }