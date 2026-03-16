void vpx_svc_release ( SvcContext * svc_ctx ) {
 SvcInternal * si ;
 if ( svc_ctx == NULL ) return ;
 si = ( SvcInternal * ) svc_ctx -> internal ;
 if ( si != NULL ) {
 free ( si ) ;
 svc_ctx -> internal = NULL ;
 }
 }