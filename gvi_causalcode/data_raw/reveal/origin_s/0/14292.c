static inline void decode_residual_chroma ( AVSContext * h ) {
 if ( h -> cbp & ( 1 << 4 ) ) decode_residual_block ( h , & h -> gb , chroma_dec , 0 , cavs_chroma_qp [ h -> qp ] , h -> cu , h -> c_stride ) ;
 if ( h -> cbp & ( 1 << 5 ) ) decode_residual_block ( h , & h -> gb , chroma_dec , 0 , cavs_chroma_qp [ h -> qp ] , h -> cv , h -> c_stride ) ;
 }