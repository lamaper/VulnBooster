static int get_flags ( MotionEstContext * c , int direct , int chroma ) {
 return ( ( c -> avctx -> flags & CODEC_FLAG_QPEL ) ? FLAG_QPEL : 0 ) + ( direct ? FLAG_DIRECT : 0 ) + ( chroma ? FLAG_CHROMA : 0 ) ;
 }