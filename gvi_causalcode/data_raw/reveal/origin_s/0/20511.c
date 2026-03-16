static void put_chunk ( AVFormatContext * s , int type , int payload_length , int flags ) {
 ASFContext * asf = s -> priv_data ;
 AVIOContext * pb = s -> pb ;
 int length ;
 length = payload_length + 8 ;
 avio_wl16 ( pb , type ) ;
 avio_wl16 ( pb , length ) ;
 avio_wl32 ( pb , asf -> seqno ) ;
 avio_wl16 ( pb , flags ) ;
 avio_wl16 ( pb , length ) ;
 asf -> seqno ++ ;
 }