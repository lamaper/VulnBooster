static void server_send_summary ( struct client * client , struct config * config ) {
 char * path = NULL ;
 char * program ;
 const char * subcommand ;
 struct rule * rule = NULL ;
 size_t i ;
 const char * * req_argv = NULL ;
 bool ok_any = false ;
 int status_all = 0 ;
 struct process process ;
 struct evbuffer * output = NULL ;
 if ( client -> protocol == 1 ) {
 output = evbuffer_new ( ) ;
 if ( output == NULL ) die ( "internal error: cannot create output buffer" ) ;
 }
 for ( i = 0 ;
 i < config -> count ;
 i ++ ) {
 memset ( & process , 0 , sizeof ( process ) ) ;
 process . client = client ;
 rule = config -> rules [ i ] ;
 if ( ! server_config_acl_permit ( rule , client ) ) continue ;
 if ( rule -> summary == NULL ) continue ;
 ok_any = true ;
 path = rule -> program ;
 req_argv = xcalloc ( 4 , sizeof ( char * ) ) ;
 program = strrchr ( path , '/' ) ;
 if ( program == NULL ) program = path ;
 else program ++ ;
 req_argv [ 0 ] = program ;
 req_argv [ 1 ] = rule -> summary ;
 subcommand = rule -> subcommand ;
 if ( strcmp ( subcommand , "ALL" ) == 0 || strcmp ( subcommand , "EMPTY" ) == 0 ) req_argv [ 2 ] = NULL ;
 else req_argv [ 2 ] = subcommand ;
 req_argv [ 3 ] = NULL ;
 process . command = rule -> summary ;
 process . argv = req_argv ;
 process . rule = rule ;
 if ( server_process_run ( & process ) ) {
 if ( client -> protocol == 1 ) if ( evbuffer_add_buffer ( output , process . output ) < 0 ) die ( "internal error: cannot copy data from output buffer" ) ;
 if ( process . status != 0 ) status_all = process . status ;
 }
 free ( req_argv ) ;
 }
 if ( WIFEXITED ( status_all ) ) status_all = ( int ) WEXITSTATUS ( process . status ) ;
 else status_all = - 1 ;
 if ( ok_any ) client -> finish ( client , output , status_all ) ;
 else {
 notice ( "summary request from user %s, but no defined summaries" , client -> user ) ;
 client -> error ( client , ERROR_UNKNOWN_COMMAND , "Unknown command" ) ;
 }
 if ( output != NULL ) evbuffer_free ( output ) ;
 }