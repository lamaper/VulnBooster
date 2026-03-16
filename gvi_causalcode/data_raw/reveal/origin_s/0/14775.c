void do_get_errcodes ( struct st_command * command ) {
 struct st_match_err * to = saved_expected_errors . err ;
 DBUG_ENTER ( "do_get_errcodes" ) ;
 if ( ! * command -> first_argument ) die ( "Missing argument(s) to 'error'" ) ;
 DYNAMIC_STRING ds ;
 init_dynamic_string ( & ds , 0 , command -> query_len + 64 , 256 ) ;
 do_eval ( & ds , command -> first_argument , command -> end , ! is_windows ) ;
 char * p = ds . str ;
 uint count = 0 ;
 char * next ;
 do {
 char * end ;
 while ( * p && * p == ' ' ) p ++ ;
 end = p ;
 while ( * end && * end != ',' && * end != ' ' ) end ++ ;
 next = end ;
 if ( * p == '$' ) {
 const char * fin ;
 VAR * var = var_get ( p , & fin , 0 , 0 ) ;
 p = var -> str_val ;
 end = p + var -> str_val_len ;
 }
 if ( * p == 'S' ) {
 char * to_ptr = to -> code . sqlstate ;
 p ++ ;
 if ( ( end - p ) != SQLSTATE_LENGTH ) die ( "The sqlstate must be exactly %d chars long" , SQLSTATE_LENGTH ) ;
 while ( * p && p < end ) {
 if ( my_isdigit ( charset_info , * p ) || my_isupper ( charset_info , * p ) ) * to_ptr ++ = * p ++ ;
 else die ( "The sqlstate may only consist of digits[0-9] " "and _uppercase_ letters" ) ;
 }
 * to_ptr = 0 ;
 to -> type = ERR_SQLSTATE ;
 DBUG_PRINT ( "info" , ( "ERR_SQLSTATE: %s" , to -> code . sqlstate ) ) ;
 }
 else if ( * p == 's' ) {
 die ( "The sqlstate definition must start with an uppercase S" ) ;
 }
 else if ( * p == 'E' || * p == 'H' ) {
 DBUG_PRINT ( "info" , ( "Error name: %s" , p ) ) ;
 to -> code . errnum = get_errcode_from_name ( p , end ) ;
 to -> type = ERR_ERRNO ;
 DBUG_PRINT ( "info" , ( "ERR_ERRNO: %d" , to -> code . errnum ) ) ;
 }
 else if ( * p == 'e' || * p == 'h' ) {
 die ( "The error name definition must start with an uppercase E or H" ) ;
 }
 else {
 long val ;
 char * start = p ;
 while ( * p && p != end ) {
 if ( ! my_isdigit ( charset_info , * p ) ) die ( "Invalid argument to error: '%s' - " "the errno may only consist of digits[0-9]" , command -> first_argument ) ;
 p ++ ;
 }
 if ( ! str2int ( start , 10 , ( long ) INT_MIN , ( long ) INT_MAX , & val ) ) die ( "Invalid argument to error: '%s'" , command -> first_argument ) ;
 to -> code . errnum = ( uint ) val ;
 to -> type = ERR_ERRNO ;
 DBUG_PRINT ( "info" , ( "ERR_ERRNO: %d" , to -> code . errnum ) ) ;
 }
 to ++ ;
 count ++ ;
 if ( count >= ( sizeof ( saved_expected_errors . err ) / sizeof ( struct st_match_err ) ) ) die ( "Too many errorcodes specified" ) ;
 p = next ;
 while ( * p && * p != ',' ) p ++ ;
 if ( * p ) p ++ ;
 }
 while ( * p ) ;
 command -> last_argument = command -> first_argument ;
 while ( * command -> last_argument ) command -> last_argument ++ ;
 to -> type = ERR_EMPTY ;
 DBUG_PRINT ( "info" , ( "Expected errors: %d" , count ) ) ;
 saved_expected_errors . count = count ;
 dynstr_free ( & ds ) ;
 DBUG_VOID_RETURN ;
 }