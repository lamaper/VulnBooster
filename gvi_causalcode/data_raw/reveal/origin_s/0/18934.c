int tm_atnode ( tm_task_id tid , tm_node_id * node ) {
 task_info * tp ;
 if ( ! init_done ) return TM_BADINIT ;
 if ( ( tp = find_task ( tid ) ) == NULL ) return TM_ENOTFOUND ;
 * node = tp -> t_node ;
 return TM_SUCCESS ;
 }