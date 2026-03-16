int main_file_open ( main_file * xfile , const char * name , int mode ) {
 int ret = 0 ;
 xfile -> mode = mode ;
 XD3_ASSERT ( name != NULL ) ;
 XD3_ASSERT ( ! main_file_isopen ( xfile ) ) ;
 if ( name [ 0 ] == 0 ) {
 XPR ( NT "invalid file name: empty string\n" ) ;
 return XD3_INVALID ;
 }

 ret = ( xfile -> file == NULL ) ? get_errno ( ) : 0 ;

 ret = get_errno ( ) ;
 }
 else {
 xfile -> file = ret ;
 ret = 0 ;
 }

 if ( xfile -> file == INVALID_HANDLE_VALUE ) {
 ret = get_errno ( ) ;
 }

 XF_ERROR ( "open" , name , ret ) ;
 }
 else {
 xfile -> realname = name ;
 xfile -> nread = 0 ;
 }
 return ret ;
 }