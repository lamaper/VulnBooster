static void map_list ( OpenPICState * opp , const MemReg * list , int * count ) {
 while ( list -> name ) {
 assert ( * count < ARRAY_SIZE ( opp -> sub_io_mem ) ) ;
 memory_region_init_io ( & opp -> sub_io_mem [ * count ] , OBJECT ( opp ) , list -> ops , opp , list -> name , list -> size ) ;
 memory_region_add_subregion ( & opp -> mem , list -> start_addr , & opp -> sub_io_mem [ * count ] ) ;
 ( * count ) ++ ;
 list ++ ;
 }
 }