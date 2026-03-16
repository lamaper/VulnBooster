static int dissect_rtmpt_http ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data _U_ ) {
 conversation_t * conv ;
 rtmpt_conv_t * rconv ;
 int cdir ;
 guint32 seq ;
 guint32 lastackseq ;
 guint32 offset ;
 gint remain ;
 offset = 0 ;
 remain = tvb_reported_length_remaining ( tvb , 0 ) ;
 cdir = pinfo -> srcport == pinfo -> match_uint ;
 if ( cdir ) {
 conv = find_conversation ( pinfo -> num , & pinfo -> dst , & pinfo -> src , pinfo -> ptype , 0 , pinfo -> srcport , 0 ) ;
 if ( ! conv ) {
 RTMPT_DEBUG ( "RTMPT new conversation\n" ) ;
 conv = conversation_new ( pinfo -> num , & pinfo -> dst , & pinfo -> src , pinfo -> ptype , 0 , pinfo -> srcport , 0 ) ;
 }
 }
 else {
 conv = find_conversation ( pinfo -> num , & pinfo -> src , & pinfo -> dst , pinfo -> ptype , 0 , pinfo -> destport , 0 ) ;
 if ( ! conv ) {
 RTMPT_DEBUG ( "RTMPT new conversation\n" ) ;
 conv = conversation_new ( pinfo -> num , & pinfo -> src , & pinfo -> dst , pinfo -> ptype , 0 , pinfo -> destport , 0 ) ;
 }
 }
 rconv = ( rtmpt_conv_t * ) conversation_get_proto_data ( conv , proto_rtmpt ) ;
 if ( ! rconv ) {
 rconv = rtmpt_init_rconv ( conv ) ;
 }
 lastackseq = GPOINTER_TO_INT ( wmem_tree_lookup32_le ( rconv -> seqs [ cdir ^ 1 ] , pinfo -> num ) ) + 1 ;
 if ( cdir == 1 && lastackseq < 2 && remain == 17 ) {
 offset += 17 ;
 remain -= 17 ;
 }
 else if ( cdir || remain == 1 ) {
 offset ++ ;
 remain -- ;
 }
 seq = GPOINTER_TO_INT ( wmem_tree_lookup32 ( rconv -> seqs [ cdir ] , pinfo -> num ) ) ;
 if ( seq == 0 ) {
 seq = GPOINTER_TO_INT ( wmem_tree_lookup32_le ( rconv -> seqs [ cdir ] , pinfo -> num ) ) ;
 seq += remain ;
 wmem_tree_insert32 ( rconv -> seqs [ cdir ] , pinfo -> num , GINT_TO_POINTER ( seq ) ) ;
 }
 seq -= remain - 1 ;
 RTMPT_DEBUG ( "RTMPT f=%d cdir=%d seq=%d lastackseq=%d len=%d\n" , pinfo -> num , cdir , seq , lastackseq , remain ) ;
 if ( remain < 1 ) return offset ;
 if ( offset > 0 ) {
 tvbuff_t * tvbrtmp = tvb_new_subset_length ( tvb , offset , remain ) ;
 dissect_rtmpt_common ( tvbrtmp , pinfo , tree , rconv , cdir , seq , lastackseq ) ;
 }
 else {
 dissect_rtmpt_common ( tvb , pinfo , tree , rconv , cdir , seq , lastackseq ) ;
 }
 return tvb_captured_length ( tvb ) ;
 }