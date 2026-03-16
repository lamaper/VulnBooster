static int dissect_pvfs_heur ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 guint32 magic_nr , mode ;
 guint64 size ;
 if ( tvb_reported_length ( tvb ) < 24 ) {
 return 0 ;
 }
 magic_nr = tvb_get_letohl ( tvb , 0 ) ;
 if ( magic_nr != BMI_MAGIC_NR ) {
 return 0 ;
 }
 mode = tvb_get_letohl ( tvb , 4 ) ;
 switch ( mode ) {
 case TCP_MODE_IMMED : case TCP_MODE_UNEXP : case TCP_MODE_EAGER : case TCP_MODE_REND : break ;
 default : return 0 ;
 }
 size = tvb_get_letohl ( tvb , 20 ) ;
 size <<= 32 ;
 size |= tvb_get_letohl ( tvb , 16 ) ;
 if ( ( size > 1000000 ) || ( size == 0 ) ) {
 return 0 ;
 }
 tcp_dissect_pdus ( tvb , pinfo , tree , pvfs_desegment , 24 , get_pvfs_pdu_len , dissect_pvfs_pdu , data ) ;
 return tvb_reported_length ( tvb ) ;
 }