int main ( int argc , const char * * argv_ ) {
 unsigned int loops = 1 , i ;
 char * * argv , * * argi , * * argj ;
 struct arg arg ;
 int error = 0 ;
 argv = argv_dup ( argc - 1 , argv_ + 1 ) ;
 for ( argi = argj = argv ;
 ( * argj = * argi ) ;
 argi += arg . argv_step ) {
 memset ( & arg , 0 , sizeof ( arg ) ) ;
 arg . argv_step = 1 ;
 if ( arg_match ( & arg , & looparg , argi ) ) {
 loops = arg_parse_uint ( & arg ) ;
 break ;
 }
 }
 free ( argv ) ;
 for ( i = 0 ;
 ! error && i < loops ;
 i ++ ) error = main_loop ( argc , argv_ ) ;
 return error ;
 }