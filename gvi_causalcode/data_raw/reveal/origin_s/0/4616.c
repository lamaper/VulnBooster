static bool message_search_more_decoded2 ( struct message_search_context * ctx , struct message_block * block ) {
 if ( block -> hdr != NULL ) {
 if ( search_header ( ctx , block -> hdr ) ) return TRUE ;
 }
 else {
 if ( str_find_more ( ctx -> str_find_ctx , block -> data , block -> size ) ) return TRUE ;
 }
 return FALSE ;
 }