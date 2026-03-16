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
 if ( s != 0 ) return READ_ERROR ;
 if ( memcmp ( header -> tag , "MBDIFF10" , 8 ) != 0 ) return UNEXPECTED_ERROR ;
 if ( hs . st_size > INT_MAX ) return UNEXPECTED_ERROR ;
 size_t size = static_cast < size_t > ( hs . st_size ) ;
 if ( size < sizeof ( MBSPatchHeader ) ) return UNEXPECTED_ERROR ;
 size -= sizeof ( MBSPatchHeader ) ;
 if ( size < header -> cblen ) return UNEXPECTED_ERROR ;
 size -= header -> cblen ;
 if ( size < header -> difflen ) return UNEXPECTED_ERROR ;
 size -= header -> difflen ;
 if ( size < header -> extralen ) return UNEXPECTED_ERROR ;
 size -= header -> extralen ;
 if ( size != 0 ) return UNEXPECTED_ERROR ;
 return OK ;
 }