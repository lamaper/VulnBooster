static void register_smram_listener ( Notifier * n , void * unused ) {
 MemoryRegion * smram = ( MemoryRegion * ) object_resolve_path ( "/machine/smram" , NULL ) ;
 memory_region_init ( & smram_as_root , OBJECT ( kvm_state ) , "mem-container-smram" , ~ 0ull ) ;
 memory_region_set_enabled ( & smram_as_root , true ) ;
 memory_region_init_alias ( & smram_as_mem , OBJECT ( kvm_state ) , "mem-smram" , get_system_memory ( ) , 0 , ~ 0ull ) ;
 memory_region_add_subregion_overlap ( & smram_as_root , 0 , & smram_as_mem , 0 ) ;
 memory_region_set_enabled ( & smram_as_mem , true ) ;
 if ( smram ) {
 memory_region_add_subregion_overlap ( & smram_as_root , 0 , smram , 10 ) ;
 memory_region_set_enabled ( smram , true ) ;
 }
 address_space_init ( & smram_address_space , & smram_as_root , "KVM-SMRAM" ) ;
 kvm_memory_listener_register ( kvm_state , & smram_listener , & smram_address_space , 1 ) ;
 }