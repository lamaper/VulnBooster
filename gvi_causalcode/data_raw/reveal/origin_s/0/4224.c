static void qcms_transform_module_LAB_to_XYZ ( struct qcms_modular_transform * transform , float * src , float * dest , size_t length ) {
 size_t i ;
 float WhitePointX = 0.9642f ;
 float WhitePointY = 1.0f ;
 float WhitePointZ = 0.8249f ;
 for ( i = 0 ;
 i < length ;
 i ++ ) {
 float device_L = * src ++ * 100.0f ;
 float device_a = * src ++ * 255.0f - 128.0f ;
 float device_b = * src ++ * 255.0f - 128.0f ;
 float y = ( device_L + 16.0f ) / 116.0f ;
 float X = f_1 ( ( y + 0.002f * device_a ) ) * WhitePointX ;
 float Y = f_1 ( y ) * WhitePointY ;
 float Z = f_1 ( ( y - 0.005f * device_b ) ) * WhitePointZ ;
 * dest ++ = X / ( 1.0 + 32767.0 / 32768.0 ) ;
 * dest ++ = Y / ( 1.0 + 32767.0 / 32768.0 ) ;
 * dest ++ = Z / ( 1.0 + 32767.0 / 32768.0 ) ;
 }
 }