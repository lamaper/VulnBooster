static void security_init ( void ) {
 uintptr_t stack_chk_guard = _dl_setup_stack_chk_guard ( _dl_random ) ;





 _dl_random = NULL ;
 }