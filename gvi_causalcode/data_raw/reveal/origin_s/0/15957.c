int V1F_Setup_Fetch ( struct vfp_ctx * vfc , struct http_conn * htc ) {
 struct vfp_entry * vfe ;
 CHECK_OBJ_NOTNULL ( vfc , VFP_CTX_MAGIC ) ;
 CHECK_OBJ_NOTNULL ( htc , HTTP_CONN_MAGIC ) ;
 switch ( htc -> body_status ) {
 case BS_EOF : assert ( htc -> content_length == - 1 ) ;
 vfe = VFP_Push ( vfc , & v1f_eof , 0 ) ;
 if ( vfe == NULL ) return ( ENOSPC ) ;
 vfe -> priv2 = 0 ;
 break ;
 case BS_LENGTH : assert ( htc -> content_length > 0 ) ;
 vfe = VFP_Push ( vfc , & v1f_straight , 0 ) ;
 if ( vfe == NULL ) return ( ENOSPC ) ;
 vfe -> priv2 = htc -> content_length ;
 break ;
 case BS_CHUNKED : assert ( htc -> content_length == - 1 ) ;
 vfe = VFP_Push ( vfc , & v1f_chunked , 0 ) ;
 if ( vfe == NULL ) return ( ENOSPC ) ;
 vfe -> priv2 = - 1 ;
 break ;
 default : WRONG ( "Wrong body_status" ) ;
 break ;
 }
 vfe -> priv1 = htc ;
 return 0 ;
 }