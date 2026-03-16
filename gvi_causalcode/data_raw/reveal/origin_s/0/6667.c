static guint32 calculate_extended_seqno ( guint32 previous_seqno , guint16 raw_seqno ) {
 guint32 seqno = ( previous_seqno & 0xffff0000 ) | raw_seqno ;
 if ( seqno + 0x8000 < previous_seqno ) {
 seqno += 0x10000 ;
 }
 else if ( previous_seqno + 0x8000 < seqno ) {
 seqno -= 0x10000 ;
 }
 return seqno ;
 }