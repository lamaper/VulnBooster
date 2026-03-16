int load_kernel ( const char * filename , uint8_t * addr , uint8_t * real_addr ) {
 int fd , size ;
 int setup_sects ;
 fd = open ( filename , O_RDONLY ) ;
 if ( fd < 0 ) return - 1 ;
 if ( read ( fd , real_addr , 512 ) != 512 ) goto fail ;
 setup_sects = real_addr [ 0x1F1 ] ;
 if ( ! setup_sects ) setup_sects = 4 ;
 if ( read ( fd , real_addr + 512 , setup_sects * 512 ) != setup_sects * 512 ) goto fail ;
 size = read ( fd , addr , 16 * 1024 * 1024 ) ;
 if ( size < 0 ) goto fail ;
 close ( fd ) ;
 return size ;
 fail : close ( fd ) ;
 return - 1 ;
 }