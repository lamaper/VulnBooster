static void extend_to_full_distribution ( vp9_prob * probs , vp9_prob p ) {
 vpx_memcpy ( probs , vp9_pareto8_full [ p = 0 ? 0 : p - 1 ] , MODEL_NODES * sizeof ( vp9_prob ) ) ;
 }