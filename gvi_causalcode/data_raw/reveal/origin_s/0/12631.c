unsigned int srtp_profile_get_master_key_length ( srtp_profile_t profile ) {
 switch ( profile ) {
 case srtp_profile_aes128_cm_sha1_80 : return 16 ;
 break ;
 case srtp_profile_aes128_cm_sha1_32 : return 16 ;
 break ;
 case srtp_profile_null_sha1_80 : return 16 ;
 break ;
 case srtp_profile_aes256_cm_sha1_80 : return 32 ;
 break ;
 case srtp_profile_aes256_cm_sha1_32 : return 32 ;
 break ;
 case srtp_profile_null_sha1_32 : default : return 0 ;
 }
 }