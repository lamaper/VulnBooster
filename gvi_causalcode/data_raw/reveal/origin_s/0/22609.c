static tvbuff_t * remove_markers ( tvbuff_t * tvb , packet_info * pinfo , guint32 marker_offset , guint32 num_markers , guint32 orig_length ) {
 guint8 * mfree_buff = NULL ;
 guint32 mfree_buff_length , tot_copy , cur_copy ;
 guint32 source_offset ;
 tvbuff_t * mfree_tvb = NULL ;
 DISSECTOR_ASSERT ( num_markers > 0 ) ;
 DISSECTOR_ASSERT ( orig_length > MPA_MARKER_LEN * num_markers ) ;
 DISSECTOR_ASSERT ( tvb_captured_length ( tvb ) == orig_length ) ;
 mfree_buff_length = orig_length - ( MPA_MARKER_LEN * num_markers ) ;
 mfree_buff = ( guint8 * ) wmem_alloc ( pinfo -> pool , mfree_buff_length ) ;
 tot_copy = 0 ;
 source_offset = 0 ;
 cur_copy = marker_offset ;
 while ( tot_copy < mfree_buff_length ) {
 tvb_memcpy ( tvb , mfree_buff + tot_copy , source_offset , cur_copy ) ;
 tot_copy += cur_copy ;
 source_offset += cur_copy + MPA_MARKER_LEN ;
 cur_copy = MIN ( MPA_MARKER_INTERVAL , ( mfree_buff_length - tot_copy ) ) ;
 }
 mfree_tvb = tvb_new_child_real_data ( tvb , mfree_buff , mfree_buff_length , mfree_buff_length ) ;
 add_new_data_source ( pinfo , mfree_tvb , "FPDU without Markers" ) ;
 return mfree_tvb ;
 }