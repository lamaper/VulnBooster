static int restore_time ( struct cpio * cpio , struct archive_entry * entry , const char * name , int fd ) {

 ( void ) cpio ;
 ( void ) entry ;
 ( void ) name ;
 if ( ! warned ) lafe_warnc ( 0 , "Can't restore access times on this platform" ) ;
 warned = 1 ;
 return ( fd ) ;



 times [ 1 ] . tv_sec = archive_entry_mtime ( entry ) ;
 times [ 1 ] . tv_usec = archive_entry_mtime_nsec ( entry ) / 1000 ;
 times [ 0 ] . tv_sec = archive_entry_atime ( entry ) ;
 times [ 0 ] . tv_usec = archive_entry_atime_nsec ( entry ) / 1000 ;


 close ( fd ) ;
 fd = - 1 ;
 }


 }