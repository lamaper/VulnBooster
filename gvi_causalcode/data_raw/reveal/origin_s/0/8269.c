static bool GetNaClVariantRoot ( const base : : FilePath : : StringType & variant , base : : FilePath * document_root ) {
 if ( ! ui_test_utils : : GetRelativeBuildDirectory ( document_root ) ) return false ;
 * document_root = document_root -> Append ( FILE_PATH_LITERAL ( "nacl_test_data" ) ) ;
 * document_root = document_root -> Append ( variant ) ;
 return true ;
 }