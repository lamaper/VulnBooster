static void copy_frame ( AVFrame * f , const uint8_t * src , int width , int height ) {
 AVPicture pic ;
 avpicture_fill ( & pic , src , AV_PIX_FMT_YUV420P , width , height ) ;
 av_picture_copy ( ( AVPicture * ) f , & pic , AV_PIX_FMT_YUV420P , width , height ) ;
 }