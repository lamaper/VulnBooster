static ssize_t v1f_read ( const struct vfp_ctx * vc , struct http_conn * htc , void * d , ssize_t len ) {
 ssize_t l ;
 unsigned char * p ;
 ssize_t i = 0 ;
 CHECK_OBJ_NOTNULL ( vc , VFP_CTX_MAGIC ) ;
 CHECK_OBJ_NOTNULL ( htc , HTTP_CONN_MAGIC ) ;
 assert ( len > 0 ) ;
 l = 0 ;
 p = d ;
 if ( htc -> pipeline_b ) {
 l = htc -> pipeline_e - htc -> pipeline_b ;
 assert ( l > 0 ) ;
 if ( l > len ) l = len ;
 memcpy ( p , htc -> pipeline_b , l ) ;
 p += l ;
 len -= l ;
 htc -> pipeline_b += l ;
 if ( htc -> pipeline_b == htc -> pipeline_e ) htc -> pipeline_b = htc -> pipeline_e = NULL ;
 }
 if ( len > 0 ) {
 i = read ( * htc -> rfd , p , len ) ;
 if ( i < 0 ) {
 VSLb ( vc -> wrk -> vsl , SLT_FetchError , "%s" , strerror ( errno ) ) ;
 return ( i ) ;
 }
 }
 return ( i + l ) ;
 }