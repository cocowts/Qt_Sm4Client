/**
 * \brief          SM4 context structure
 */
#ifndef SM4_H
#define SM4_H

#define SM4_ENCRYPT     0
#define SM4_DECRYPT     1

#define SM4_RESTART     1
#define SM4_KEEP        0

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          SM4-CBC buffer encryption/decryption
 * \param ctx      SM4 context
 * \param dec_en   SM4_ENCRYPT or SM4_DECRYPT
 * \param flag     SM4_RESTART or SM4_KEEP
 * \param iv       initialization vector (updated after use)
 * \param length   length of the input data
 * \param input    buffer holding the input data
 * \param output   buffer holding the output data
 */
unsigned int sm4_cbc(unsigned char key[16],
                    int dec_en,
                    int flag,
                    unsigned char iv[16],
                    unsigned int  length,
                    unsigned char *input,
                    unsigned char *output );

/**
 * \brief          SM4-CBC buffer encryption/decryption
 * \param ctx      SM4 context
 * \param dec_en   SM4_ENCRYPT or SM4_DECRYPT
 * \param flag     SM4_RESTART or SM4_KEEP
 * \param length   length of the input data
 * \param input    buffer holding the input data
 * \param output   buffer holding the output data
 */
unsigned int sm4_ecb(unsigned char key[16],
         int dec_en,
         int flag,
         unsigned int length,
         unsigned char *input,
         unsigned char *output);

#ifdef __cplusplus
}
#endif

#endif

