static int get_and_cmp_point ( const char * name , const char * mpi_x_string , const char * mpi_y_string , const char * desc , gcry_ctx_t ctx ) {
 gcry_mpi_point_t point ;
 gcry_mpi_t x , y , z ;
 int result = 0 ;
 point = gcry_mpi_ec_get_point ( name , ctx , 1 ) ;
 if ( ! point ) {
 fail ( "error getting point parameter '%s' of curve '%s'\n" , name , desc ) ;
 return 1 ;
 }
 if ( debug ) print_point ( name , point ) ;
 x = gcry_mpi_new ( 0 ) ;
 y = gcry_mpi_new ( 0 ) ;
 z = gcry_mpi_new ( 0 ) ;
 gcry_mpi_point_snatch_get ( x , y , z , point ) ;
 if ( cmp_mpihex ( x , mpi_x_string ) ) {
 fail ( "x coordinate of '%s' of curve '%s' does not match\n" , name , desc ) ;
 result = 1 ;
 }
 if ( cmp_mpihex ( y , mpi_y_string ) ) {
 fail ( "y coordinate of '%s' of curve '%s' does not match\n" , name , desc ) ;
 result = 1 ;
 }
 if ( cmp_mpihex ( z , "01" ) ) {
 fail ( "z coordinate of '%s' of curve '%s' is not 1\n" , name , desc ) ;
 result = 1 ;
 }
 gcry_mpi_release ( x ) ;
 gcry_mpi_release ( y ) ;
 gcry_mpi_release ( z ) ;
 return result ;
 }