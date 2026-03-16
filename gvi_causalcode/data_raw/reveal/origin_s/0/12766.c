static void curses_destroy_conndata ( void ) {
 conntrack_hook_conn_del ( curr_conn , split_print_po ) ;
 conntrack_hook_conn_del ( curr_conn , join_print_po ) ;
 wdg_conndata = NULL ;
 wdg_c1 = NULL ;
 wdg_c2 = NULL ;
 wdg_join = NULL ;
 curr_conn -> flags &= ~ CONN_VIEWING ;
 curr_conn = NULL ;
 }