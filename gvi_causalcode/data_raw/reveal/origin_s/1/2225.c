static void sbr_hf_apply_noise_3 ( float ( * Y ) [ 2 ] , const float * s_m , const float * q_filt , int noise , int kx , int m_max ) {
 float phi_sign = 1 - 2 * ( kx & 1 ) ;
 sbr_hf_apply_noise ( Y , s_m , q_filt , noise , 0.0 , - phi_sign , m_max ) ;
 }