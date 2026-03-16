int main_file_stat ( main_file * xfile , xoff_t * size ) {
 int ret = 0 ;

 return - 1 ;
 }

 LARGE_INTEGER li ;
 if ( GetFileSizeEx ( xfile -> file , & li ) == 0 ) {
 return get_errno ( ) ;
 }
 * size = li . QuadPart ;
 }

 DWORD filesize = GetFileSize ( xfile -> file , NULL ) ;
 if ( filesize == INVALID_FILE_SIZE ) {
 return get_errno ( ) }
 * size = filesize ;
 }

 if ( fstat ( XFNO ( xfile ) , & sbuf ) < 0 ) {
 ret = get_errno ( ) ;
 return ret ;
 }
 if ( ! S_ISREG ( sbuf . st_mode ) ) {
 return ESPIPE ;
 }
 ( * size ) = sbuf . st_size ;

 }