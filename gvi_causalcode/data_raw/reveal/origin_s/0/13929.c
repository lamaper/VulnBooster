int chk_status ( MI_CHECK * param , register MI_INFO * info ) {
 MYISAM_SHARE * share = info -> s ;
 if ( mi_is_crashed_on_repair ( info ) ) mi_check_print_warning ( param , "Table is marked as crashed and last repair failed" ) ;
 else if ( mi_is_crashed ( info ) ) mi_check_print_warning ( param , "Table is marked as crashed" ) ;
 if ( share -> state . open_count != ( uint ) ( info -> s -> global_changed ? 1 : 0 ) ) {
 uint save = param -> warning_printed ;
 mi_check_print_warning ( param , share -> state . open_count == 1 ? "%d client is using or hasn't closed the table properly" : "%d clients are using or haven't closed the table properly" , share -> state . open_count ) ;
 if ( param -> testflag & T_UPDATE_STATE ) param -> warning_printed = save ;
 }
 return 0 ;
 }