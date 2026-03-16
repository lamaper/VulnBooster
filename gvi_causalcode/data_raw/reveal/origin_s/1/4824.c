void vpx_svc_release ( SvcContext * svc_ctx ) {
 SvcInternal * si ;
 if ( svc_ctx == NULL ) return ;
 si = ( SvcInternal * ) svc_ctx -> internal ;
 if ( si != NULL ) {
 fd_free ( si -> frame_temp ) ;
 fd_free_list ( si -> frame_list ) ;
 if ( si -> rc_stats_buf ) {
 free ( si -> rc_stats_buf ) ;
 }
 free ( si ) ;
 svc_ctx -> internal = NULL ;
 }
 }