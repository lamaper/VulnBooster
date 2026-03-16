static inline void mlt_compensate_output ( COOKContext * q , float * decode_buffer , cook_gains * gains_ptr , float * previous_buffer , float * out ) {
 imlt_gain ( q , decode_buffer , gains_ptr , previous_buffer ) ;
 if ( out ) q -> saturate_output ( q , out ) ;
 }