void vp9_model_to_full_probs ( const vp9_prob * model , vp9_prob * full ) {
 if ( full != model ) vpx_memcpy ( full , model , sizeof ( vp9_prob ) * UNCONSTRAINED_NODES ) ;
 extend_to_full_distribution ( & full [ UNCONSTRAINED_NODES ] , model [ PIVOT_NODE ] ) ;
 }