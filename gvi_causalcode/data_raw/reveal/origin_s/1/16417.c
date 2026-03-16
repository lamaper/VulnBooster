static void security_init ( void ) {
 uintptr_t stack_chk_guard = _dl_setup_stack_chk_guard ( _dl_random ) ;



 uintptr_t pointer_chk_guard = _dl_setup_pointer_guard ( _dl_random , stack_chk_guard ) ;


 }
 _dl_random = NULL ;
 }