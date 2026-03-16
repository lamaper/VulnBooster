static bool pickoneauth ( struct auth * pick ) {
 bool picked ;
 unsigned long avail = pick -> avail & pick -> want ;
 picked = TRUE ;
 if ( avail & CURLAUTH_NEGOTIATE ) pick -> picked = CURLAUTH_NEGOTIATE ;
 else if ( avail & CURLAUTH_DIGEST ) pick -> picked = CURLAUTH_DIGEST ;
 else if ( avail & CURLAUTH_NTLM ) pick -> picked = CURLAUTH_NTLM ;
 else if ( avail & CURLAUTH_NTLM_WB ) pick -> picked = CURLAUTH_NTLM_WB ;
 else if ( avail & CURLAUTH_BASIC ) pick -> picked = CURLAUTH_BASIC ;
 else {
 pick -> picked = CURLAUTH_PICKNONE ;
 picked = FALSE ;
 }
 pick -> avail = CURLAUTH_NONE ;
 return picked ;
 }