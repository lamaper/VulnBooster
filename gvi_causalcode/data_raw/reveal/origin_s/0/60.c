void gx_device_copy_params ( gx_device * dev , const gx_device * target ) {

 COPY_PARAM ( height ) ;
 COPY_ARRAY_PARAM ( MediaSize ) ;
 COPY_ARRAY_PARAM ( ImagingBBox ) ;
 COPY_PARAM ( ImagingBBox_set ) ;
 COPY_ARRAY_PARAM ( HWResolution ) ;
 COPY_ARRAY_PARAM ( Margins ) ;
 COPY_ARRAY_PARAM ( HWMargins ) ;
 COPY_PARAM ( PageCount ) ;
 COPY_PARAM ( MaxPatternBitmap ) ;

 }