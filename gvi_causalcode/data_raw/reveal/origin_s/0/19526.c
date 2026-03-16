static int is_slice_short ( struct dxva_context * ctx ) {
 assert ( ctx -> cfg -> ConfigBitstreamRaw == 1 || ctx -> cfg -> ConfigBitstreamRaw == 2 ) ;
 return ctx -> cfg -> ConfigBitstreamRaw == 2 ;
 }