int main_file_close ( main_file * xfile ) {
 int ret = 0 ;
 if ( ! main_file_isopen ( xfile ) ) {
 return 0 ;
 }

 xfile -> file = NULL ;

 xfile -> file = - 1 ;

 ret = get_errno ( ) ;
 }
 xfile -> file = INVALID_HANDLE_VALUE ;

 XF_ERROR ( "close" , xfile -> filename , ret = get_errno ( ) ) ;
 }
 return ret ;
 }