static bfd_boolean srec_get_section_contents ( bfd * abfd , asection * section , void * location , file_ptr offset , bfd_size_type count ) {
 if ( count == 0 ) return TRUE ;
 if ( offset + count < count || offset + count > section -> size ) {
 bfd_set_error ( bfd_error_invalid_operation ) ;
 return FALSE ;
 }
 if ( section -> used_by_bfd == NULL ) {
 section -> used_by_bfd = bfd_alloc ( abfd , section -> size ) ;
 if ( section -> used_by_bfd == NULL ) return FALSE ;
 if ( ! srec_read_section ( abfd , section , ( bfd_byte * ) section -> used_by_bfd ) ) return FALSE ;
 }
 memcpy ( location , ( bfd_byte * ) section -> used_by_bfd + offset , ( size_t ) count ) ;
 return TRUE ;
 }