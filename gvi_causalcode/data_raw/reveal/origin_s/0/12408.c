int NumRelids ( Node * clause ) {
 Relids varnos = pull_varnos ( clause ) ;
 int result = bms_num_members ( varnos ) ;
 bms_free ( varnos ) ;
 return result ;
 }