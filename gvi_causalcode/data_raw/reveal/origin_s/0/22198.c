static vpx_codec_err_t extract_option ( LAYER_OPTION_TYPE type , char * input , int * value0 , int * value1 ) {
 if ( type == SCALE_FACTOR ) {
 * value0 = strtol ( input , & input , 10 ) ;
 if ( * input ++ != '/' ) return VPX_CODEC_INVALID_PARAM ;
 * value1 = strtol ( input , & input , 10 ) ;
 if ( * value0 < option_min_values [ SCALE_FACTOR ] || * value1 < option_min_values [ SCALE_FACTOR ] || * value0 > option_max_values [ SCALE_FACTOR ] || * value1 > option_max_values [ SCALE_FACTOR ] || * value0 > * value1 ) return VPX_CODEC_INVALID_PARAM ;
 }
 else {
 * value0 = atoi ( input ) ;
 if ( * value0 < option_min_values [ type ] || * value0 > option_max_values [ type ] ) return VPX_CODEC_INVALID_PARAM ;
 }
 return VPX_CODEC_OK ;
 }