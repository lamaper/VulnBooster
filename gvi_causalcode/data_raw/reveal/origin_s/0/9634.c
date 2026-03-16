static void copy_picture_attributes ( MpegEncContext * s , AVFrame * dst , const AVFrame * src ) {
 dst -> pict_type = src -> pict_type ;
 dst -> quality = src -> quality ;
 dst -> coded_picture_number = src -> coded_picture_number ;
 dst -> display_picture_number = src -> display_picture_number ;
 dst -> pts = src -> pts ;
 dst -> interlaced_frame = src -> interlaced_frame ;
 dst -> top_field_first = src -> top_field_first ;
 }