static int asf_write_markers ( AVFormatContext * s ) {
 ASFContext * asf = s -> priv_data ;
 AVIOContext * pb = s -> pb ;
 int i ;
 AVRational scale = {
 1 , 10000000 }
 ;
 int64_t hpos = put_header ( pb , & ff_asf_marker_header ) ;
 ff_put_guid ( pb , & ff_asf_reserved_4 ) ;
 avio_wl32 ( pb , s -> nb_chapters ) ;
 avio_wl16 ( pb , 0 ) ;
 avio_wl16 ( pb , 0 ) ;
 for ( i = 0 ;
 i < s -> nb_chapters ;
 i ++ ) {
 AVChapter * c = s -> chapters [ i ] ;
 AVDictionaryEntry * t = av_dict_get ( c -> metadata , "title" , NULL , 0 ) ;
 int64_t pres_time = av_rescale_q ( c -> start , c -> time_base , scale ) ;
 uint64_t offset ;
 int32_t send_time = get_send_time ( asf , pres_time , & offset ) ;
 int len = 0 ;
 uint8_t * buf ;
 AVIOContext * dyn_buf ;
 if ( t ) {
 if ( avio_open_dyn_buf ( & dyn_buf ) < 0 ) return AVERROR ( ENOMEM ) ;
 avio_put_str16le ( dyn_buf , t -> value ) ;
 len = avio_close_dyn_buf ( dyn_buf , & buf ) ;
 }
 avio_wl64 ( pb , offset ) ;
 avio_wl64 ( pb , pres_time + PREROLL_TIME * 10000 ) ;
 avio_wl16 ( pb , 12 + len ) ;
 avio_wl32 ( pb , send_time ) ;
 avio_wl32 ( pb , 0 ) ;
 avio_wl32 ( pb , len / 2 ) ;
 if ( t ) {
 avio_write ( pb , buf , len ) ;
 av_freep ( & buf ) ;
 }
 }
 end_header ( pb , hpos ) ;
 return 0 ;
 }