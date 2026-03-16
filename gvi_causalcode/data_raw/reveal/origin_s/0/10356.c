static int matroska_read_packet ( AVFormatContext * s , AVPacket * pkt ) {
 MatroskaDemuxContext * matroska = s -> priv_data ;
 int ret = 0 ;
 while ( ! ret && matroska_deliver_packet ( matroska , pkt ) ) {
 int64_t pos = avio_tell ( matroska -> ctx -> pb ) ;
 if ( matroska -> done ) return AVERROR_EOF ;
 if ( matroska_parse_cluster ( matroska ) < 0 ) ret = matroska_resync ( matroska , pos ) ;
 }
 if ( ret == AVERROR_INVALIDDATA && pkt -> data ) {
 pkt -> flags |= AV_PKT_FLAG_CORRUPT ;
 return 0 ;
 }
 return ret ;
 }