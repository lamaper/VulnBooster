static guint32 fpdu_total_length ( struct tcpinfo * tcpinfo ) {
 guint32 size = 0 ;
 if ( tcpinfo -> seq < tcpinfo -> nxtseq ) {
 size = tcpinfo -> nxtseq - tcpinfo -> seq ;
 }
 if ( tcpinfo -> seq >= tcpinfo -> nxtseq ) {
 size = tcpinfo -> nxtseq + ( TCP_MAX_SEQ - tcpinfo -> seq ) ;
 }
 return size ;
 }