void ff_mpeg12_common_init ( MpegEncContext * s ) {
 s -> y_dc_scale_table = s -> c_dc_scale_table = ff_mpeg2_dc_scale_table [ s -> intra_dc_precision ] ;
 }