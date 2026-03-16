static bfd_boolean srec_write_terminator ( bfd * abfd , tdata_type * tdata ) {
 return srec_write_record ( abfd , 10 - tdata -> type , abfd -> start_address , NULL , NULL ) ;
 }