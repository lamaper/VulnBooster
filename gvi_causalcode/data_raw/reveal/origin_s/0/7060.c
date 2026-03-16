static guint16 expected_ulpdu_length ( mpa_state_t * state , struct tcpinfo * tcpinfo , guint8 endpoint ) {
 guint32 length , pad_length , markers_length ;
 length = fpdu_total_length ( tcpinfo ) ;
 if ( length <= MPA_CRC_LEN ) return 0 ;
 length -= MPA_CRC_LEN ;
 pad_length = ( MPA_ALIGNMENT - ( length % MPA_ALIGNMENT ) ) % MPA_ALIGNMENT ;
 if ( length <= pad_length ) return 0 ;
 length -= pad_length ;
 if ( state -> minfo [ endpoint ] . valid ) {
 markers_length = number_of_markers ( state , tcpinfo , endpoint ) * MPA_MARKER_LEN ;
 if ( length <= markers_length ) return 0 ;
 length -= markers_length ;
 }
 if ( length <= MPA_ULPDU_LENGTH_LEN ) return 0 ;
 length -= MPA_ULPDU_LENGTH_LEN ;
 return ( guint16 ) length ;
 }