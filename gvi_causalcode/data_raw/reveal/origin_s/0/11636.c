int main_file_write ( main_file * ofile , uint8_t * buf , usize_t size , const char * msg ) {
 int ret = 0 ;

 result = fwrite ( buf , 1 , size , ofile -> file ) ;
 if ( result != size ) {
 ret = get_errno ( ) ;
 }



 XPR ( NT "%s: %s: %s\n" , msg , ofile -> filename , xd3_mainerror ( ret ) ) ;
 }
 else {
 if ( option_verbose > 5 ) {
 XPR ( NT "write %s: %u bytes\n" , ofile -> filename , size ) ;
 }
 ofile -> nwrite += size ;
 }
 return ret ;
 }