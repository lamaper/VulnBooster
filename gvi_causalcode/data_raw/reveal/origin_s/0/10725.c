static bfd_boolean srec_set_section_contents ( bfd * abfd , sec_ptr section , const void * location , file_ptr offset , bfd_size_type bytes_to_do ) {
 int opb = bfd_octets_per_byte ( abfd ) ;
 tdata_type * tdata = abfd -> tdata . srec_data ;
 srec_data_list_type * entry ;
 entry = ( srec_data_list_type * ) bfd_alloc ( abfd , sizeof ( * entry ) ) ;
 if ( entry == NULL ) return FALSE ;
 if ( bytes_to_do && ( section -> flags & SEC_ALLOC ) && ( section -> flags & SEC_LOAD ) ) {
 bfd_byte * data ;
 data = ( bfd_byte * ) bfd_alloc ( abfd , bytes_to_do ) ;
 if ( data == NULL ) return FALSE ;
 memcpy ( ( void * ) data , location , ( size_t ) bytes_to_do ) ;
 if ( S3Forced ) tdata -> type = 3 ;
 else if ( ( section -> lma + ( offset + bytes_to_do ) / opb - 1 ) <= 0xffff ) ;
 else if ( ( section -> lma + ( offset + bytes_to_do ) / opb - 1 ) <= 0xffffff && tdata -> type <= 2 ) tdata -> type = 2 ;
 else tdata -> type = 3 ;
 entry -> data = data ;
 entry -> where = section -> lma + offset / opb ;
 entry -> size = bytes_to_do ;
 if ( tdata -> tail != NULL && entry -> where >= tdata -> tail -> where ) {
 tdata -> tail -> next = entry ;
 entry -> next = NULL ;
 tdata -> tail = entry ;
 }
 else {
 srec_data_list_type * * look ;
 for ( look = & tdata -> head ;
 * look != NULL && ( * look ) -> where < entry -> where ;
 look = & ( * look ) -> next ) ;
 entry -> next = * look ;
 * look = entry ;
 if ( entry -> next == NULL ) tdata -> tail = entry ;
 }
 }
 return TRUE ;
 }