const char * TSMimeFieldValueGet ( TSMBuffer , TSMLoc field_obj , int idx , int * value_len_ptr ) {
 MIMEFieldSDKHandle * handle = ( MIMEFieldSDKHandle * ) field_obj ;
 if ( idx >= 0 ) {
 return mime_field_value_get_comma_val ( handle -> field_ptr , value_len_ptr , idx ) ;
 }
 else {
 return mime_field_value_get ( handle -> field_ptr , value_len_ptr ) ;
 }
 }