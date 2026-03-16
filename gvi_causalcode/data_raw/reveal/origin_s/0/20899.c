static int zvmstatus ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 gs_memory_status_t mstat , dstat ;
 gs_memory_status ( imemory , & mstat ) ;
 if ( imemory == imemory_global ) {
 gs_memory_status_t sstat ;
 gs_memory_status ( imemory_system , & sstat ) ;
 mstat . allocated += sstat . allocated ;
 mstat . used += sstat . used ;
 }
 gs_memory_status ( imemory -> non_gc_memory , & dstat ) ;
 push ( 3 ) ;
 make_int ( op - 2 , imemory_save_level ( iimemory_local ) ) ;
 make_int ( op - 1 , mstat . used ) ;
 make_int ( op , mstat . allocated + dstat . allocated - dstat . used ) ;
 return 0 ;
 }