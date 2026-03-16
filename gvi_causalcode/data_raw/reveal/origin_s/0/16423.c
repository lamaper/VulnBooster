static void relocate_doit ( void * a ) {
 struct relocate_args * args = ( struct relocate_args * ) a ;
 _dl_relocate_object ( args -> l , args -> l -> l_scope , args -> reloc_mode , 0 ) ;
 }