/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set expandtab shiftwidth=4 tabstop=4: */

/**
 * \file
 * <PRE>
 * High performance base64 encoder / decoder
 *
 * Copyright &copy; 2005, 2006, 2007 Nick Galbreath -- nickg [at] modp [dot] com
 * All rights reserved.
 *
 * http://code.google.com/p/stringencoders/
 *
 * Released under bsd license.  See modp_b64.c for details.
 * </pre>
 *
 * This uses the standard base 64 alphabet.  If you are planning
 * to embed a base 64 encoding inside a URL use modp_b64w instead.
 *
 */

#ifndef COM_MODP_STRINGENCODERS_B64
#define COM_MODP_STRINGENCODERS_B64

#ifdef __cplusplus
#define BEGIN_C extern "C" {
#define END_C }
#else
#define BEGIN_C
#define END_C
#endif

BEGIN_C

/**
 * Encode a raw binary string into base 64.
 * \param[out] dest should be allocated by the caller to contain
 *   at least modp_b64_encode_len(len) bytes (see below)
 *   This will contain the null-terminated b64 encoded result
 * \param[in] src contains the bytes
 * \param[in] len contains the number of bytes in the src
 * \return length of the destination string plus the ending null byte
 *    i.e.  the result will be equal to strlen(dest) + 1
 *
 * Example
 *
 * \code
 * char* src = ...;
 * int srclen = ...; //the length of number of bytes in src
 * char* dest = (char*) malloc(modp_b64_encode_len);
 * int len = modp_b64_encode(dest, src, sourcelen);
 * if (len == -1) {
 *   printf("Error\n");
 * } else {
 *   printf("b64 = %s\n", dest);
 * }
 * \endcode
 *
 */
int modp_b64_encode(char* dest, const char* str, int len);

/**
 * Decode a base64 encoded string
 *
 * \param[out] dest should be allocated by the caller to contain at least
 *    len * 3 / 4 bytes.  The destination cannot be the same as the source
 *    They must be different buffers.
 * \param[in] src should contain exactly len bytes of b64 characters.
 *     if src contains -any- non-base characters (such as white
 *     space, -1 is returned.
 * \param[in] len is the length of src
 *
 * \return the length (strlen) of the output, or -1 if unable to
 * decode
 *
 * \code
 * char* src = ...;
 * int srclen = ...; // or if you don't know use strlen(src)
 * char* dest = (char*) malloc(modp_b64_decode_len(srclen));
 * int len = modp_b64_decode(dest, src, sourcelen);
 * if (len == -1) { error }
 * \endcode
 */
int modp_b64_decode(char* dest, const char* src, int len);

/**
 * Given a source string of length len, this returns the amount of
 * memory the destination string should have.
 *
 * remember, this is integer math
 * 3 bytes turn into 4 chars
 * ceiling[len / 3] * 4 + 1
 *
 * +1 is for any extra null.
 */
#define modp_b64_encode_len(A) ((A+2)/3 * 4 + 1)

/**
 * Given a base64 string of length len,
 *   this returns the amount of memory required for output string
 *  It maybe be more than the actual number of bytes written.
 * NOTE: remember this is integer math
 * this allocates a bit more memory than traditional versions of b64
 * decode  4 chars turn into 3 bytes
 * floor[len * 3/4] + 2
 */
#define modp_b64_decode_len(A) (A / 4 * 3 + 2)

/**
 * Will return the strlen of the output from encoding.
 * This may be less than the required number of bytes allocated.
 *
 * This allows you to 'deserialized' a struct
 * \code
 * char* b64encoded = "...";
 * int len = strlen(b64encoded);
 *
 * struct datastuff foo;
 * if (modp_b64_encode_strlen(sizeof(struct datastuff)) != len) {
 *    // wrong size
 *    return false;
 * } else {
 *    // safe to do;
 *    if (modp_b64_decode((char*) &foo, b64encoded, len) == -1) {
 *      // bad characters
 *      return false;
 *    }
 * }
 * // foo is filled out now
 * \endcode
 */
#define modp_b64_encode_strlen(A) ((A + 2)/ 3 * 4)

END_C


#endif /* MODP_B64 */
