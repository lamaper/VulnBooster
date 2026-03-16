static void copy_superblock ( uint16_t * dest , unsigned dest_stride , uint16_t * src , unsigned src_stride ) {
 unsigned y ;
 if ( src ) for ( y = 0 ;
 y < 8 ;
 y ++ ) memcpy ( dest + y * dest_stride , src + y * src_stride , sizeof ( uint16_t ) * 8 ) ;
 else for ( y = 0 ;
 y < 8 ;
 y ++ ) memset ( dest + y * dest_stride , 0 , sizeof ( uint16_t ) * 8 ) ;
 }