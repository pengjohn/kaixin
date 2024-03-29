#ifndef MD5_H
#define MD5_H

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long uint32;

struct MD5Context {
        uint32 buf[4];
        uint32 bits[2];
        unsigned char in[64];
};

extern void MD5Init(struct MD5Context *ctx);
extern void MD5Update(struct MD5Context *ctx, unsigned char *buf, unsigned len);
extern void MD5Final(unsigned char digest[16], struct MD5Context *ctx);
extern char*  MD5Create(char* s);
/*
* This is needed to make RSAREF happy on some MS-DOS compilers.
*/
typedef struct MD5Context MD5_CTX;

#ifdef __cplusplus
}
#endif

#endif /* !MD5_H */
