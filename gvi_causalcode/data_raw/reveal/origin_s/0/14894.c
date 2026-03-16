static my_bool get_one_option ( int optid , const struct my_option * opt __attribute__ ( ( unused ) ) , char * argument ) {
 switch ( optid ) {
 case 'a' : if ( argument == disabled_my_option ) check_param . testflag &= ~ T_STATISTICS ;
 else check_param . testflag |= T_STATISTICS ;
 break ;
 case 'A' : if ( argument ) check_param . auto_increment_value = strtoull ( argument , NULL , 0 ) ;
 else check_param . auto_increment_value = 0 ;
 check_param . testflag |= T_AUTO_INC ;
 break ;
 case 'b' : check_param . search_after_block = strtoul ( argument , NULL , 10 ) ;
 break ;
 case 'B' : if ( argument == disabled_my_option ) check_param . testflag &= ~ T_BACKUP_DATA ;
 else check_param . testflag |= T_BACKUP_DATA ;
 break ;
 case 'c' : if ( argument == disabled_my_option ) check_param . testflag &= ~ T_CHECK ;
 else check_param . testflag |= T_CHECK ;
 break ;
 case 'C' : if ( argument == disabled_my_option ) check_param . testflag &= ~ ( T_CHECK | T_CHECK_ONLY_CHANGED ) ;
 else check_param . testflag |= T_CHECK | T_CHECK_ONLY_CHANGED ;
 break ;
 case 'D' : check_param . max_data_file_length = strtoll ( argument , NULL , 10 ) ;
 break ;
 case 's' : if ( argument == disabled_my_option ) check_param . testflag &= ~ ( T_SILENT | T_VERY_SILENT ) ;
 else {
 if ( check_param . testflag & T_SILENT ) check_param . testflag |= T_VERY_SILENT ;
 check_param . testflag |= T_SILENT ;
 check_param . testflag &= ~ T_WRITE_LOOP ;
 }
 break ;
 case 'w' : if ( argument == disabled_my_option ) check_param . testflag &= ~ T_WAIT_FOREVER ;
 else check_param . testflag |= T_WAIT_FOREVER ;
 break ;
 case 'd' : if ( argument == disabled_my_option ) check_param . testflag &= ~ T_DESCRIPT ;
 else check_param . testflag |= T_DESCRIPT ;
 break ;
 case 'e' : if ( argument == disabled_my_option ) check_param . testflag &= ~ T_EXTEND ;
 else check_param . testflag |= T_EXTEND ;
 break ;
 case 'i' : if ( argument == disabled_my_option ) check_param . testflag &= ~ T_INFO ;
 else check_param . testflag |= T_INFO ;
 break ;
 case 'f' : if ( argument == disabled_my_option ) {
 check_param . tmpfile_createflag = O_RDWR | O_TRUNC | O_EXCL ;
 check_param . testflag &= ~ ( T_FORCE_CREATE | T_UPDATE_STATE ) ;
 }
 else {
 check_param . tmpfile_createflag = O_RDWR | O_TRUNC ;
 check_param . testflag |= T_FORCE_CREATE | T_UPDATE_STATE ;
 }
 break ;
 case 'F' : if ( argument == disabled_my_option ) check_param . testflag &= ~ T_FAST ;
 else check_param . testflag |= T_FAST ;
 break ;
 case 'k' : check_param . keys_in_use = ( ulonglong ) strtoll ( argument , NULL , 10 ) ;
 break ;
 case 'm' : if ( argument == disabled_my_option ) check_param . testflag &= ~ T_MEDIUM ;
 else check_param . testflag |= T_MEDIUM ;
 break ;
 case 'r' : check_param . testflag &= ~ T_REP_ANY ;
 if ( argument != disabled_my_option ) check_param . testflag |= T_REP_BY_SORT ;
 break ;
 case 'p' : check_param . testflag &= ~ T_REP_ANY ;
 if ( argument != disabled_my_option ) check_param . testflag |= T_REP_PARALLEL ;
 break ;
 case 'o' : check_param . testflag &= ~ T_REP_ANY ;
 check_param . force_sort = 0 ;
 if ( argument != disabled_my_option ) {
 check_param . testflag |= T_REP ;
 my_disable_async_io = 1 ;
 }
 break ;
 case 'n' : check_param . testflag &= ~ T_REP_ANY ;
 if ( argument == disabled_my_option ) check_param . force_sort = 0 ;
 else {
 check_param . testflag |= T_REP_BY_SORT ;
 check_param . force_sort = 1 ;
 }
 break ;
 case 'q' : if ( argument == disabled_my_option ) check_param . testflag &= ~ ( T_QUICK | T_FORCE_UNIQUENESS ) ;
 else check_param . testflag |= ( check_param . testflag & T_QUICK ) ? T_FORCE_UNIQUENESS : T_QUICK ;
 break ;
 case 'u' : if ( argument == disabled_my_option ) check_param . testflag &= ~ ( T_UNPACK | T_REP_BY_SORT ) ;
 else check_param . testflag |= T_UNPACK | T_REP_BY_SORT ;
 break ;
 case 'v' : if ( argument == disabled_my_option ) {
 check_param . testflag &= ~ T_VERBOSE ;
 check_param . verbose = 0 ;
 }
 else {
 check_param . testflag |= T_VERBOSE ;
 check_param . verbose ++ ;
 }
 break ;
 case 'R' : if ( argument == disabled_my_option ) check_param . testflag &= ~ T_SORT_RECORDS ;
 else {
 check_param . testflag |= T_SORT_RECORDS ;
 check_param . opt_sort_key = ( uint ) atoi ( argument ) - 1 ;
 if ( check_param . opt_sort_key >= MI_MAX_KEY ) {
 fprintf ( stderr , "The value of the sort key is bigger than max key: %d.\n" , MI_MAX_KEY ) ;
 exit ( 1 ) ;
 }
 }
 break ;
 case 'S' : if ( argument == disabled_my_option ) check_param . testflag &= ~ T_SORT_INDEX ;
 else check_param . testflag |= T_SORT_INDEX ;
 break ;
 case 'T' : if ( argument == disabled_my_option ) check_param . testflag &= ~ T_READONLY ;
 else check_param . testflag |= T_READONLY ;
 break ;
 case 'U' : if ( argument == disabled_my_option ) check_param . testflag &= ~ T_UPDATE_STATE ;
 else check_param . testflag |= T_UPDATE_STATE ;
 break ;
 case '#' : if ( argument == disabled_my_option ) {
 DBUG_POP ( ) ;
 }
 else {
 DBUG_PUSH ( argument ? argument : "d:t:o,/tmp/myisamchk.trace" ) ;
 }
 break ;
 case 'V' : print_version ( ) ;
 exit ( 0 ) ;
 case OPT_CORRECT_CHECKSUM : if ( argument == disabled_my_option ) check_param . testflag &= ~ T_CALC_CHECKSUM ;
 else check_param . testflag |= T_CALC_CHECKSUM ;
 break ;
 case OPT_STATS_METHOD : {
 int method ;
 enum_mi_stats_method UNINIT_VAR ( method_conv ) ;
 myisam_stats_method_str = argument ;
 if ( ( method = find_type ( argument , & myisam_stats_method_typelib , FIND_TYPE_BASIC ) ) <= 0 ) {
 fprintf ( stderr , "Invalid value of stats_method: %s.\n" , argument ) ;
 exit ( 1 ) ;
 }
 switch ( method - 1 ) {
 case 0 : method_conv = MI_STATS_METHOD_NULLS_EQUAL ;
 break ;
 case 1 : method_conv = MI_STATS_METHOD_NULLS_NOT_EQUAL ;
 break ;
 case 2 : method_conv = MI_STATS_METHOD_IGNORE_NULLS ;
 break ;
 default : assert ( 0 ) ;
 }
 check_param . stats_method = method_conv ;
 break ;
 }

 break ;

 exit ( 0 ) ;
 case '?' : usage ( ) ;
 exit ( 0 ) ;
 }
 return 0 ;
 }