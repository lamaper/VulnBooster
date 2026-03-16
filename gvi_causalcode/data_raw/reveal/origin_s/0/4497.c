static int vp3_update_thread_context ( AVCodecContext * dst , const AVCodecContext * src ) {
 Vp3DecodeContext * s = dst -> priv_data , * s1 = src -> priv_data ;
 int qps_changed = 0 , i , err ;

 if ( s != s1 ) ref_frames ( s , s1 ) ;
 return - 1 ;
 }
 if ( s != s1 ) {
 if ( ! s -> current_frame . f -> data [ 0 ] ) {
 int y_fragment_count , c_fragment_count ;
 s -> avctx = dst ;
 err = allocate_tables ( dst ) ;
 if ( err ) return err ;
 y_fragment_count = s -> fragment_width [ 0 ] * s -> fragment_height [ 0 ] ;
 c_fragment_count = s -> fragment_width [ 1 ] * s -> fragment_height [ 1 ] ;
 memcpy ( s -> motion_val [ 0 ] , s1 -> motion_val [ 0 ] , y_fragment_count * sizeof ( * s -> motion_val [ 0 ] ) ) ;
 memcpy ( s -> motion_val [ 1 ] , s1 -> motion_val [ 1 ] , c_fragment_count * sizeof ( * s -> motion_val [ 1 ] ) ) ;
 }
 if ( ( err = ref_frames ( s , s1 ) ) < 0 ) return err ;
 s -> keyframe = s1 -> keyframe ;
 for ( i = 0 ;
 i < 3 ;
 i ++ ) {
 if ( s -> qps [ i ] != s1 -> qps [ 1 ] ) {
 qps_changed = 1 ;
 memcpy ( & s -> qmat [ i ] , & s1 -> qmat [ i ] , sizeof ( s -> qmat [ i ] ) ) ;
 }
 }
 if ( s -> qps [ 0 ] != s1 -> qps [ 0 ] ) memcpy ( & s -> bounding_values_array , & s1 -> bounding_values_array , sizeof ( s -> bounding_values_array ) ) ;
 if ( qps_changed ) copy_fields ( s , s1 , qps , superblock_count ) ;

 return update_frames ( dst ) ;
 }