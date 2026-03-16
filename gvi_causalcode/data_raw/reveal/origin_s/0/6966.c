static const SvcInternal * get_const_svc_internal ( const SvcContext * svc_ctx ) {
 if ( svc_ctx == NULL ) return NULL ;
 return ( const SvcInternal * ) svc_ctx -> internal ;
 }