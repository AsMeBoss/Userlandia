#define HASHSTART 5381
unsigned int make_hash (char *s, unsigned int len)
{
    unsigned int h = HASHSTART, i;
    if (len > 0)
        for (i = 0; i < len; i++)
            h = (h + (h << 5)) ^* s++;
    return h;
}

