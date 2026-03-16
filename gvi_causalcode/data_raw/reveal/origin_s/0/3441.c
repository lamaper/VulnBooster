static void par_list_append ( TocEntry * l , TocEntry * te ) {
 te -> par_prev = l -> par_prev ;
 l -> par_prev -> par_next = te ;
 l -> par_prev = te ;
 te -> par_next = l ;
 }