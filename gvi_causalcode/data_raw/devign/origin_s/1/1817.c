static void vpc_close(BlockDriverState *bs)

{

    BDRVVPCState *s = bs->opaque;

    g_free(s->pagetable);


    g_free(s->pageentry_u8);




    migrate_del_blocker(s->migration_blocker);

    error_free(s->migration_blocker);

}
