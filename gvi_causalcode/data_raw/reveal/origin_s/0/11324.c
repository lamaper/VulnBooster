static GstFlowReturn gst_asf_demux_process_simple_index ( GstASFDemux * demux , guint8 * data , guint64 size ) {
 GstClockTime interval ;
 guint32 count , i ;
 if ( size < ( 16 + 8 + 4 + 4 ) ) goto not_enough_data ;
 gst_asf_demux_skip_bytes ( 16 , & data , & size ) ;
 interval = gst_asf_demux_get_uint64 ( & data , & size ) * ( GstClockTime ) 100 ;
 gst_asf_demux_skip_bytes ( 4 , & data , & size ) ;
 count = gst_asf_demux_get_uint32 ( & data , & size ) ;
 if ( count > 0 ) {
 demux -> sidx_interval = interval ;
 demux -> sidx_num_entries = count ;
 g_free ( demux -> sidx_entries ) ;
 demux -> sidx_entries = g_new0 ( AsfSimpleIndexEntry , count ) ;
 for ( i = 0 ;
 i < count ;
 ++ i ) {
 if ( G_UNLIKELY ( size < 6 ) ) {
 demux -> sidx_num_entries -= ( count - i ) ;
 break ;
 }
 demux -> sidx_entries [ i ] . packet = gst_asf_demux_get_uint32 ( & data , & size ) ;
 demux -> sidx_entries [ i ] . count = gst_asf_demux_get_uint16 ( & data , & size ) ;
 GST_LOG_OBJECT ( demux , "%" GST_TIME_FORMAT " = packet %4u count : %2d" , GST_TIME_ARGS ( i * interval ) , demux -> sidx_entries [ i ] . packet , demux -> sidx_entries [ i ] . count ) ;
 }
 }
 else {
 GST_DEBUG_OBJECT ( demux , "simple index object with 0 entries" ) ;
 }
 return GST_FLOW_OK ;
 not_enough_data : {
 GST_WARNING_OBJECT ( demux , "short read parsing simple index object!" ) ;
 return GST_FLOW_OK ;
 }
 }