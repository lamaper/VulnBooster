static int com_source ( String * buffer __attribute__ ( ( unused ) ) , char * line ) {
 char source_name [ FN_REFLEN ] , * end , * param ;
 LINE_BUFFER * line_buff ;
 int error ;
 STATUS old_status ;
 FILE * sql_file ;
 my_bool save_ignore_errors ;
 while ( my_isspace ( charset_info , * line ) ) line ++ ;
 if ( ! ( param = strchr ( line , ' ' ) ) ) return put_info ( "Usage: \\. <filename> | source <filename>" , INFO_ERROR , 0 ) ;
 while ( my_isspace ( charset_info , * param ) ) param ++ ;
 end = strmake_buf ( source_name , param ) ;
 while ( end > source_name && ( my_isspace ( charset_info , end [ - 1 ] ) || my_iscntrl ( charset_info , end [ - 1 ] ) ) ) end -- ;
 end [ 0 ] = 0 ;
 unpack_filename ( source_name , source_name ) ;
 if ( ! ( sql_file = my_fopen ( source_name , O_RDONLY | O_BINARY , MYF ( 0 ) ) ) ) {
 char buff [ FN_REFLEN + 60 ] ;
 sprintf ( buff , "Failed to open file '%s', error: %d" , source_name , errno ) ;
 return put_info ( buff , INFO_ERROR , 0 ) ;
 }
 if ( ! ( line_buff = batch_readline_init ( MAX_BATCH_BUFFER_SIZE , sql_file ) ) ) {
 my_fclose ( sql_file , MYF ( 0 ) ) ;
 return put_info ( "Can't initialize batch_readline" , INFO_ERROR , 0 ) ;
 }
 old_status = status ;
 save_ignore_errors = ignore_errors ;
 bfill ( ( char * ) & status , sizeof ( status ) , ( char ) 0 ) ;
 status . batch = old_status . batch ;
 status . line_buff = line_buff ;
 status . file_name = source_name ;
 glob_buffer . length ( 0 ) ;
 ignore_errors = ! batch_abort_on_error ;
 in_com_source = 1 ;
 error = read_and_execute ( false ) ;
 ignore_errors = save_ignore_errors ;
 status = old_status ;
 in_com_source = aborted = 0 ;
 my_fclose ( sql_file , MYF ( 0 ) ) ;
 batch_readline_end ( line_buff ) ;
 if ( error && ignore_errors ) error = - 1 ;
 return error ;
 }