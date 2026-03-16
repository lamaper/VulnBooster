static void vdpau_h264_clear_rf ( VdpReferenceFrameH264 * rf ) {
 rf -> surface = VDP_INVALID_HANDLE ;
 rf -> is_long_term = VDP_FALSE ;
 rf -> top_is_reference = VDP_FALSE ;
 rf -> bottom_is_reference = VDP_FALSE ;
 rf -> field_order_cnt [ 0 ] = 0 ;
 rf -> field_order_cnt [ 1 ] = 0 ;
 rf -> frame_idx = 0 ;
 }