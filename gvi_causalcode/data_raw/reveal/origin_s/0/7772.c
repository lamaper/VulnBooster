static void put_frame ( AVFormatContext * s , ASFStream * stream , AVStream * avst , int64_t timestamp , const uint8_t * buf , int m_obj_size , int flags ) {
 ASFContext * asf = s -> priv_data ;
 int m_obj_offset , payload_len , frag_len1 ;
 m_obj_offset = 0 ;
 while ( m_obj_offset < m_obj_size ) {
 payload_len = m_obj_size - m_obj_offset ;
 if ( asf -> packet_timestamp_start == - 1 ) {
 asf -> multi_payloads_present = ( payload_len < MULTI_PAYLOAD_CONSTANT ) ;
 asf -> packet_size_left = PACKET_SIZE ;
 if ( asf -> multi_payloads_present ) {
 frag_len1 = MULTI_PAYLOAD_CONSTANT - 1 ;
 }
 else {
 frag_len1 = SINGLE_PAYLOAD_DATA_LENGTH ;
 }
 asf -> packet_timestamp_start = timestamp ;
 }
 else {
 frag_len1 = asf -> packet_size_left - PAYLOAD_HEADER_SIZE_MULTIPLE_PAYLOADS - PACKET_HEADER_MIN_SIZE - 1 ;
 if ( frag_len1 < payload_len && avst -> codec -> codec_type == AVMEDIA_TYPE_AUDIO ) {
 flush_packet ( s ) ;
 continue ;
 }
 if ( asf -> packet_timestamp_start > INT64_MAX - UINT16_MAX || timestamp > asf -> packet_timestamp_start + UINT16_MAX ) {
 flush_packet ( s ) ;
 continue ;
 }
 }
 if ( frag_len1 > 0 ) {
 if ( payload_len > frag_len1 ) payload_len = frag_len1 ;
 else if ( payload_len == ( frag_len1 - 1 ) ) payload_len = frag_len1 - 2 ;
 put_payload_header ( s , stream , timestamp + PREROLL_TIME , m_obj_size , m_obj_offset , payload_len , flags ) ;
 avio_write ( & asf -> pb , buf , payload_len ) ;
 if ( asf -> multi_payloads_present ) asf -> packet_size_left -= ( payload_len + PAYLOAD_HEADER_SIZE_MULTIPLE_PAYLOADS ) ;
 else asf -> packet_size_left -= ( payload_len + PAYLOAD_HEADER_SIZE_SINGLE_PAYLOAD ) ;
 asf -> packet_timestamp_end = timestamp ;
 asf -> packet_nb_payloads ++ ;
 }
 else {
 payload_len = 0 ;
 }
 m_obj_offset += payload_len ;
 buf += payload_len ;
 if ( ! asf -> multi_payloads_present ) flush_packet ( s ) ;
 else if ( asf -> packet_size_left <= ( PAYLOAD_HEADER_SIZE_MULTIPLE_PAYLOADS + PACKET_HEADER_MIN_SIZE + 1 ) ) flush_packet ( s ) ;
 else if ( asf -> packet_nb_payloads == ASF_PAYLOADS_PER_PACKET ) flush_packet ( s ) ;
 }
 stream -> seq ++ ;
 }