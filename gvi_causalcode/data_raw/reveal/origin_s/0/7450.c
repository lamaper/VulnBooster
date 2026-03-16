size_t TSfread ( TSFile filep , void * buf , size_t length ) {
 FileImpl * file = ( FileImpl * ) filep ;
 return file -> fread ( buf , length ) ;
 }