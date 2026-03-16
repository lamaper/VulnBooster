static int asf_write_index ( AVFormatContext * s , const ASFIndex * index , uint16_t max , uint32_t count ) {
 AVIOContext * pb = s -> pb ;
 int i ;
 ff_put_guid ( pb , & ff_asf_simple_index_header ) ;
 avio_wl64 ( pb , 24 + 16 + 8 + 4 + 4 + ( 4 + 2 ) * count ) ;
 ff_put_guid ( pb , & ff_asf_my_guid ) ;
 avio_wl64 ( pb , ASF_INDEXED_INTERVAL ) ;
 avio_wl32 ( pb , max ) ;
 avio_wl32 ( pb , count ) ;
 for ( i = 0 ;
 i < count ;
 i ++ ) {
 avio_wl32 ( pb , index [ i ] . packet_number ) ;
 avio_wl16 ( pb , index [ i ] . packet_count ) ;
 }
 return 0 ;
 }