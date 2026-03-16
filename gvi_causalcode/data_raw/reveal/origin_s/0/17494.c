static void kvm_unpoison_all ( void * param ) {
 HWPoisonPage * page , * next_page ;
 QLIST_FOREACH_SAFE ( page , & hwpoison_page_list , list , next_page ) {
 QLIST_REMOVE ( page , list ) ;
 qemu_ram_remap ( page -> ram_addr , TARGET_PAGE_SIZE ) ;
 g_free ( page ) ;
 }
 }