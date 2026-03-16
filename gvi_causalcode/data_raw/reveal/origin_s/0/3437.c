static void sql_inline_error_callback ( void * arg ) {
 inline_error_callback_arg * callback_arg = ( inline_error_callback_arg * ) arg ;
 int syntaxerrposition ;
 syntaxerrposition = geterrposition ( ) ;
 if ( syntaxerrposition > 0 ) {
 errposition ( 0 ) ;
 internalerrposition ( syntaxerrposition ) ;
 internalerrquery ( callback_arg -> prosrc ) ;
 }
 errcontext ( "SQL function \"%s\" during inlining" , callback_arg -> proname ) ;
 }