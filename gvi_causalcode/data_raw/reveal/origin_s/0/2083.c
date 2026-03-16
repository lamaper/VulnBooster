static slurm_addr_t * _build_node_addr ( char * node_list , uint32_t node_cnt , uint32_t pack_job_id ) {
 hostlist_t host_list = NULL ;
 struct node_record * node_ptr ;
 slurm_addr_t * node_addr ;
 char * this_node_name ;
 int error_code = SLURM_SUCCESS , node_inx = 0 ;
 if ( ( host_list = hostlist_create ( node_list ) ) == NULL ) {
 error ( "%s hostlist_create error for pack job %u (%s): %m" , __func__ , pack_job_id , node_list ) ;
 return NULL ;
 }
 node_addr = xmalloc ( sizeof ( slurm_addr_t ) * node_cnt ) ;
 while ( ( this_node_name = hostlist_shift ( host_list ) ) ) {
 if ( ( node_ptr = find_node_record ( this_node_name ) ) ) {
 memcpy ( node_addr + node_inx , & node_ptr -> slurm_addr , sizeof ( slurm_addr_t ) ) ;
 node_inx ++ ;
 }
 else {
 error ( "%s: Invalid node %s in pack job %u" , __func__ , this_node_name , pack_job_id ) ;
 error_code = SLURM_ERROR ;
 }
 free ( this_node_name ) ;
 if ( error_code != SLURM_SUCCESS ) break ;
 }
 hostlist_destroy ( host_list ) ;
 if ( error_code != SLURM_SUCCESS ) xfree ( node_addr ) ;
 return node_addr ;
 }