#ifndef PROTO_H__
#define PROTO_H__

#define RCVPORT         "1989"

#define NAMESIZE        11

struct msg_st
{
    uint8_t name[NAMESIZE];
    uint32_t dog;
    uint32_t bird;
    uint32_t fox;
}__attribute__((packed));

#endif

