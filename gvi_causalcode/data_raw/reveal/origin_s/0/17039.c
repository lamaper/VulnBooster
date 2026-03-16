void mszipd_free ( struct mszipd_stream * zip ) {
 struct mspack_system * sys ;
 if ( zip ) {
 sys = zip -> sys ;
 sys -> free ( zip -> inbuf ) ;
 sys -> free ( zip ) ;
 }
 }