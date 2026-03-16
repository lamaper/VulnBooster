struct archive_wstring * archive_wstrcat ( struct archive_wstring * as , const wchar_t * p ) {
 return archive_wstrncat ( as , p , 0x1000000 ) ;
 }