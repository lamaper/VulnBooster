int load_initrd ( const char * filename , uint8_t * addr ) {
 int fd , size ;
 printf ( "Load initrd\n" ) ;
 fd = open ( filename , O_RDONLY ) ;
 if ( fd < 0 ) return - 1 ;
 size = read ( fd , addr , 16 * 1024 * 1024 ) ;
 if ( size < 0 ) goto fail ;
 close ( fd ) ;
 printf ( "Load initrd: %d\n" , size ) ;
 return size ;
 fail : close ( fd ) ;
 printf ( "Load initrd failed\n" ) ;
 return - 1 ;
 }