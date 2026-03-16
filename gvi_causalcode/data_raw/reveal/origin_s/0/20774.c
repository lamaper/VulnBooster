static bfd_boolean srec_write_section ( bfd * abfd , tdata_type * tdata , srec_data_list_type * list ) {
 unsigned int octets_written = 0 ;
 bfd_byte * location = list -> data ;
 if ( Chunk == 0 ) Chunk = 1 ;
 else if ( Chunk > MAXCHUNK - tdata -> type - 2 ) Chunk = MAXCHUNK - tdata -> type - 2 ;
 while ( octets_written < list -> size ) {
 bfd_vma address ;
 unsigned int octets_this_chunk = list -> size - octets_written ;
 if ( octets_this_chunk > Chunk ) octets_this_chunk = Chunk ;
 address = list -> where + octets_written / bfd_octets_per_byte ( abfd ) ;
 if ( ! srec_write_record ( abfd , tdata -> type , address , location , location + octets_this_chunk ) ) return FALSE ;
 octets_written += octets_this_chunk ;
 location += octets_this_chunk ;
 }
 return TRUE ;
 }