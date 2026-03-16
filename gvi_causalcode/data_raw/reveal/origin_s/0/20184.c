static void par_list_remove ( TocEntry * te ) {
 te -> par_prev -> par_next = te -> par_next ;
 te -> par_next -> par_prev = te -> par_prev ;
 te -> par_prev = NULL ;
 te -> par_next = NULL ;
 }