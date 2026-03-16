const char * vpx_svc_get_message ( const SvcContext * svc_ctx ) {
 const SvcInternal * const si = get_const_svc_internal ( svc_ctx ) ;
 if ( svc_ctx == NULL || si == NULL ) return NULL ;
 return si -> message_buffer ;
 }