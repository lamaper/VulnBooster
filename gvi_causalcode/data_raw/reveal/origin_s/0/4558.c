sig_handler mysql_end ( int sig ) {

 signal ( SIGINT , SIG_IGN ) ;


 if ( verbose ) tee_fprintf ( stdout , "Writing history-file %s\n" , histfile ) ;
 if ( ! write_history ( histfile_tmp ) ) my_rename ( histfile_tmp , histfile , MYF ( MY_WME ) ) ;
 }
 batch_readline_end ( status . line_buff ) ;
 completion_hash_free ( & ht ) ;
 free_root ( & hash_mem_root , MYF ( 0 ) ) ;

 glob_buffer . free ( ) ;
 old_buffer . free ( ) ;
 processed_prompt . free ( ) ;
 my_free ( server_version ) ;
 my_free ( opt_password ) ;
 my_free ( opt_mysql_unix_port ) ;
 my_free ( histfile ) ;
 my_free ( histfile_tmp ) ;
 my_free ( current_db ) ;
 my_free ( current_host ) ;
 my_free ( current_user ) ;
 my_free ( full_username ) ;
 my_free ( part_username ) ;
 my_free ( default_prompt ) ;


 while ( embedded_server_arg_count > 1 ) my_free ( embedded_server_args [ -- embedded_server_arg_count ] ) ;
 mysql_server_end ( ) ;
 free_defaults ( defaults_argv ) ;
 my_end ( my_end_arg ) ;
 exit ( status . exit_status ) ;
 }