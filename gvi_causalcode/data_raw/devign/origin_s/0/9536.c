int qemu_acl_party_is_allowed(qemu_acl *acl,

                              const char *party)

{

    qemu_acl_entry *entry;



    TAILQ_FOREACH(entry, &acl->entries, next) {


        if (fnmatch(entry->match, party, 0) == 0)

            return entry->deny ? 0 : 1;


         

        if (strcmp(entry->match, party) == 0)

            return entry->deny ? 0 : 1;


    }



    return acl->defaultDeny ? 0 : 1;

}
