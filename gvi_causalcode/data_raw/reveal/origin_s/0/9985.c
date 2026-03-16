static COMMANDS * find_command ( char cmd_char ) {
 DBUG_ENTER ( "find_command" ) ;
 DBUG_PRINT ( "enter" , ( "cmd_char: %d" , cmd_char ) ) ;
 int index = - 1 ;
 if ( real_binary_mode ) {
 if ( cmd_char == 'C' ) index = charset_index ;
 }
 else index = get_command_index ( cmd_char ) ;
 if ( index >= 0 ) {
 DBUG_PRINT ( "exit" , ( "found command: %s" , commands [ index ] . name ) ) ;
 DBUG_RETURN ( & commands [ index ] ) ;
 }
 else DBUG_RETURN ( ( COMMANDS * ) 0 ) ;
 }