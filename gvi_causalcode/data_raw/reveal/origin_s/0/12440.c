static bool _tocEntryIsACL ( TocEntry * te ) {
 if ( strcmp ( te -> desc , "ACL" ) == 0 || strcmp ( te -> desc , "ACL LANGUAGE" ) == 0 || strcmp ( te -> desc , "DEFAULT ACL" ) == 0 ) return true ;
 return false ;
 }