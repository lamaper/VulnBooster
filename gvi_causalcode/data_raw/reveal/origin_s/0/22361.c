strong_alias ( __pointer_chk_guard_local , __pointer_chk_guard ) # endif static struct audit_list {
 const char * name ;
 struct audit_list * next ;
 }
 * audit_list ;

 rtld_hidden_def ( _dl_starting_up ) # endif struct rtld_global _rtld_global = {
 . _dl_stack_flags = DEFAULT_STACK_PERMS , # ifdef _LIBC_REENTRANT . _dl_load_lock = _RTLD_LOCK_RECURSIVE_INITIALIZER , . _dl_load_write_lock = _RTLD_LOCK_RECURSIVE_INITIALIZER , # endif . _dl_nns = 1 , . _dl_ns = {

 . _ns_unique_sym_table = {
 . lock = _RTLD_LOCK_RECURSIVE_INITIALIZER }
 }

 }