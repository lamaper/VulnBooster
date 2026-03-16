static int vmdk_is_cid_valid(BlockDriverState *bs)

{


    BDRVVmdkState *s = bs->opaque;

    BlockDriverState *p_bs = bs->backing_hd;

    uint32_t cur_pcid;



    if (p_bs) {

        cur_pcid = vmdk_read_cid(p_bs, 0);

        if (s->parent_cid != cur_pcid) {

             

            return 0;

        }

    }


     

    return 1;

}
