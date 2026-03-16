FILE * __setmntent ( const char * file , const char * mode ) {
 size_t modelen = strlen ( mode ) ;
 char newmode [ modelen + 2 ] ;
 memcpy ( mempcpy ( newmode , mode , modelen ) , "c" , 2 ) ;
 FILE * result = fopen ( file , newmode ) ;
 if ( result != NULL ) __fsetlocking ( result , FSETLOCKING_BYCALLER ) ;
 return result ;
 }