void getconfig ( int argc , char * * argv ) {
 char line [ MAXLINE ] ;



 if ( ! ExpandEnvironmentStrings ( ( LPCTSTR ) temp , ( LPTSTR ) config_file_storage , ( DWORD ) sizeof ( config_file_storage ) ) ) {
 msyslog ( LOG_ERR , "ExpandEnvironmentStrings CONFIG_FILE failed: %m\n" ) ;
 exit ( 1 ) ;
 }
 config_file = config_file_storage ;
 temp = ALT_CONFIG_FILE ;
 if ( ! ExpandEnvironmentStrings ( ( LPCTSTR ) temp , ( LPTSTR ) alt_config_file_storage , ( DWORD ) sizeof ( alt_config_file_storage ) ) ) {
 msyslog ( LOG_ERR , "ExpandEnvironmentStrings ALT_CONFIG_FILE failed: %m\n" ) ;
 exit ( 1 ) ;
 }
 alt_config_file = alt_config_file_storage ;

 set_sys_var ( line , strlen ( line ) + 1 , RO ) ;
 set_tod_using = & ntpd_set_tod_using ;

 set_sys_var ( line , strlen ( line ) + 1 , RO ) ;

 init_syntax_tree ( & cfgt ) ;
 curr_include_level = 0 ;
 if ( ( fp [ curr_include_level ] = F_OPEN ( FindConfig ( config_file ) , "r" ) ) == NULL # ifdef HAVE_NETINFO && check_netinfo && ! ( config_netinfo = get_netinfo_config ( ) ) # endif ) {
 msyslog ( LOG_INFO , "getconfig: Couldn't open <%s>" , FindConfig ( config_file ) ) ;

 return ;

 msyslog ( LOG_INFO , "getconfig: Couldn't open <%s>" , FindConfig ( alt_config_file ) ) ;
 io_open_sockets ( ) ;
 return ;
 }
 cfgt . source . value . s = estrdup ( alt_config_file ) ;

 else cfgt . source . value . s = estrdup ( config_file ) ;


 yyparse ( ) ;
 DPRINTF ( 1 , ( "Finished Parsing!!\n" ) ) ;
 cfgt . source . attr = CONF_SOURCE_FILE ;
 cfgt . timestamp = time ( NULL ) ;
 save_and_apply_config_tree ( ) ;
 while ( curr_include_level != - 1 ) FCLOSE ( fp [ curr_include_level -- ] ) ;

