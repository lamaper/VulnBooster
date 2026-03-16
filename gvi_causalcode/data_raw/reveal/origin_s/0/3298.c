int main_file_read ( main_file * ifile , uint8_t * buf , size_t size , size_t * nread , const char * msg ) {
 int ret = 0 ;

 result = fread ( buf , 1 , size , ifile -> file ) ;
 if ( result < size && ferror ( ifile -> file ) ) {
 ret = get_errno ( ) ;
 }
 else {
 * nread = result ;
 }



 XPR ( NT "%s: %s: %s\n" , msg , ifile -> filename , xd3_mainerror ( ret ) ) ;
 }
 else {
 if ( option_verbose > 4 ) {
 XPR ( NT "read %s: %zu bytes\n" , ifile -> filename , ( * nread ) ) ;
 }
 ifile -> nread += ( * nread ) ;
 }
 return ret ;
 }