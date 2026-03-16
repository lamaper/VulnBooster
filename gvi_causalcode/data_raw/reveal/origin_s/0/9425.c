static void at1_subband_synthesis ( AT1Ctx * q , AT1SUCtx * su , float * pOut ) {
 float temp [ 256 ] ;
 float iqmf_temp [ 512 + 46 ] ;
 ff_atrac_iqmf ( q -> bands [ 0 ] , q -> bands [ 1 ] , 128 , temp , su -> fst_qmf_delay , iqmf_temp ) ;
 memcpy ( su -> last_qmf_delay , & su -> last_qmf_delay [ 256 ] , sizeof ( float ) * 23 ) ;
 memcpy ( & su -> last_qmf_delay [ 23 ] , q -> bands [ 2 ] , sizeof ( float ) * 256 ) ;
 ff_atrac_iqmf ( temp , su -> last_qmf_delay , 256 , pOut , su -> snd_qmf_delay , iqmf_temp ) ;
 }