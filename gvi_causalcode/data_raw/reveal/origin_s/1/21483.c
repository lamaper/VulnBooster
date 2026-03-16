__attribute__ ( ( format ( printf , 2 , 3 ) ) ) static int cmd_submitf ( int id , const char * fmt , ... ) {
 char cmd [ MAX_EXTERNAL_COMMAND_LENGTH ] ;
 const char * command ;
 int len , len2 ;
 va_list ap ;
 command = extcmd_get_name ( id ) ;
 len = snprintf ( cmd , sizeof ( cmd ) - 1 , "[%lu] %s;
" , time ( NULL ) , command ) ;
 if ( len < 0 ) return ERROR ;
 if ( fmt ) {
 va_start ( ap , fmt ) ;
 len2 = vsnprintf ( & cmd [ len ] , sizeof ( cmd ) - len - 1 , fmt , ap ) ;
 va_end ( ap ) ;
 if ( len2 < 0 ) return ERROR ;
 }
 return write_command_to_file ( cmd ) ;
 }