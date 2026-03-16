static void curses_connection_data_help ( void ) {
 char help [ ] = "HELP: shortcut list:\n\n" " ARROWS - switch between panels\n" " j - switch from split to joined view\n" " y - inject characters interactively\n" " Y - inject characters from a file\n" " k - kill the connection" ;
 curses_message ( help ) ;
 }