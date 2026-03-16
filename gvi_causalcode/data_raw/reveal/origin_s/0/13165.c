static int match_version ( const char * string , struct link_map * map ) {
 const char * strtab = ( const void * ) D_PTR ( map , l_info [ DT_STRTAB ] ) ;
 ElfW ( Verdef ) * def ;

 def = ( ElfW ( Verdef ) * ) ( ( char * ) map -> l_addr + map -> l_info [ VERDEFTAG ] -> d_un . d_ptr ) ;
 while ( 1 ) {
 ElfW ( Verdaux ) * aux = ( ElfW ( Verdaux ) * ) ( ( char * ) def + def -> vd_aux ) ;
 if ( strcmp ( string , strtab + aux -> vda_name ) == 0 ) return 1 ;
 if ( def -> vd_next == 0 ) break ;
 def = ( ElfW ( Verdef ) * ) ( ( char * ) def + def -> vd_next ) ;
 }
 return 0 ;
 }