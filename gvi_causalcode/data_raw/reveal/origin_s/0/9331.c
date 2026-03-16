static inline void update_qscale ( MpegEncContext * s ) {
 s -> qscale = ( s -> lambda * 139 + FF_LAMBDA_SCALE * 64 ) >> ( FF_LAMBDA_SHIFT + 7 ) ;
 s -> qscale = av_clip ( s -> qscale , s -> avctx -> qmin , s -> avctx -> qmax ) ;
 s -> lambda2 = ( s -> lambda * s -> lambda + FF_LAMBDA_SCALE / 2 ) >> FF_LAMBDA_SHIFT ;
 }