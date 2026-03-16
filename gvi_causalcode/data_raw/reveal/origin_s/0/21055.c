static void set_temporal_layer_pattern ( int layering_mode , vpx_codec_enc_cfg_t * cfg , int * layer_flags , int * flag_periodicity ) {
 switch ( layering_mode ) {
 case 0 : {
 int ids [ 1 ] = {
 0 }
 ;
 cfg -> ts_periodicity = 1 ;
 * flag_periodicity = 1 ;
 cfg -> ts_number_layers = 1 ;
 cfg -> ts_rate_decimator [ 0 ] = 1 ;
 memcpy ( cfg -> ts_layer_id , ids , sizeof ( ids ) ) ;
 layer_flags [ 0 ] = VPX_EFLAG_FORCE_KF | VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF ;
 break ;
 }
 case 1 : {
 int ids [ 2 ] = {
 0 , 1 }
 ;
 cfg -> ts_periodicity = 2 ;
 * flag_periodicity = 2 ;
 cfg -> ts_number_layers = 2 ;
 cfg -> ts_rate_decimator [ 0 ] = 2 ;
 cfg -> ts_rate_decimator [ 1 ] = 1 ;
 memcpy ( cfg -> ts_layer_id , ids , sizeof ( ids ) ) ;

 layer_flags [ 1 ] = VP8_EFLAG_NO_UPD_ARF | VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_REF_ARF ;

 layer_flags [ 1 ] = VP8_EFLAG_NO_UPD_ARF | VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_REF_ARF | VP8_EFLAG_NO_REF_LAST ;

 }
 case 2 : {
 int ids [ 3 ] = {
 0 , 1 , 1 }
 ;
 cfg -> ts_periodicity = 3 ;
 * flag_periodicity = 3 ;
 cfg -> ts_number_layers = 2 ;
 cfg -> ts_rate_decimator [ 0 ] = 3 ;
 cfg -> ts_rate_decimator [ 1 ] = 1 ;
 memcpy ( cfg -> ts_layer_id , ids , sizeof ( ids ) ) ;
 layer_flags [ 0 ] = VPX_EFLAG_FORCE_KF | VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF | VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF ;
 layer_flags [ 1 ] = layer_flags [ 2 ] = VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF | VP8_EFLAG_NO_UPD_ARF | VP8_EFLAG_NO_UPD_LAST ;
 break ;
 }
 case 3 : {
 int ids [ 6 ] = {
 0 , 2 , 2 , 1 , 2 , 2 }
 ;
 cfg -> ts_periodicity = 6 ;
 * flag_periodicity = 6 ;
 cfg -> ts_number_layers = 3 ;
 cfg -> ts_rate_decimator [ 0 ] = 6 ;
 cfg -> ts_rate_decimator [ 1 ] = 3 ;
 cfg -> ts_rate_decimator [ 2 ] = 1 ;
 memcpy ( cfg -> ts_layer_id , ids , sizeof ( ids ) ) ;
 layer_flags [ 0 ] = VPX_EFLAG_FORCE_KF | VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF | VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF ;
 layer_flags [ 3 ] = VP8_EFLAG_NO_REF_ARF | VP8_EFLAG_NO_UPD_ARF | VP8_EFLAG_NO_UPD_LAST ;
 layer_flags [ 1 ] = layer_flags [ 2 ] = layer_flags [ 4 ] = layer_flags [ 5 ] = VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_LAST ;
 break ;
 }
 case 4 : {
 int ids [ 4 ] = {
 0 , 2 , 1 , 2 }
 ;
 cfg -> ts_periodicity = 4 ;
 * flag_periodicity = 4 ;
 cfg -> ts_number_layers = 3 ;
 cfg -> ts_rate_decimator [ 0 ] = 4 ;
 cfg -> ts_rate_decimator [ 1 ] = 2 ;
 cfg -> ts_rate_decimator [ 2 ] = 1 ;
 memcpy ( cfg -> ts_layer_id , ids , sizeof ( ids ) ) ;
 layer_flags [ 0 ] = VPX_EFLAG_FORCE_KF | VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF | VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF ;
 layer_flags [ 2 ] = VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF | VP8_EFLAG_NO_UPD_ARF | VP8_EFLAG_NO_UPD_LAST ;
 layer_flags [ 1 ] = layer_flags [ 3 ] = VP8_EFLAG_NO_REF_ARF | VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF ;
 break ;
 }
 case 5 : {
 int ids [ 4 ] = {
 0 , 2 , 1 , 2 }
 ;
 cfg -> ts_periodicity = 4 ;
 * flag_periodicity = 4 ;
 cfg -> ts_number_layers = 3 ;
 cfg -> ts_rate_decimator [ 0 ] = 4 ;
 cfg -> ts_rate_decimator [ 1 ] = 2 ;
 cfg -> ts_rate_decimator [ 2 ] = 1 ;
 memcpy ( cfg -> ts_layer_id , ids , sizeof ( ids ) ) ;
 layer_flags [ 0 ] = VPX_EFLAG_FORCE_KF | VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF | VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF ;
 layer_flags [ 2 ] = VP8_EFLAG_NO_REF_ARF | VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_ARF ;
 layer_flags [ 1 ] = layer_flags [ 3 ] = VP8_EFLAG_NO_REF_ARF | VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF ;
 break ;
 }
 case 6 : {
 int ids [ 4 ] = {
 0 , 2 , 1 , 2 }
 ;
 cfg -> ts_periodicity = 4 ;
 * flag_periodicity = 4 ;
 cfg -> ts_number_layers = 3 ;
 cfg -> ts_rate_decimator [ 0 ] = 4 ;
 cfg -> ts_rate_decimator [ 1 ] = 2 ;
 cfg -> ts_rate_decimator [ 2 ] = 1 ;
 memcpy ( cfg -> ts_layer_id , ids , sizeof ( ids ) ) ;
 layer_flags [ 0 ] = VPX_EFLAG_FORCE_KF | VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF | VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF ;
 layer_flags [ 2 ] = VP8_EFLAG_NO_REF_ARF | VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_ARF ;
 layer_flags [ 1 ] = layer_flags [ 3 ] = VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_GF ;
 break ;
 }
 case 7 : {
 int ids [ 16 ] = {
 0 , 4 , 3 , 4 , 2 , 4 , 3 , 4 , 1 , 4 , 3 , 4 , 2 , 4 , 3 , 4 }
 ;
 cfg -> ts_periodicity = 16 ;
 * flag_periodicity = 16 ;
 cfg -> ts_number_layers = 5 ;
 cfg -> ts_rate_decimator [ 0 ] = 16 ;
 cfg -> ts_rate_decimator [ 1 ] = 8 ;
 cfg -> ts_rate_decimator [ 2 ] = 4 ;
 cfg -> ts_rate_decimator [ 3 ] = 2 ;
 cfg -> ts_rate_decimator [ 4 ] = 1 ;
 memcpy ( cfg -> ts_layer_id , ids , sizeof ( ids ) ) ;
 layer_flags [ 0 ] = VPX_EFLAG_FORCE_KF ;
 layer_flags [ 1 ] = layer_flags [ 3 ] = layer_flags [ 5 ] = layer_flags [ 7 ] = layer_flags [ 9 ] = layer_flags [ 11 ] = layer_flags [ 13 ] = layer_flags [ 15 ] = VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF ;
 layer_flags [ 2 ] = layer_flags [ 6 ] = layer_flags [ 10 ] = layer_flags [ 14 ] = VP8_EFLAG_NO_UPD_ARF | VP8_EFLAG_NO_UPD_GF ;
 layer_flags [ 4 ] = layer_flags [ 12 ] = VP8_EFLAG_NO_REF_LAST | VP8_EFLAG_NO_UPD_ARF ;
 layer_flags [ 8 ] = VP8_EFLAG_NO_REF_LAST | VP8_EFLAG_NO_REF_GF ;
 break ;
 }
 case 8 : {
 int ids [ 2 ] = {
 0 , 1 }
 ;
 cfg -> ts_periodicity = 2 ;
 * flag_periodicity = 8 ;
 cfg -> ts_number_layers = 2 ;
 cfg -> ts_rate_decimator [ 0 ] = 2 ;
 cfg -> ts_rate_decimator [ 1 ] = 1 ;
 memcpy ( cfg -> ts_layer_id , ids , sizeof ( ids ) ) ;
 layer_flags [ 0 ] = VPX_EFLAG_FORCE_KF | VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_UPD_ARF ;
 layer_flags [ 1 ] = VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_ARF ;
 layer_flags [ 2 ] = VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF ;
 layer_flags [ 3 ] = VP8_EFLAG_NO_UPD_ARF | VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_ENTROPY ;
 layer_flags [ 4 ] = layer_flags [ 2 ] ;
 layer_flags [ 5 ] = layer_flags [ 3 ] ;
 layer_flags [ 6 ] = layer_flags [ 4 ] ;
 layer_flags [ 7 ] = layer_flags [ 5 ] ;
 break ;
 }
 case 9 : {
 int ids [ 4 ] = {
 0 , 2 , 1 , 2 }
 ;
 cfg -> ts_periodicity = 4 ;
 * flag_periodicity = 8 ;
 cfg -> ts_number_layers = 3 ;
 cfg -> ts_rate_decimator [ 0 ] = 4 ;
 cfg -> ts_rate_decimator [ 1 ] = 2 ;
 cfg -> ts_rate_decimator [ 2 ] = 1 ;
 memcpy ( cfg -> ts_layer_id , ids , sizeof ( ids ) ) ;
 layer_flags [ 0 ] = VPX_EFLAG_FORCE_KF | VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF | VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF ;
 layer_flags [ 1 ] = VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF | VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_GF ;
 layer_flags [ 2 ] = VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF | VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_ARF ;
 layer_flags [ 3 ] = layer_flags [ 5 ] = VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_GF ;
 layer_flags [ 4 ] = VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF | VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF ;
 layer_flags [ 6 ] = VP8_EFLAG_NO_REF_ARF | VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_ARF ;
 layer_flags [ 7 ] = VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF | VP8_EFLAG_NO_UPD_ENTROPY ;
 break ;
 }
 case 10 : {
 int ids [ 4 ] = {
 0 , 2 , 1 , 2 }
 ;
 cfg -> ts_periodicity = 4 ;
 * flag_periodicity = 8 ;
 cfg -> ts_number_layers = 3 ;
 cfg -> ts_rate_decimator [ 0 ] = 4 ;
 cfg -> ts_rate_decimator [ 1 ] = 2 ;
 cfg -> ts_rate_decimator [ 2 ] = 1 ;
 memcpy ( cfg -> ts_layer_id , ids , sizeof ( ids ) ) ;
 layer_flags [ 0 ] = VPX_EFLAG_FORCE_KF | VP8_EFLAG_NO_UPD_ARF | VP8_EFLAG_NO_REF_GF ;
 layer_flags [ 1 ] = VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF | VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_ENTROPY ;
 layer_flags [ 2 ] = VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_UPD_ARF | VP8_EFLAG_NO_UPD_LAST ;
 layer_flags [ 3 ] = VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF | VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_ENTROPY ;
 layer_flags [ 4 ] = VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF | VP8_EFLAG_NO_REF_GF ;
 layer_flags [ 5 ] = layer_flags [ 3 ] ;
 layer_flags [ 6 ] = VP8_EFLAG_NO_UPD_ARF | VP8_EFLAG_NO_UPD_LAST ;
 layer_flags [ 7 ] = layer_flags [ 3 ] ;
 break ;
 }
 case 11 : default : {
 int ids [ 4 ] = {
 0 , 2 , 1 , 2 }
 ;
 cfg -> ts_periodicity = 4 ;
 * flag_periodicity = 8 ;
 cfg -> ts_number_layers = 3 ;
 cfg -> ts_rate_decimator [ 0 ] = 4 ;
 cfg -> ts_rate_decimator [ 1 ] = 2 ;
 cfg -> ts_rate_decimator [ 2 ] = 1 ;
 memcpy ( cfg -> ts_layer_id , ids , sizeof ( ids ) ) ;
 layer_flags [ 0 ] = VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF | VP8_EFLAG_NO_REF_GF ;
 layer_flags [ 4 ] = layer_flags [ 0 ] ;
 layer_flags [ 2 ] = VP8_EFLAG_NO_UPD_ARF | VP8_EFLAG_NO_UPD_LAST ;
 layer_flags [ 6 ] = layer_flags [ 2 ] ;
 layer_flags [ 1 ] = VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF | VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_ENTROPY ;
 layer_flags [ 3 ] = layer_flags [ 1 ] ;
 layer_flags [ 5 ] = layer_flags [ 1 ] ;
 layer_flags [ 7 ] = layer_flags [ 1 ] ;
 break ;
 }
 }
 }