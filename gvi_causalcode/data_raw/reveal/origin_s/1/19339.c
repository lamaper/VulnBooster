int MBS_ReadHeader ( int fd , MBSPatchHeader * header ) {
 int s = read ( fd , header , sizeof ( MBSPatchHeader ) ) ;
 if ( s != sizeof ( MBSPatchHeader ) ) return READ_ERROR ;
 header -> slen = ntohl ( header -> slen ) ;
 header -> scrc32 = ntohl ( header -> scrc32 ) ;
 header -> dlen = ntohl ( header -> dlen ) ;
 header -> cblen = ntohl ( header -> cblen ) ;
 header -> difflen = ntohl ( header -> difflen ) ;
 header -> extralen = ntohl ( header -> extralen ) ;
 struct stat hs ;
 s = fstat ( fd , & hs ) ;
 if ( s ) return READ_ERROR ;
 if ( memcmp ( header -> tag , "MBDIFF10" , 8 ) != 0 ) return UNEXPECTED_ERROR ;
 if ( sizeof ( MBSPatchHeader ) + header -> cblen + header -> difflen + header -> extralen != int ( hs . st_size ) ) return UNEXPECTED_ERROR ;
 return OK ;
 }