static int _valid_id ( char * caller , job_desc_msg_t * msg , uid_t uid , gid_t gid ) {
 if ( validate_slurm_user ( uid ) ) return SLURM_SUCCESS ;
 if ( uid != msg -> user_id ) {
 error ( "%s: Requested UID=%u doesn't match user UID=%u." , caller , msg -> user_id , uid ) ;
 return ESLURM_USER_ID_MISSING ;
 }
 if ( gid != msg -> group_id ) {
 error ( "%s: Requested GID=%u doesn't match user GID=%u." , caller , msg -> group_id , gid ) ;
 return ESLURM_GROUP_ID_MISSING ;
 }
 return SLURM_SUCCESS ;
 }