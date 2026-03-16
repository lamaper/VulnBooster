static void clear_codec_buffers ( WmallDecodeCtx * s ) {
 int ich , ilms ;
 memset ( s -> acfilter_coeffs , 0 , sizeof ( s -> acfilter_coeffs ) ) ;
 memset ( s -> acfilter_prevvalues , 0 , sizeof ( s -> acfilter_prevvalues ) ) ;
 memset ( s -> lpc_coefs , 0 , sizeof ( s -> lpc_coefs ) ) ;
 memset ( s -> mclms_coeffs , 0 , sizeof ( s -> mclms_coeffs ) ) ;
 memset ( s -> mclms_coeffs_cur , 0 , sizeof ( s -> mclms_coeffs_cur ) ) ;
 memset ( s -> mclms_prevvalues , 0 , sizeof ( s -> mclms_prevvalues ) ) ;
 memset ( s -> mclms_updates , 0 , sizeof ( s -> mclms_updates ) ) ;
 for ( ich = 0 ;
 ich < s -> num_channels ;
 ich ++ ) {
 for ( ilms = 0 ;
 ilms < s -> cdlms_ttl [ ich ] ;
 ilms ++ ) {
 memset ( s -> cdlms [ ich ] [ ilms ] . coefs , 0 , sizeof ( s -> cdlms [ ich ] [ ilms ] . coefs ) ) ;
 memset ( s -> cdlms [ ich ] [ ilms ] . lms_prevvalues , 0 , sizeof ( s -> cdlms [ ich ] [ ilms ] . lms_prevvalues ) ) ;
 memset ( s -> cdlms [ ich ] [ ilms ] . lms_updates , 0 , sizeof ( s -> cdlms [ ich ] [ ilms ] . lms_updates ) ) ;
 }
 s -> ave_sum [ ich ] = 0 ;
 }
 }