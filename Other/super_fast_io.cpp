
char in[1 << 25];  // sizeof in varied in problem
char const* o;

void init_in() {
    o = in;
    in[fread(in, 1, sizeof(in) - 4, stdin)] = 0;  // set 0 at the end of buffer.
}

int readInt() {
    unsigned u = 0, s = 0;

    while (*o && *o <= 32) ++o;  // skip whitespaces...

    if (*o == '-')
        s = ~s, ++o;
    else if (*o == '+')
        ++o;  // skip sign

    while (*o >= '0' && *o <= '9')
        u = (u << 3) + (u << 1) + (*o++ - '0');  // u * 10 = u * 8 + u * 2 :)

    return static_cast<int>((u ^ s) + !!s);
}
