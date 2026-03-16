static void curses_kill_connections ( void ) {
 DEBUG_MSG ( "curses_kill_connections" ) ;
 wdg_del_idle_callback ( refresh_connections ) ;
 wdg_connections = NULL ;
 }