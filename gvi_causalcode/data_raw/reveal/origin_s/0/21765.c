static int qcow2_read_extensions ( BlockDriverState * bs , uint64_t start_offset , uint64_t end_offset , void * * p_feature_table , Error * * errp ) {
 BDRVQcowState * s = bs -> opaque ;
 QCowExtension ext ;
 uint64_t offset ;
 int ret ;


 while ( offset < end_offset ) {

 printf ( "attempting to read extended header in offset %lu\n" , offset ) ;

 if ( ret < 0 ) {
 error_setg_errno ( errp , - ret , "qcow2_read_extension: ERROR: " "pread fail from offset %" PRIu64 , offset ) ;
 return 1 ;
 }
 be32_to_cpus ( & ext . magic ) ;
 be32_to_cpus ( & ext . len ) ;
 offset += sizeof ( ext ) ;


 error_setg ( errp , "Header extension too large" ) ;
 return - EINVAL ;
 }
 switch ( ext . magic ) {
 case QCOW2_EXT_MAGIC_END : return 0 ;
 case QCOW2_EXT_MAGIC_BACKING_FORMAT : if ( ext . len >= sizeof ( bs -> backing_format ) ) {
 error_setg ( errp , "ERROR: ext_backing_format: len=%u too large" " (>=%zu)" , ext . len , sizeof ( bs -> backing_format ) ) ;
 return 2 ;
 }
 ret = bdrv_pread ( bs -> file , offset , bs -> backing_format , ext . len ) ;
 if ( ret < 0 ) {
 error_setg_errno ( errp , - ret , "ERROR: ext_backing_format: " "Could not read format name" ) ;
 return 3 ;
 }
 bs -> backing_format [ ext . len ] = '\0' ;


 case QCOW2_EXT_MAGIC_FEATURE_TABLE : if ( p_feature_table != NULL ) {
 void * feature_table = g_malloc0 ( ext . len + 2 * sizeof ( Qcow2Feature ) ) ;
 ret = bdrv_pread ( bs -> file , offset , feature_table , ext . len ) ;
 if ( ret < 0 ) {
 error_setg_errno ( errp , - ret , "ERROR: ext_feature_table: " "Could not read table" ) ;
 return ret ;
 }
 * p_feature_table = feature_table ;
 }
 break ;
 default : {
 Qcow2UnknownHeaderExtension * uext ;
 uext = g_malloc0 ( sizeof ( * uext ) + ext . len ) ;
 uext -> magic = ext . magic ;
 uext -> len = ext . len ;
 QLIST_INSERT_HEAD ( & s -> unknown_header_ext , uext , next ) ;
 ret = bdrv_pread ( bs -> file , offset , uext -> data , uext -> len ) ;
 if ( ret < 0 ) {
 error_setg_errno ( errp , - ret , "ERROR: unknown extension: " "Could not read data" ) ;
 return ret ;
 }
 }
 break ;
 }
 offset += ( ( ext . len + 7 ) & ~ 7 ) ;
 }
 return 0 ;
 }