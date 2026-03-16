void TSfflush ( TSFile filep ) {
 FileImpl * file = ( FileImpl * ) filep ;
 file -> fflush ( ) ;
 }