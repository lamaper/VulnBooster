void qmp_pmemsave ( int64_t addr , int64_t size , const char * filename , Error * * errp ) {
 FILE * f ;
 uint32_t l ;
 uint8_t buf [ 1024 ] ;
 f = fopen ( filename , "wb" ) ;
 if ( ! f ) {
 error_setg_file_open ( errp , errno , filename ) ;
 return ;
 }
 while ( size != 0 ) {
 l = sizeof ( buf ) ;
 if ( l > size ) l = size ;
 cpu_physical_memory_rw ( addr , buf , l , 0 ) ;
 if ( fwrite ( buf , 1 , l , f ) != l ) {
 error_set ( errp , QERR_IO_ERROR ) ;
 goto exit ;
 }
 addr += l ;
 size -= l ;
 }
 exit : fclose ( f ) ;
 }