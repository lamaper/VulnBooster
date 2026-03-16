int main ( int argc , char * argv [ ] ) {
 char buff [ 80 ] ;
 MY_INIT ( argv [ 0 ] ) ;
 DBUG_ENTER ( "main" ) ;
 DBUG_PROCESS ( argv [ 0 ] ) ;
 charset_index = get_command_index ( 'C' ) ;
 delimiter_index = get_command_index ( 'd' ) ;
 delimiter_str = delimiter ;
 default_prompt = my_strdup ( getenv ( "MYSQL_PS1" ) ? getenv ( "MYSQL_PS1" ) : "\\N [\\d]> " , MYF ( MY_WME ) ) ;
 current_prompt = my_strdup ( default_prompt , MYF ( MY_WME ) ) ;
 prompt_counter = 0 ;
 aborted = 0 ;
 outfile [ 0 ] = 0 ;
 strmov ( pager , "stdout" ) ;
 {
 char * tmp = getenv ( "PAGER" ) ;
 if ( tmp && strlen ( tmp ) ) {
 default_pager_set = 1 ;
 strmov ( default_pager , tmp ) ;
 }
 }
 if ( ! isatty ( 0 ) || ! isatty ( 1 ) ) {
 status . batch = 1 ;
 opt_silent = 1 ;
 ignore_errors = 0 ;
 }
 else status . add_to_history = 1 ;
 status . exit_status = 1 ;
 {
 int stdout_fileno_copy ;
 stdout_fileno_copy = dup ( fileno ( stdout ) ) ;
 if ( stdout_fileno_copy == - 1 ) fclose ( stdout ) ;
 else close ( stdout_fileno_copy ) ;
 }
 if ( load_defaults ( "my" , load_default_groups , & argc , & argv ) ) {
 my_end ( 0 ) ;
 exit ( 1 ) ;
 }
 defaults_argv = argv ;
 if ( get_options ( argc , ( char * * ) argv ) ) {
 free_defaults ( defaults_argv ) ;
 my_end ( 0 ) ;
 exit ( 1 ) ;
 }
 if ( status . batch && ! status . line_buff && ! ( status . line_buff = batch_readline_init ( MAX_BATCH_BUFFER_SIZE , stdin ) ) ) {
 put_info ( "Can't initialize batch_readline - may be the input source is " "a directory or a block device." , INFO_ERROR , 0 ) ;
 free_defaults ( defaults_argv ) ;
 my_end ( 0 ) ;
 exit ( 1 ) ;
 }
 if ( mysql_server_init ( embedded_server_arg_count , embedded_server_args , ( char * * ) embedded_server_groups ) ) {
 put_error ( NULL ) ;
 free_defaults ( defaults_argv ) ;
 my_end ( 0 ) ;
 exit ( 1 ) ;
 }
 glob_buffer . realloc ( 512 ) ;
 completion_hash_init ( & ht , 128 ) ;
 init_alloc_root ( & hash_mem_root , 16384 , 0 ) ;
 bzero ( ( char * ) & mysql , sizeof ( mysql ) ) ;
 if ( sql_connect ( current_host , current_db , current_user , opt_password , opt_silent ) ) {
 quick = 1 ;
 status . exit_status = 1 ;
 mysql_end ( - 1 ) ;
 }
 if ( ! status . batch ) ignore_errors = 1 ;
 if ( opt_sigint_ignore ) signal ( SIGINT , SIG_IGN ) ;
 else signal ( SIGINT , handle_sigint ) ;
 signal ( SIGQUIT , mysql_end ) ;

 window_resize ( 0 ) ;

 or \\g." , INFO_INFO ) ;
 my_snprintf ( ( char * ) glob_buffer . ptr ( ) , glob_buffer . alloced_length ( ) , "Your %s connection id is %lu\nServer version: %s\n" , mysql_get_server_name ( & mysql ) , mysql_thread_id ( & mysql ) , server_version_string ( & mysql ) ) ;
 put_info ( ( char * ) glob_buffer . ptr ( ) , INFO_INFO ) ;
 put_info ( ORACLE_WELCOME_COPYRIGHT_NOTICE ( "2000" ) , INFO_INFO ) ;

 if ( ! status . batch && ! quick && ! opt_html && ! opt_xml ) {
 if ( getenv ( "MYSQL_HISTFILE" ) ) histfile = my_strdup ( getenv ( "MYSQL_HISTFILE" ) , MYF ( MY_WME ) ) ;
 else if ( getenv ( "HOME" ) ) {
 histfile = ( char * ) my_malloc ( ( uint ) strlen ( getenv ( "HOME" ) ) + ( uint ) strlen ( "/.mysql_history" ) + 2 , MYF ( MY_WME ) ) ;
 if ( histfile ) sprintf ( histfile , "%s/.mysql_history" , getenv ( "HOME" ) ) ;
 char link_name [ FN_REFLEN ] ;
 if ( my_readlink ( link_name , histfile , 0 ) == 0 && strncmp ( link_name , "/devull" , 10 ) == 0 ) {
 my_free ( histfile ) ;
 histfile = 0 ;
 }
 }
 if ( histfile && strncmp ( histfile , "/devull" , 10 ) == 0 ) histfile = NULL ;
 if ( histfile && histfile [ 0 ] ) {
 if ( verbose ) tee_fprintf ( stdout , "Reading history-file %s\n" , histfile ) ;
 read_history ( histfile ) ;
 if ( ! ( histfile_tmp = ( char * ) my_malloc ( ( uint ) strlen ( histfile ) + 5 , MYF ( MY_WME ) ) ) ) {
 fprintf ( stderr , "Couldn't allocate memory for temp histfile!\n" ) ;
 exit ( 1 ) ;
 }
 sprintf ( histfile_tmp , "%s.TMP" , histfile ) ;
 }
 }

' or '\\h' for help. Type '\\c' to clear the current input statement.\n" ) ;
 put_info ( buff , INFO_INFO ) ;
 status . exit_status = read_and_execute ( ! status . batch ) ;
 if ( opt_outfile ) end_tee ( ) ;
 mysql_end ( 0 ) ;

