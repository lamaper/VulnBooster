static int main_file_seek ( main_file * xfile , xoff_t pos ) {
 int ret = 0 ;

 ret = get_errno ( ) ;
 }

 ret = get_errno ( ) ;
 }

 move . QuadPart = pos ;
 if ( SetFilePointerEx ( xfile -> file , move , & out , FILE_BEGIN ) == 0 ) {
 ret = get_errno ( ) ;
 }

 ret = get_errno ( ) ;
 }

 }