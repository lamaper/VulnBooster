TSFile TSfopen ( const char * filename , const char * mode ) {
 FileImpl * file ;
 file = new FileImpl ;
 if ( ! file -> fopen ( filename , mode ) ) {
 delete file ;
 return nullptr ;
 }
 return ( TSFile ) file ;
 }