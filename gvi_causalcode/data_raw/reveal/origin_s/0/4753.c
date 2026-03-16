static void sbr_gain_calc ( AACContext * ac , SpectralBandReplication * sbr , SBRData * ch_data , const int e_a [ 2 ] ) {
 int e , k , m ;
 static const float limgain [ 4 ] = {
 0.70795 , 1.0 , 1.41254 , 10000000000 }
 ;
 for ( e = 0 ;
 e < ch_data -> bs_num_env ;
 e ++ ) {
 int delta = ! ( ( e == e_a [ 1 ] ) || ( e == e_a [ 0 ] ) ) ;
 for ( k = 0 ;
 k < sbr -> n_lim ;
 k ++ ) {
 float gain_boost , gain_max ;
 float sum [ 2 ] = {
 0.0f , 0.0f }
 ;
 for ( m = sbr -> f_tablelim [ k ] - sbr -> kx [ 1 ] ;
 m < sbr -> f_tablelim [ k + 1 ] - sbr -> kx [ 1 ] ;
 m ++ ) {
 const float temp = sbr -> e_origmapped [ e ] [ m ] / ( 1.0f + sbr -> q_mapped [ e ] [ m ] ) ;
 sbr -> q_m [ e ] [ m ] = sqrtf ( temp * sbr -> q_mapped [ e ] [ m ] ) ;
 sbr -> s_m [ e ] [ m ] = sqrtf ( temp * ch_data -> s_indexmapped [ e + 1 ] [ m ] ) ;
 if ( ! sbr -> s_mapped [ e ] [ m ] ) {
 sbr -> gain [ e ] [ m ] = sqrtf ( sbr -> e_origmapped [ e ] [ m ] / ( ( 1.0f + sbr -> e_curr [ e ] [ m ] ) * ( 1.0f + sbr -> q_mapped [ e ] [ m ] * delta ) ) ) ;
 }
 else {
 sbr -> gain [ e ] [ m ] = sqrtf ( sbr -> e_origmapped [ e ] [ m ] * sbr -> q_mapped [ e ] [ m ] / ( ( 1.0f + sbr -> e_curr [ e ] [ m ] ) * ( 1.0f + sbr -> q_mapped [ e ] [ m ] ) ) ) ;
 }
 }
 for ( m = sbr -> f_tablelim [ k ] - sbr -> kx [ 1 ] ;
 m < sbr -> f_tablelim [ k + 1 ] - sbr -> kx [ 1 ] ;
 m ++ ) {
 sum [ 0 ] += sbr -> e_origmapped [ e ] [ m ] ;
 sum [ 1 ] += sbr -> e_curr [ e ] [ m ] ;
 }
 gain_max = limgain [ sbr -> bs_limiter_gains ] * sqrtf ( ( FLT_EPSILON + sum [ 0 ] ) / ( FLT_EPSILON + sum [ 1 ] ) ) ;
 gain_max = FFMIN ( 100000.f , gain_max ) ;
 for ( m = sbr -> f_tablelim [ k ] - sbr -> kx [ 1 ] ;
 m < sbr -> f_tablelim [ k + 1 ] - sbr -> kx [ 1 ] ;
 m ++ ) {
 float q_m_max = sbr -> q_m [ e ] [ m ] * gain_max / sbr -> gain [ e ] [ m ] ;
 sbr -> q_m [ e ] [ m ] = FFMIN ( sbr -> q_m [ e ] [ m ] , q_m_max ) ;
 sbr -> gain [ e ] [ m ] = FFMIN ( sbr -> gain [ e ] [ m ] , gain_max ) ;
 }
 sum [ 0 ] = sum [ 1 ] = 0.0f ;
 for ( m = sbr -> f_tablelim [ k ] - sbr -> kx [ 1 ] ;
 m < sbr -> f_tablelim [ k + 1 ] - sbr -> kx [ 1 ] ;
 m ++ ) {
 sum [ 0 ] += sbr -> e_origmapped [ e ] [ m ] ;
 sum [ 1 ] += sbr -> e_curr [ e ] [ m ] * sbr -> gain [ e ] [ m ] * sbr -> gain [ e ] [ m ] + sbr -> s_m [ e ] [ m ] * sbr -> s_m [ e ] [ m ] + ( delta && ! sbr -> s_m [ e ] [ m ] ) * sbr -> q_m [ e ] [ m ] * sbr -> q_m [ e ] [ m ] ;
 }
 gain_boost = sqrtf ( ( FLT_EPSILON + sum [ 0 ] ) / ( FLT_EPSILON + sum [ 1 ] ) ) ;
 gain_boost = FFMIN ( 1.584893192f , gain_boost ) ;
 for ( m = sbr -> f_tablelim [ k ] - sbr -> kx [ 1 ] ;
 m < sbr -> f_tablelim [ k + 1 ] - sbr -> kx [ 1 ] ;
 m ++ ) {
 sbr -> gain [ e ] [ m ] *= gain_boost ;
 sbr -> q_m [ e ] [ m ] *= gain_boost ;
 sbr -> s_m [ e ] [ m ] *= gain_boost ;
 }
 }
 }
 }