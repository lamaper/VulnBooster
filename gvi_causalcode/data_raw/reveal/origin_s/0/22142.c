size_t TSfwrite ( TSFile filep , const void * buf , size_t length ) {
 FileImpl * file = ( FileImpl * ) filep ;
 return file -> fwrite ( buf , length ) ;
 }