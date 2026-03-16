static void put_str16 ( AVIOContext * s , const char * tag ) {
 int len ;
 uint8_t * pb ;
 AVIOContext * dyn_buf ;
 if ( avio_open_dyn_buf ( & dyn_buf ) < 0 ) return ;
 avio_put_str16le ( dyn_buf , tag ) ;
 len = avio_close_dyn_buf ( dyn_buf , & pb ) ;
 avio_wl16 ( s , len ) ;
 avio_write ( s , pb , len ) ;
 av_freep ( & pb ) ;
 }