static void put_payload_header ( AVFormatContext * s , ASFStream * stream , int64_t presentation_time , int m_obj_size , int m_obj_offset , int payload_len , int flags ) {
 ASFContext * asf = s -> priv_data ;
 AVIOContext * pb = & asf -> pb ;
 int val ;
 val = stream -> num ;
 if ( flags & AV_PKT_FLAG_KEY ) val |= ASF_PL_FLAG_KEY_FRAME ;
 avio_w8 ( pb , val ) ;
 avio_w8 ( pb , stream -> seq ) ;
 avio_wl32 ( pb , m_obj_offset ) ;
 avio_w8 ( pb , ASF_PAYLOAD_REPLICATED_DATA_LENGTH ) ;
 avio_wl32 ( pb , m_obj_size ) ;
 avio_wl32 ( pb , ( uint32_t ) presentation_time ) ;
 if ( asf -> multi_payloads_present ) {
 avio_wl16 ( pb , payload_len ) ;
 }
 }