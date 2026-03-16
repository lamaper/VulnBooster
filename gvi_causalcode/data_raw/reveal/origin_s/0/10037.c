static void qcms_transform_module_XYZ_to_LAB ( struct qcms_modular_transform * transform , float * src , float * dest , size_t length ) {
 size_t i ;
 float WhitePointX = 0.9642f ;
 float WhitePointY = 1.0f ;
 float WhitePointZ = 0.8249f ;
 for ( i = 0 ;
 i < length ;
 i ++ ) {
 float device_x = * src ++ * ( 1.0 + 32767.0 / 32768.0 ) / WhitePointX ;
 float device_y = * src ++ * ( 1.0 + 32767.0 / 32768.0 ) / WhitePointY ;
 float device_z = * src ++ * ( 1.0 + 32767.0 / 32768.0 ) / WhitePointZ ;
 float fx = f ( device_x ) ;
 float fy = f ( device_y ) ;
 float fz = f ( device_z ) ;
 float L = 116.0f * fy - 16.0f ;
 float a = 500.0f * ( fx - fy ) ;
 float b = 200.0f * ( fy - fz ) ;
 * dest ++ = L / 100.0f ;
 * dest ++ = ( a + 128.0f ) / 255.0f ;
 * dest ++ = ( b + 128.0f ) / 255.0f ;
 }
 }