void dissect_h245_FastStart_OLC ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , char * codec_str ) {
 fast_start = TRUE ;
 upcoming_olc = NULL ;
 upcoming_channel = NULL ;
 codec_type = NULL ;
 dissect_OpenLogicalChannel_PDU ( tvb , pinfo , tree ) ;
 if ( h245_pi != NULL ) h245_pi -> msg_type = H245_OpenLogChn ;
 if ( codec_str && codec_type ) {
 g_strlcpy ( codec_str , codec_type , 50 ) ;
 }
 }