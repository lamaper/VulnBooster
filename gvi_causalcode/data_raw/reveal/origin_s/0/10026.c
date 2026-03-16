static void fill_slice_short ( DXVA_Slice_H264_Short * slice , unsigned position , unsigned size ) {
 memset ( slice , 0 , sizeof ( * slice ) ) ;
 slice -> BSNALunitDataLocation = position ;
 slice -> SliceBytesInBuffer = size ;
 slice -> wBadSliceChopping = 0 ;
 }