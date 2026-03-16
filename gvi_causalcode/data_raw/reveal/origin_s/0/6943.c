static SvcInternal * get_svc_internal ( SvcContext * svc_ctx ) {
 if ( svc_ctx == NULL ) return NULL ;
 if ( svc_ctx -> internal == NULL ) {
 SvcInternal * const si = ( SvcInternal * ) malloc ( sizeof ( * si ) ) ;
 if ( si != NULL ) {
 memset ( si , 0 , sizeof ( * si ) ) ;
 }
 svc_ctx -> internal = si ;
 }
 return ( SvcInternal * ) svc_ctx -> internal ;
 }