size_t qcms_profile_get_parametric_curve ( qcms_profile * profile , qcms_trc_channel channel , float data [ 7 ] ) {
 static const uint32_t COUNT_TO_LENGTH [ 5 ] = {
 1 , 3 , 4 , 5 , 7 }
 ;
 struct curveType * curve = NULL ;
 size_t size ;
 if ( profile -> color_space != RGB_SIGNATURE ) return 0 ;
 switch ( channel ) {
 case QCMS_TRC_RED : curve = profile -> redTRC ;
 break ;
 case QCMS_TRC_GREEN : curve = profile -> greenTRC ;
 break ;
 case QCMS_TRC_BLUE : curve = profile -> blueTRC ;
 break ;
 default : return 0 ;
 }
 if ( ! curve || curve -> type != PARAMETRIC_CURVE_TYPE ) return 0 ;
 size = COUNT_TO_LENGTH [ curve -> count ] ;
 if ( data ) memcpy ( data , curve -> parameter , size * sizeof ( float ) ) ;
 return size ;
 }