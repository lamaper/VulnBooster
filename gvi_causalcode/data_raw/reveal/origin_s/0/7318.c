int evbuffer_add_buffer ( struct evbuffer * outbuf , struct evbuffer * inbuf ) {
 int res ;
 if ( outbuf -> off == 0 ) {
 struct evbuffer tmp ;
 size_t oldoff = inbuf -> off ;
 SWAP ( & tmp , outbuf ) ;
 SWAP ( outbuf , inbuf ) ;
 SWAP ( inbuf , & tmp ) ;
 if ( inbuf -> off != oldoff && inbuf -> cb != NULL ) ( * inbuf -> cb ) ( inbuf , oldoff , inbuf -> off , inbuf -> cbarg ) ;
 if ( oldoff && outbuf -> cb != NULL ) ( * outbuf -> cb ) ( outbuf , 0 , oldoff , outbuf -> cbarg ) ;
 return ( 0 ) ;
 }
 res = evbuffer_add ( outbuf , inbuf -> buffer , inbuf -> off ) ;
 if ( res == 0 ) {
 evbuffer_drain ( inbuf , inbuf -> off ) ;
 }
 return ( res ) ;
 }