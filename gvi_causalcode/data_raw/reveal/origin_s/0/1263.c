static int ilbc_encode_frame ( AVCodecContext * avctx , AVPacket * avpkt , const AVFrame * frame , int * got_packet_ptr ) {
 ILBCEncContext * s = avctx -> priv_data ;
 int ret ;
 if ( ( ret = ff_alloc_packet ( avpkt , 50 ) ) ) {
 av_log ( avctx , AV_LOG_ERROR , "Error getting output packet\n" ) ;
 return ret ;
 }
 WebRtcIlbcfix_EncodeImpl ( ( WebRtc_UWord16 * ) avpkt -> data , ( const WebRtc_Word16 * ) frame -> data [ 0 ] , & s -> encoder ) ;
 avpkt -> size = s -> encoder . no_of_bytes ;
 * got_packet_ptr = 1 ;
 return 0 ;
 }