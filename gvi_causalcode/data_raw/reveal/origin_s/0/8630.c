static void AddTok ( GrowBuf * gb , char * buf , int islit ) {
 if ( islit ) GrowBufferAdd ( gb , '/' ) ;
 GrowBufferAddStr ( gb , buf ) ;
 GrowBufferAdd ( gb , ' ' ) ;
 }