bool checkSeek ( FILE * fp ) {
 pgoff_t tpos ;


 if ( tpos < 0 ) return false ;
 if ( fseeko ( fp , tpos , SEEK_SET ) != 0 ) return false ;
 return true ;
 }