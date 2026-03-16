static int __attribute_noinline__ link_exists2_p ( const char * dir , size_t dirlen , const char * fname , glob_t * pglob # ifndef _LIBC , int flags # endif ) {
 size_t fnamelen = strlen ( fname ) ;
 char * fullname = ( char * ) __alloca ( dirlen + 1 + fnamelen + 1 ) ;
 struct stat st ;




