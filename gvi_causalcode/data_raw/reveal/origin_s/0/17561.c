static void curses_connection_data_join ( void ) {
 char src [ MAX_ASCII_ADDR_LEN ] ;
 char dst [ MAX_ASCII_ADDR_LEN ] ;
 char title [ 64 ] ;
 DEBUG_MSG ( "curses_connection_data_join" ) ;
 if ( wdg_conndata ) {
 struct conn_object * tmp_conn = curr_conn ;
 wdg_destroy_object ( & wdg_conndata ) ;
 curses_destroy_conndata ( ) ;
 curr_conn = tmp_conn ;
 }
 curr_conn -> flags |= CONN_VIEWING ;
 wdg_create_object ( & wdg_conndata , WDG_COMPOUND , WDG_OBJ_WANT_FOCUS ) ;
 wdg_set_color ( wdg_conndata , WDG_COLOR_SCREEN , EC_COLOR ) ;
 wdg_set_color ( wdg_conndata , WDG_COLOR_WINDOW , EC_COLOR ) ;
 wdg_set_color ( wdg_conndata , WDG_COLOR_FOCUS , EC_COLOR_FOCUS ) ;
 wdg_set_color ( wdg_conndata , WDG_COLOR_TITLE , EC_COLOR_TITLE ) ;
 wdg_set_title ( wdg_conndata , "Connection data" , WDG_ALIGN_LEFT ) ;
 wdg_set_size ( wdg_conndata , 1 , 2 , - 1 , SYSMSG_WIN_SIZE - 1 ) ;
 wdg_create_object ( & wdg_join , WDG_SCROLL , 0 ) ;
 snprintf ( title , 64 , "%s:%d - %s:%d" , ip_addr_ntoa ( & curr_conn -> L3_addr1 , src ) , ntohs ( curr_conn -> L4_addr1 ) , ip_addr_ntoa ( & curr_conn -> L3_addr2 , dst ) , ntohs ( curr_conn -> L4_addr2 ) ) ;
 wdg_set_title ( wdg_join , title , WDG_ALIGN_LEFT ) ;
 wdg_set_color ( wdg_join , WDG_COLOR_TITLE , EC_COLOR_TITLE ) ;
 wdg_set_color ( wdg_join , WDG_COLOR_FOCUS , EC_COLOR_FOCUS ) ;
 wdg_set_size ( wdg_join , 2 , 3 , - 2 , SYSMSG_WIN_SIZE - 2 ) ;
 wdg_scroll_set_lines ( wdg_join , GBL_CONF -> connection_buffer / ( current_screen . cols / 2 ) ) ;
 wdg_compound_add ( wdg_conndata , wdg_join ) ;
 wdg_add_destroy_key ( wdg_conndata , CTRL ( 'Q' ) , curses_destroy_conndata ) ;
 wdg_compound_add_callback ( wdg_conndata , 'j' , curses_connection_data_split ) ;
 wdg_compound_add_callback ( wdg_conndata , 'k' , curses_connection_kill_wrapper ) ;
 wdg_compound_add_callback ( wdg_conndata , ' ' , curses_connection_data_help ) ;
 wdg_draw_object ( wdg_conndata ) ;
 wdg_set_focus ( wdg_conndata ) ;
 connbuf_print ( & curr_conn -> data , join_print ) ;
 conntrack_hook_conn_add ( curr_conn , join_print_po ) ;
 }