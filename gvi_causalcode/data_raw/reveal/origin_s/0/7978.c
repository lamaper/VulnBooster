void qtmd_free ( struct qtmd_stream * qtm ) {
 struct mspack_system * sys ;
 if ( qtm ) {
 sys = qtm -> sys ;
 sys -> free ( qtm -> window ) ;
 sys -> free ( qtm -> inbuf ) ;
 sys -> free ( qtm ) ;
 }
 }