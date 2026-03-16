static void sbr_hf_apply_noise_2 ( float ( * Y ) [ 2 ] , const float * s_m , const float * q_filt , int noise , int kx , int m_max ) {
 sbr_hf_apply_noise ( Y , s_m , q_filt , noise , - 1.0 , 0.0 , m_max ) ;
 }