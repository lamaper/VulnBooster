static void free_resources ( ) {
 if ( md_result_file && md_result_file != stdout ) my_fclose ( md_result_file , MYF ( 0 ) ) ;
 my_free ( opt_password ) ;
 my_free ( current_host ) ;
 if ( my_hash_inited ( & ignore_table ) ) my_hash_free ( & ignore_table ) ;
 if ( extended_insert ) dynstr_free ( & extended_row ) ;
 if ( insert_pat_inited ) dynstr_free ( & insert_pat ) ;
 if ( defaults_argv ) free_defaults ( defaults_argv ) ;
 mysql_library_end ( ) ;
 my_end ( my_end_arg ) ;
 }