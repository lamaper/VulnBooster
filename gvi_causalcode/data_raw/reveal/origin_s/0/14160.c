static bool gn_to_string ( identification_t * id , char * * uri ) {
 int len ;

 chunk_printable ( id -> get_encoding ( id ) , & proper , '?' ) ;
 len = asprintf ( uri , "%.*s" , ( int ) proper . len , proper . ptr ) ;
 chunk_free ( & proper ) ;


 free ( * uri ) ;
 return FALSE ;
 }
 return len > 0 ;
 }