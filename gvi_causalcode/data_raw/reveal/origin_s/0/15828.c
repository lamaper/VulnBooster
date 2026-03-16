static bool MakeTempFile ( const base : : FilePath & dir , const base : : FilePath & file_name , base : : FilePath * full_path ) {
 * full_path = dir . Append ( file_name ) ;
 return base : : WriteFile ( * full_path , "" , 0 ) == 0 ;
 }