void do_perl ( struct st_command * command ) {
 int error ;
 File fd ;
 FILE * res_file ;
 char buf [ FN_REFLEN ] ;
 char temp_file_path [ FN_REFLEN ] ;
 static DYNAMIC_STRING ds_script ;
 static DYNAMIC_STRING ds_delimiter ;
 const struct command_arg perl_args [ ] = {
 {
 "delimiter" , ARG_STRING , FALSE , & ds_delimiter , "Delimiter to read until" }
 }
 ;
 DBUG_ENTER ( "do_perl" ) ;
 check_command_args ( command , command -> first_argument , perl_args , sizeof ( perl_args ) / sizeof ( struct command_arg ) , ' ' ) ;
 ds_script = command -> content ;
 if ( ! ds_script . str ) {
 if ( ds_delimiter . length == 0 ) dynstr_set ( & ds_delimiter , "EOF" ) ;
 init_dynamic_string ( & ds_script , "" , 1024 , 1024 ) ;
 read_until_delimiter ( & ds_script , & ds_delimiter ) ;
 command -> content = ds_script ;
 }
 if ( cur_block -> ok ) {
 DBUG_PRINT ( "info" , ( "Executing perl: %s" , ds_script . str ) ) ;
 if ( ( fd = create_temp_file ( temp_file_path , getenv ( "MYSQLTEST_VARDIR" ) , "tmp" , O_CREAT | O_SHARE | O_RDWR , MYF ( MY_WME ) ) ) < 0 ) die ( "Failed to create temporary file for perl command" ) ;
 my_close ( fd , MYF ( 0 ) ) ;
 str_to_file ( temp_file_path , ds_script . str , ds_script . length ) ;
 my_snprintf ( buf , sizeof ( buf ) , "perl %s" , temp_file_path ) ;
 if ( ! ( res_file = popen ( buf , "r" ) ) ) {
 if ( command -> abort_on_error ) die ( "popen(\"%s\", \"r\") failed" , buf ) ;
 dynstr_free ( & ds_delimiter ) ;
 return ;
 }
 while ( fgets ( buf , sizeof ( buf ) , res_file ) ) {
 if ( disable_result_log ) {
 buf [ strlen ( buf ) - 1 ] = 0 ;
 DBUG_PRINT ( "exec_result" , ( "%s" , buf ) ) ;
 }
 else {
 replace_dynstr_append ( & ds_res , buf ) ;
 }
 }
 error = pclose ( res_file ) ;
 if ( ! error ) my_delete ( temp_file_path , MYF ( MY_WME ) ) ;
 int exstat = WEXITSTATUS ( error ) ;



 }
 dynstr_free ( & ds_delimiter ) ;
 DBUG_VOID_RETURN ;
 }