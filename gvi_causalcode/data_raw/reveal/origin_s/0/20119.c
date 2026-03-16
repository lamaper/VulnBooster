int server_run_command ( struct client * client , struct config * config , struct iovec * * argv ) {
 char * command = NULL ;
 char * subcommand = NULL ;
 char * helpsubcommand = NULL ;
 struct rule * rule = NULL ;
 char * * req_argv = NULL ;
 size_t i ;
 int status = - 1 ;
 bool ok = false ;
 bool help = false ;
 const char * user = client -> user ;
 struct process process ;
 memset ( & process , 0 , sizeof ( process ) ) ;
 process . client = client ;
 if ( argv [ 0 ] == NULL ) {
 notice ( "empty command from user %s" , user ) ;
 client -> error ( client , ERROR_BAD_COMMAND , "Invalid command token" ) ;
 goto done ;
 }
 for ( i = 0 ;
 argv [ i ] != NULL && i < 2 ;
 i ++ ) {
 if ( memchr ( argv [ i ] -> iov_base , '\0' , argv [ i ] -> iov_len ) ) {
 notice ( "%s from user %s contains nul octet" , ( i == 0 ) ? "command" : "subcommand" , user ) ;
 client -> error ( client , ERROR_BAD_COMMAND , "Invalid command token" ) ;
 goto done ;
 }
 }
 command = xstrndup ( argv [ 0 ] -> iov_base , argv [ 0 ] -> iov_len ) ;
 if ( argv [ 1 ] != NULL ) subcommand = xstrndup ( argv [ 1 ] -> iov_base , argv [ 1 ] -> iov_len ) ;
 rule = find_config_line ( config , command , subcommand ) ;
 if ( rule == NULL && strcmp ( command , "help" ) == 0 ) {
 if ( argv [ 1 ] != NULL && argv [ 2 ] != NULL && argv [ 3 ] != NULL ) {
 notice ( "help command from user %s has more than three arguments" , user ) ;
 client -> error ( client , ERROR_TOOMANY_ARGS , "Too many arguments for help command" ) ;
 }
 if ( subcommand == NULL ) {
 server_send_summary ( client , config ) ;
 goto done ;
 }
 else {
 help = true ;
 if ( argv [ 2 ] != NULL ) helpsubcommand = xstrndup ( argv [ 2 ] -> iov_base , argv [ 2 ] -> iov_len ) ;
 rule = find_config_line ( config , subcommand , helpsubcommand ) ;
 }
 }
 for ( i = 1 ;
 argv [ i ] != NULL ;
 i ++ ) {
 if ( rule != NULL ) {
 if ( help == false && ( long ) i == rule -> stdin_arg ) continue ;
 if ( argv [ i + 1 ] == NULL && rule -> stdin_arg == - 1 ) continue ;
 }
 if ( memchr ( argv [ i ] -> iov_base , '\0' , argv [ i ] -> iov_len ) ) {
 notice ( "argument %lu from user %s contains nul octet" , ( unsigned long ) i , user ) ;
 client -> error ( client , ERROR_BAD_COMMAND , "Invalid command token" ) ;
 goto done ;
 }
 }
 server_log_command ( argv , rule , user ) ;
 if ( rule == NULL ) {
 notice ( "unknown command %s%s%s from user %s" , command , ( subcommand == NULL ) ? "" : " " , ( subcommand == NULL ) ? "" : subcommand , user ) ;
 client -> error ( client , ERROR_UNKNOWN_COMMAND , "Unknown command" ) ;
 goto done ;
 }
 if ( ! server_config_acl_permit ( rule , client ) ) {
 notice ( "access denied: user %s, command %s%s%s" , user , command , ( subcommand == NULL ) ? "" : " " , ( subcommand == NULL ) ? "" : subcommand ) ;
 client -> error ( client , ERROR_ACCESS , "Access denied" ) ;
 goto done ;
 }
 if ( help ) {
 if ( rule -> help == NULL ) {
 notice ( "command %s from user %s has no defined help" , command , user ) ;
 client -> error ( client , ERROR_NO_HELP , "No help defined for command" ) ;
 goto done ;
 }
 else {
 free ( subcommand ) ;
 subcommand = xstrdup ( rule -> help ) ;
 }
 }
 if ( help ) req_argv = create_argv_help ( rule -> program , subcommand , helpsubcommand ) ;
 else req_argv = create_argv_command ( rule , & process , argv ) ;
 process . command = command ;
 process . argv = ( const char * * ) req_argv ;
 process . rule = rule ;
 ok = server_process_run ( & process ) ;
 if ( ok ) {
 if ( WIFEXITED ( process . status ) ) process . status = ( signed int ) WEXITSTATUS ( process . status ) ;
 else process . status = - 1 ;
 client -> finish ( client , process . output , process . status ) ;
 }
 status = process . status ;
 done : free ( command ) ;
 free ( subcommand ) ;
 free ( helpsubcommand ) ;
 if ( req_argv != NULL ) {
 for ( i = 0 ;
 req_argv [ i ] != NULL ;
 i ++ ) free ( req_argv [ i ] ) ;
 free ( req_argv ) ;
 }
 if ( process . input != NULL ) evbuffer_free ( process . input ) ;
 if ( process . output != NULL ) evbuffer_free ( process . output ) ;
 return status ;
 }