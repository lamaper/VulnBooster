int main ( int argc , char * * argv ) {
 if ( argc < 2 ) {
 fprintf ( stderr , "Usage:\n%s t_header.h\n" , argv [ 0 ] ) ;
 exit ( 1 ) ;
 }
 debug = 1 ;
 populate_symb ( argv [ 1 ] ) ;
 generate_preamble ( ) ;
 generate_token_text ( ) ;
 generate_fsm ( ) ;
 return 0 ;
 }