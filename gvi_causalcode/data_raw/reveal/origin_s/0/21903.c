void mem_get_initial_matrix ( gx_device * dev , gs_matrix * pmat ) {
 gx_device_memory * const mdev = ( gx_device_memory * ) dev ;
 pmat -> xx = mdev -> initial_matrix . xx ;
 pmat -> xy = mdev -> initial_matrix . xy ;
 pmat -> yx = mdev -> initial_matrix . yx ;
 pmat -> yy = mdev -> initial_matrix . yy ;
 pmat -> tx = mdev -> initial_matrix . tx ;
 pmat -> ty = mdev -> initial_matrix . ty ;
 }