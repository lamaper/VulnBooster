inline int get_command_index ( char cmd_char ) {
 for ( uint i = 0 ;
 commands [ i ] . func ;
 i ++ ) if ( commands [ i ] . cmd_char == cmd_char ) return i ;
 return - 1 ;
 }