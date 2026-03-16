void get_command_type ( struct st_command * command ) {
 char save ;
 uint type ;
 DBUG_ENTER ( "get_command_type" ) ;
 if ( * command -> query == '}
' ) {
 command -> type = Q_END_BLOCK ;
 DBUG_VOID_RETURN ;
 }
 save = command -> query [ command -> first_word_len ] ;
 command -> query [ command -> first_word_len ] = 0 ;
 type = find_type ( command -> query , & command_typelib , FIND_TYPE_NO_PREFIX ) ;
 command -> query [ command -> first_word_len ] = save ;
 if ( type > 0 ) {
 command -> type = ( enum enum_commands ) type ;
 if ( type == Q_QUERY ) {
 command -> query = command -> first_argument ;
 }
 }
 else {
 if ( command -> type != Q_COMMENT_WITH_COMMAND ) {
 command -> type = Q_QUERY ;
 }
 else {
 report_or_die ( "Found line beginning with -- that didn't contain " "a valid mysqltest command, check your syntax or " "use # if you intended to write a comment" ) ;
 command -> type = Q_COMMENT ;
 }
 }
 memcpy ( & command -> expected_errors , & saved_expected_errors , sizeof ( saved_expected_errors ) ) ;
 DBUG_PRINT ( "info" , ( "There are %d expected errors" , command -> expected_errors . count ) ) ;
 DBUG_VOID_RETURN ;
 }