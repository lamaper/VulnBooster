static void AddPnaclParm ( const base : : FilePath : : StringType & url , base : : FilePath : : StringType * url_with_parm ) {
 if ( url . find ( FILE_PATH_LITERAL ( "?" ) ) == base : : FilePath : : StringType : : npos ) {
 * url_with_parm = url + FILE_PATH_LITERAL ( "?pnacl=1" ) ;
 }
 else {
 * url_with_parm = url + FILE_PATH_LITERAL ( "&pnacl=1" ) ;
 }
 }