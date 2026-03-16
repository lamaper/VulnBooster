static my_bool get_one_option ( int optid , const struct my_option * opt __attribute__ ( ( unused ) ) , char * argument ) {
 switch ( optid ) {
 case 'p' : if ( argument == disabled_my_option ) argument = ( char * ) "" ;
 if ( argument ) {
 char * start = argument ;
 my_free ( opt_password ) ;
 opt_password = my_strdup ( argument , MYF ( MY_FAE ) ) ;
 while ( * argument ) * argument ++ = 'x' ;
 if ( * start ) start [ 1 ] = 0 ;
 tty_password = 0 ;
 }
 else tty_password = 1 ;
 break ;
 case 'r' : if ( ! ( md_result_file = my_fopen ( argument , O_WRONLY | FILE_BINARY , MYF ( MY_WME ) ) ) ) exit ( 1 ) ;
 break ;
 case 'W' : # ifdef __WIN__ opt_protocol = MYSQL_PROTOCOL_PIPE ;

 case 'N' : opt_set_charset = 0 ;
 break ;
 case 'T' : opt_disable_keys = 0 ;
 if ( strlen ( argument ) >= FN_REFLEN ) {
 die ( EX_USAGE , "Input filename too long: %s" , argument ) ;
 }
 break ;
 case '#' : DBUG_PUSH ( argument ? argument : default_dbug_option ) ;
 debug_check_flag = 1 ;
 break ;

 exit ( 0 ) ;
 case 'X' : opt_xml = 1 ;
 extended_insert = opt_drop = opt_lock = opt_disable_keys = opt_autocommit = opt_create_db = 0 ;
 break ;
 case 'i' : opt_comments_used = 1 ;
 break ;
 case 'I' : case '?' : usage ( ) ;
 exit ( 0 ) ;
 case ( int ) OPT_MASTER_DATA : if ( ! argument ) opt_master_data = MYSQL_OPT_MASTER_DATA_EFFECTIVE_SQL ;
 break ;
 case ( int ) OPT_MYSQLDUMP_SLAVE_DATA : if ( ! argument ) opt_slave_data = MYSQL_OPT_SLAVE_DATA_EFFECTIVE_SQL ;
 break ;
 case ( int ) OPT_OPTIMIZE : extended_insert = opt_drop = opt_lock = quick = create_options = opt_disable_keys = lock_tables = opt_set_charset = 1 ;
 break ;
 case ( int ) OPT_SKIP_OPTIMIZATION : extended_insert = opt_drop = opt_lock = quick = create_options = opt_disable_keys = lock_tables = opt_set_charset = 0 ;
 break ;
 case ( int ) OPT_COMPACT : if ( opt_compact ) {
 opt_comments = opt_drop = opt_disable_keys = opt_lock = 0 ;
 opt_set_charset = 0 ;
 }
 break ;
 case ( int ) OPT_TABLES : opt_databases = 0 ;
 break ;
 case ( int ) OPT_IGNORE_TABLE : {
 if ( ! strchr ( argument , '.' ) ) {
 fprintf ( stderr , "Illegal use of option --ignore-table=<database>.<table>\n" ) ;
 exit ( 1 ) ;
 }
 if ( my_hash_insert ( & ignore_table , ( uchar * ) my_strdup ( argument , MYF ( 0 ) ) ) ) exit ( EX_EOM ) ;
 break ;
 }
 case ( int ) OPT_COMPATIBLE : {
 char buff [ 255 ] ;
 char * end = compatible_mode_normal_str ;
 int i ;
 ulong mode ;
 uint err_len ;
 opt_quoted = 1 ;
 opt_set_charset = 0 ;
 opt_compatible_mode_str = argument ;
 opt_compatible_mode = find_set ( & compatible_mode_typelib , argument , strlen ( argument ) , & err_ptr , & err_len ) ;
 if ( err_len ) {
 strmake ( buff , err_ptr , min ( sizeof ( buff ) - 1 , err_len ) ) ;
 fprintf ( stderr , "Invalid mode to --compatible: %s\n" , buff ) ;
 exit ( 1 ) ;
 }

 size_t size_for_sql_mode = 0 ;
 const char * * ptr ;
 for ( ptr = compatible_mode_names ;
 * ptr ;
 ptr ++ ) size_for_sql_mode += strlen ( * ptr ) ;
 size_for_sql_mode += sizeof ( compatible_mode_names ) - 1 ;
 DBUG_ASSERT ( sizeof ( compatible_mode_normal_str ) >= size_for_sql_mode ) ;
 }

 for ( i = 0 , mode = opt_compatible_mode ;
 mode ;
 mode >>= 1 , i ++ ) {
 if ( mode & 1 ) {
 end = strmov ( end , compatible_mode_names [ i ] ) ;
 end = strmov ( end , "," ) ;
 }
 }
 if ( end != compatible_mode_normal_str ) end [ - 1 ] = 0 ;
 if ( default_charset == mysql_universal_client_charset ) default_charset = ( char * ) MYSQL_DEFAULT_CHARSET_NAME ;
 break ;
 }
 case ( int ) OPT_MYSQL_PROTOCOL : opt_protocol = find_type_or_exit ( argument , & sql_protocol_typelib , opt -> name ) ;
 break ;
 }
 return 0 ;
 }