static int compareFiles ( const void * file1 , const void * file2 ) {
 return uprv_strcmp ( ( ( File * ) file1 ) -> basename , ( ( File * ) file2 ) -> basename ) ;
 }