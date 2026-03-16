static err_status_t srtp_validate_rtp_header ( void * rtp_hdr , int * pkt_octet_len ) {
 srtp_hdr_t * hdr = ( srtp_hdr_t * ) rtp_hdr ;
 int rtp_header_len = octets_in_rtp_header + 4 * hdr -> cc ;
 if ( hdr -> x == 1 ) rtp_header_len += octets_in_rtp_extn_hdr ;
 if ( * pkt_octet_len < rtp_header_len ) return err_status_bad_param ;
 if ( hdr -> x == 1 ) {
 srtp_hdr_xtnd_t * xtn_hdr = ( srtp_hdr_xtnd_t * ) ( ( uint32_t * ) hdr + uint32s_in_rtp_header + hdr -> cc ) ;
 int profile_len = ntohs ( xtn_hdr -> length ) ;
 rtp_header_len += profile_len * 4 ;
 if ( * pkt_octet_len < rtp_header_len ) return err_status_bad_param ;
 }
 return err_status_ok ;
 }