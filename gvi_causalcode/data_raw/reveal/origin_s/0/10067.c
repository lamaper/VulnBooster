static bool IsMatchingFileURL ( const std : : string & url , const base : : FilePath & full_file_path ) {
 if ( url . length ( ) <= 8 ) return false ;
 if ( std : : string ( "file:///" ) != url . substr ( 0 , 8 ) ) return false ;
 if ( url . find ( '\\' ) != std : : string : : npos ) return false ;
 base : : FilePath derived_path ;
 net : : FileURLToFilePath ( GURL ( url ) , & derived_path ) ;
 return base : : FilePath : : CompareEqualIgnoreCase ( derived_path . value ( ) , full_file_path . value ( ) ) ;
 }