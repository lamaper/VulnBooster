static void _update_cred_key ( void ) {
 slurm_cred_ctx_key_update ( slurmctld_config . cred_ctx , slurmctld_conf . job_credential_private_key ) ;
 }