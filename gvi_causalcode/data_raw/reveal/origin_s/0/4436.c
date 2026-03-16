static inline void init_interlaced_ref ( MpegEncContext * s , int ref_index ) {
 MotionEstContext * const c = & s -> me ;
 c -> ref [ 1 + ref_index ] [ 0 ] = c -> ref [ 0 + ref_index ] [ 0 ] + s -> linesize ;
 c -> src [ 1 ] [ 0 ] = c -> src [ 0 ] [ 0 ] + s -> linesize ;
 if ( c -> flags & FLAG_CHROMA ) {
 c -> ref [ 1 + ref_index ] [ 1 ] = c -> ref [ 0 + ref_index ] [ 1 ] + s -> uvlinesize ;
 c -> ref [ 1 + ref_index ] [ 2 ] = c -> ref [ 0 + ref_index ] [ 2 ] + s -> uvlinesize ;
 c -> src [ 1 ] [ 1 ] = c -> src [ 0 ] [ 1 ] + s -> uvlinesize ;
 c -> src [ 1 ] [ 2 ] = c -> src [ 0 ] [ 2 ] + s -> uvlinesize ;
 }
 }