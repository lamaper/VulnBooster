char * TSfgets ( TSFile filep , char * buf , size_t length ) {
 FileImpl * file = ( FileImpl * ) filep ;
 return file -> fgets ( buf , length ) ;
 }