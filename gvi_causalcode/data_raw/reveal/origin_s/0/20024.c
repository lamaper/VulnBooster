int ialloc_add_clump ( gs_ref_memory_t * imem , ulong space , client_name_t cname ) {
 clump_t * cp ;
 imem -> is_controlled = false ;
 imem -> large_size = imem -> clump_size ;
 imem -> limit = max_long ;
 imem -> gc_status . max_vm = max_long ;
 cp = alloc_add_clump ( imem , space , cname ) ;
 imem -> procs . alloc_bytes_immovable = imem -> procs . alloc_bytes ;
 imem -> procs . alloc_struct_immovable = imem -> procs . alloc_struct ;
 imem -> procs . alloc_byte_array_immovable = imem -> procs . alloc_byte_array ;
 imem -> procs . alloc_struct_array_immovable = imem -> procs . alloc_struct_array ;
 imem -> procs . alloc_string_immovable = imem -> procs . alloc_string ;
 imem -> is_controlled = true ;
 imem -> limit = 0 ;
 return ( cp ? 0 : gs_note_error ( gs_error_VMerror ) ) ;
 }