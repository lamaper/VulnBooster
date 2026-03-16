void TSfclose ( TSFile filep ) {
 FileImpl * file = ( FileImpl * ) filep ;
 file -> fclose ( ) ;
 delete file ;
 }