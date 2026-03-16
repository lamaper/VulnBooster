static void decode_postinit(H264Context *h, int setup_finished)

{

    H264Picture *out = h->cur_pic_ptr;

    H264Picture *cur = h->cur_pic_ptr;

    int i, pics, out_of_order, out_idx;

    int invalid = 0, cnt = 0;



    h->cur_pic_ptr->f->pict_type = h->pict_type;



    if (h->next_output_pic)

        return;



    if (cur->field_poc[0] == INT_MAX || cur->field_poc[1] == INT_MAX) {

         

         

         

        return;

    }



    cur->f->interlaced_frame = 0;

    cur->f->repeat_pict      = 0;



     

     



    if (h->sps.pic_struct_present_flag) {

        switch (h->sei_pic_struct) {

        case SEI_PIC_STRUCT_FRAME:

            break;

        case SEI_PIC_STRUCT_TOP_FIELD:

        case SEI_PIC_STRUCT_BOTTOM_FIELD:

            cur->f->interlaced_frame = 1;

            break;

        case SEI_PIC_STRUCT_TOP_BOTTOM:

        case SEI_PIC_STRUCT_BOTTOM_TOP:

            if (FIELD_OR_MBAFF_PICTURE(h))

                cur->f->interlaced_frame = 1;

            else

                 

                cur->f->interlaced_frame = h->prev_interlaced_frame;

            break;

        case SEI_PIC_STRUCT_TOP_BOTTOM_TOP:

        case SEI_PIC_STRUCT_BOTTOM_TOP_BOTTOM:

             

            cur->f->repeat_pict = 1;

            break;

        case SEI_PIC_STRUCT_FRAME_DOUBLING:

            cur->f->repeat_pict = 2;

            break;

        case SEI_PIC_STRUCT_FRAME_TRIPLING:

            cur->f->repeat_pict = 4;

            break;

        }



        if ((h->sei_ct_type & 3) &&

            h->sei_pic_struct <= SEI_PIC_STRUCT_BOTTOM_TOP)

            cur->f->interlaced_frame = (h->sei_ct_type & (1 << 1)) != 0;

    } else {

         

        cur->f->interlaced_frame = FIELD_OR_MBAFF_PICTURE(h);

    }

    h->prev_interlaced_frame = cur->f->interlaced_frame;



    if (cur->field_poc[0] != cur->field_poc[1]) {

         

        cur->f->top_field_first = cur->field_poc[0] < cur->field_poc[1];

    } else {

        if (cur->f->interlaced_frame || h->sps.pic_struct_present_flag) {

             

            if (h->sei_pic_struct == SEI_PIC_STRUCT_TOP_BOTTOM ||

                h->sei_pic_struct == SEI_PIC_STRUCT_TOP_BOTTOM_TOP)

                cur->f->top_field_first = 1;

            else

                cur->f->top_field_first = 0;

        } else {

             

            cur->f->top_field_first = 0;

        }

    }



    if (h->sei_frame_packing_present &&

        h->frame_packing_arrangement_type >= 0 &&

        h->frame_packing_arrangement_type <= 6 &&

        h->content_interpretation_type > 0 &&

        h->content_interpretation_type < 3) {

        AVStereo3D *stereo = av_stereo3d_create_side_data(cur->f);

        if (!stereo)

            return;



        switch (h->frame_packing_arrangement_type) {

        case 0:

            stereo->type = AV_STEREO3D_CHECKERBOARD;

            break;

        case 1:

            stereo->type = AV_STEREO3D_COLUMNS;

            break;

        case 2:

            stereo->type = AV_STEREO3D_LINES;

            break;

        case 3:

            if (h->quincunx_subsampling)

                stereo->type = AV_STEREO3D_SIDEBYSIDE_QUINCUNX;

            else

                stereo->type = AV_STEREO3D_SIDEBYSIDE;

            break;

        case 4:

            stereo->type = AV_STEREO3D_TOPBOTTOM;

            break;

        case 5:

            stereo->type = AV_STEREO3D_FRAMESEQUENCE;

            break;

        case 6:

            stereo->type = AV_STEREO3D_2D;

            break;

        }



        if (h->content_interpretation_type == 2)

            stereo->flags = AV_STEREO3D_FLAG_INVERT;

    }



    if (h->sei_display_orientation_present &&

        (h->sei_anticlockwise_rotation || h->sei_hflip || h->sei_vflip)) {

        double angle = h->sei_anticlockwise_rotation * 360 / (double) (1 << 16);

        AVFrameSideData *rotation = av_frame_new_side_data(cur->f,

                                                           AV_FRAME_DATA_DISPLAYMATRIX,

                                                           sizeof(int32_t) * 9);

        if (!rotation)

            return;



        av_display_rotation_set((int32_t *)rotation->data, angle);

        av_display_matrix_flip((int32_t *)rotation->data,

                               h->sei_hflip, h->sei_vflip);

    }



     



     



    if (h->sps.bitstream_restriction_flag &&

        h->avctx->has_b_frames < h->sps.num_reorder_frames) {

        h->avctx->has_b_frames = h->sps.num_reorder_frames;

        h->low_delay           = 0;

    }



    if (h->avctx->strict_std_compliance >= FF_COMPLIANCE_STRICT &&

        !h->sps.bitstream_restriction_flag) {

        h->avctx->has_b_frames = MAX_DELAYED_PIC_COUNT - 1;

        h->low_delay           = 0;

    }



    pics = 0;

    while (h->delayed_pic[pics])

        pics++;



    assert(pics <= MAX_DELAYED_PIC_COUNT);



    h->delayed_pic[pics++] = cur;

    if (cur->reference == 0)

        cur->reference = DELAYED_PIC_REF;



     

    for (i = 0; i < MAX_DELAYED_PIC_COUNT; i++) {

        cnt     += out->poc < h->last_pocs[i];

        invalid += out->poc == INT_MIN;

    }

    if (!h->mmco_reset && !cur->f->key_frame &&

        cnt + invalid == MAX_DELAYED_PIC_COUNT && cnt > 0) {

        h->mmco_reset = 2;

        if (pics > 1)

            h->delayed_pic[pics - 2]->mmco_reset = 2;

    }

    if (h->mmco_reset || cur->f->key_frame) {

        for (i = 0; i < MAX_DELAYED_PIC_COUNT; i++)

            h->last_pocs[i] = INT_MIN;

        cnt     = 0;

        invalid = MAX_DELAYED_PIC_COUNT;

    }

    out     = h->delayed_pic[0];

    out_idx = 0;

    for (i = 1; i < MAX_DELAYED_PIC_COUNT &&

                h->delayed_pic[i] &&

                !h->delayed_pic[i - 1]->mmco_reset &&

                !h->delayed_pic[i]->f->key_frame;

         i++)

        if (h->delayed_pic[i]->poc < out->poc) {

            out     = h->delayed_pic[i];

            out_idx = i;

        }

    if (h->avctx->has_b_frames == 0 &&

        (h->delayed_pic[0]->f->key_frame || h->mmco_reset))

        h->next_outputed_poc = INT_MIN;

    out_of_order = !out->f->key_frame && !h->mmco_reset &&

                   (out->poc < h->next_outputed_poc);



    if (h->sps.bitstream_restriction_flag &&

        h->avctx->has_b_frames >= h->sps.num_reorder_frames) {

    } else if (out_of_order && pics - 1 == h->avctx->has_b_frames &&

               h->avctx->has_b_frames < MAX_DELAYED_PIC_COUNT) {

        if (invalid + cnt < MAX_DELAYED_PIC_COUNT) {

            h->avctx->has_b_frames = FFMAX(h->avctx->has_b_frames, cnt);

        }

        h->low_delay = 0;

    } else if (h->low_delay &&

               ((h->next_outputed_poc != INT_MIN &&

                 out->poc > h->next_outputed_poc + 2) ||

                cur->f->pict_type == AV_PICTURE_TYPE_B)) {

        h->low_delay = 0;

        h->avctx->has_b_frames++;

    }



    if (pics > h->avctx->has_b_frames) {

        out->reference &= ~DELAYED_PIC_REF;

         

         

        for (i = out_idx; h->delayed_pic[i]; i++)

            h->delayed_pic[i] = h->delayed_pic[i + 1];

    }

    memmove(h->last_pocs, &h->last_pocs[1],

            sizeof(*h->last_pocs) * (MAX_DELAYED_PIC_COUNT - 1));

    h->last_pocs[MAX_DELAYED_PIC_COUNT - 1] = cur->poc;

    if (!out_of_order && pics > h->avctx->has_b_frames) {

        h->next_output_pic = out;

        if (out->mmco_reset) {

            if (out_idx > 0) {

                h->next_outputed_poc                    = out->poc;

                h->delayed_pic[out_idx - 1]->mmco_reset = out->mmco_reset;

            } else {

                h->next_outputed_poc = INT_MIN;

            }

        } else {

            if (out_idx == 0 && pics > 1 && h->delayed_pic[0]->f->key_frame) {

                h->next_outputed_poc = INT_MIN;

            } else {

                h->next_outputed_poc = out->poc;

            }

        }

        h->mmco_reset = 0;

    } else {

        av_log(h->avctx, AV_LOG_DEBUG, "no picture\n");

    }



    if (h->next_output_pic) {

        if (h->next_output_pic->recovered) {

             

             

            h->frame_recovered |= FRAME_RECOVERED_SEI;

        }

        h->next_output_pic->recovered |= !!(h->frame_recovered & FRAME_RECOVERED_SEI);

    }



    if (setup_finished && !h->avctx->hwaccel)

        ff_thread_finish_setup(h->avctx);

}
