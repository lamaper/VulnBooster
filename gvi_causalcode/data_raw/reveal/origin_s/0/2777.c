static void fill_picture_entry ( DXVA_PicEntry_H264 * pic , unsigned index , unsigned flag ) {
 assert ( ( index & 0x7f ) == index && ( flag & 0x01 ) == flag ) ;
 pic -> bPicEntry = index | ( flag << 7 ) ;
 }