const unsigned char * fz_lookup_icc ( fz_context * ctx , const char * name , size_t * size ) {

 if ( ! strcmp ( name , FZ_ICC_PROFILE_GRAY ) ) {
 extern const int fz_resources_icc_gray_icc_size ;
 extern const unsigned char fz_resources_icc_gray_icc [ ] ;
 * size = fz_resources_icc_gray_icc_size ;
 return fz_resources_icc_gray_icc ;
 }
 if ( ! strcmp ( name , FZ_ICC_PROFILE_RGB ) || ! strcmp ( name , FZ_ICC_PROFILE_BGR ) ) {
 extern const int fz_resources_icc_rgb_icc_size ;
 extern const unsigned char fz_resources_icc_rgb_icc [ ] ;
 * size = fz_resources_icc_rgb_icc_size ;
 return fz_resources_icc_rgb_icc ;
 }
 if ( ! strcmp ( name , FZ_ICC_PROFILE_CMYK ) ) {
 extern const int fz_resources_icc_cmyk_icc_size ;
 extern const unsigned char fz_resources_icc_cmyk_icc [ ] ;
 * size = fz_resources_icc_cmyk_icc_size ;
 return fz_resources_icc_cmyk_icc ;
 }
 if ( ! strcmp ( name , FZ_ICC_PROFILE_LAB ) ) {
 extern const int fz_resources_icc_lab_icc_size ;
 extern const unsigned char fz_resources_icc_lab_icc [ ] ;
 * size = fz_resources_icc_lab_icc_size ;
 return fz_resources_icc_lab_icc ;
 }

 }