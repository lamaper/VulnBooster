void ialloc_set_limit ( register gs_ref_memory_t * mem ) {
 ulong max_allocated = ( mem -> gc_status . max_vm > mem -> previous_status . allocated ? mem -> gc_status . max_vm - mem -> previous_status . allocated : 0 ) ;
 if ( mem -> gc_status . enabled ) {
 ulong limit = mem -> gc_allocated + mem -> gc_status . vm_threshold ;
 if ( limit < mem -> previous_status . allocated ) mem -> limit = 0 ;
 else {
 limit -= mem -> previous_status . allocated ;
 mem -> limit = min ( limit , max_allocated ) ;
 }
 }
 else mem -> limit = min ( max_allocated , mem -> gc_allocated + FORCE_GC_LIMIT ) ;
 if_debug7m ( '0' , ( const gs_memory_t * ) mem , "[0]space=%d, max_vm=%ld, prev.alloc=%ld, enabled=%d, " "gc_alloc=%ld, threshold=%ld => limit=%ld\n" , mem -> space , ( long ) mem -> gc_status . max_vm , ( long ) mem -> previous_status . allocated , mem -> gc_status . enabled , ( long ) mem -> gc_allocated , ( long ) mem -> gc_status . vm_threshold , ( long ) mem -> limit ) ;
 }