static void sbr_hf_assemble ( float Y1 [ 38 ] [ 64 ] [ 2 ] , const float X_high [ 64 ] [ 40 ] [ 2 ] , SpectralBandReplication * sbr , SBRData * ch_data , const int e_a [ 2 ] ) {
 int e , i , j , m ;
 const int h_SL = 4 * ! sbr -> bs_smoothing_mode ;
 const int kx = sbr -> kx [ 1 ] ;
 const int m_max = sbr -> m [ 1 ] ;
 static const float h_smooth [ 5 ] = {
 0.33333333333333 , 0.30150283239582 , 0.21816949906249 , 0.11516383427084 , 0.03183050093751 , }
 ;
 float ( * g_temp ) [ 48 ] = ch_data -> g_temp , ( * q_temp ) [ 48 ] = ch_data -> q_temp ;
 int indexnoise = ch_data -> f_indexnoise ;
 int indexsine = ch_data -> f_indexsine ;
 if ( sbr -> reset ) {
 for ( i = 0 ;
 i < h_SL ;
 i ++ ) {
 memcpy ( g_temp [ i + 2 * ch_data -> t_env [ 0 ] ] , sbr -> gain [ 0 ] , m_max * sizeof ( sbr -> gain [ 0 ] [ 0 ] ) ) ;
 memcpy ( q_temp [ i + 2 * ch_data -> t_env [ 0 ] ] , sbr -> q_m [ 0 ] , m_max * sizeof ( sbr -> q_m [ 0 ] [ 0 ] ) ) ;
 }
 }
 else if ( h_SL ) {
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 memcpy ( g_temp [ i + 2 * ch_data -> t_env [ 0 ] ] , g_temp [ i + 2 * ch_data -> t_env_num_env_old ] , sizeof ( g_temp [ 0 ] ) ) ;
 memcpy ( q_temp [ i + 2 * ch_data -> t_env [ 0 ] ] , q_temp [ i + 2 * ch_data -> t_env_num_env_old ] , sizeof ( q_temp [ 0 ] ) ) ;
 }
 }
 for ( e = 0 ;
 e < ch_data -> bs_num_env ;
 e ++ ) {
 for ( i = 2 * ch_data -> t_env [ e ] ;
 i < 2 * ch_data -> t_env [ e + 1 ] ;
 i ++ ) {
 memcpy ( g_temp [ h_SL + i ] , sbr -> gain [ e ] , m_max * sizeof ( sbr -> gain [ 0 ] [ 0 ] ) ) ;
 memcpy ( q_temp [ h_SL + i ] , sbr -> q_m [ e ] , m_max * sizeof ( sbr -> q_m [ 0 ] [ 0 ] ) ) ;
 }
 }
 for ( e = 0 ;
 e < ch_data -> bs_num_env ;
 e ++ ) {
 for ( i = 2 * ch_data -> t_env [ e ] ;
 i < 2 * ch_data -> t_env [ e + 1 ] ;
 i ++ ) {
 LOCAL_ALIGNED_16 ( float , g_filt_tab , [ 48 ] ) ;
 LOCAL_ALIGNED_16 ( float , q_filt_tab , [ 48 ] ) ;
 float * g_filt , * q_filt ;
 if ( h_SL && e != e_a [ 0 ] && e != e_a [ 1 ] ) {
 g_filt = g_filt_tab ;
 q_filt = q_filt_tab ;
 for ( m = 0 ;
 m < m_max ;
 m ++ ) {
 const int idx1 = i + h_SL ;
 g_filt [ m ] = 0.0f ;
 q_filt [ m ] = 0.0f ;
 for ( j = 0 ;
 j <= h_SL ;
 j ++ ) {
 g_filt [ m ] += g_temp [ idx1 - j ] [ m ] * h_smooth [ j ] ;
 q_filt [ m ] += q_temp [ idx1 - j ] [ m ] * h_smooth [ j ] ;
 }
 }
 }
 else {
 g_filt = g_temp [ i + h_SL ] ;
 q_filt = q_temp [ i ] ;
 }
 sbr -> dsp . hf_g_filt ( Y1 [ i ] + kx , X_high + kx , g_filt , m_max , i + ENVELOPE_ADJUSTMENT_OFFSET ) ;
 if ( e != e_a [ 0 ] && e != e_a [ 1 ] ) {
 sbr -> dsp . hf_apply_noise [ indexsine ] ( Y1 [ i ] + kx , sbr -> s_m [ e ] , q_filt , indexnoise , kx , m_max ) ;
 }
 else {
 int idx = indexsine & 1 ;
 int A = ( 1 - ( ( indexsine + ( kx & 1 ) ) & 2 ) ) ;
 int B = ( A ^ ( - idx ) ) + idx ;
 float * out = & Y1 [ i ] [ kx ] [ idx ] ;
 float * in = sbr -> s_m [ e ] ;
 for ( m = 0 ;
 m + 1 < m_max ;
 m += 2 ) {
 out [ 2 * m ] += in [ m ] * A ;
 out [ 2 * m + 2 ] += in [ m + 1 ] * B ;
 }
 if ( m_max & 1 ) out [ 2 * m ] += in [ m ] * A ;
 }
 indexnoise = ( indexnoise + m_max ) & 0x1ff ;
 indexsine = ( indexsine + 1 ) & 3 ;
 }
 }
 ch_data -> f_indexnoise = indexnoise ;
 ch_data -> f_indexsine = indexsine ;
 }