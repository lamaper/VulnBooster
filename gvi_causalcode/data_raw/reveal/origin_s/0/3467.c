static guint32 pad_offset ( struct tcpinfo * tcpinfo , guint32 fpdu_total_len , guint8 pad_len ) {
 if ( ( tcpinfo -> nxtseq - MPA_CRC_LEN - MPA_MARKER_LEN ) % MPA_MARKER_INTERVAL == 0 ) {
 return fpdu_total_len - MPA_CRC_LEN - MPA_MARKER_LEN - pad_len ;
 }
 else {
 return fpdu_total_len - MPA_CRC_LEN - pad_len ;
 }
 }