#ifndef CRC32_H_
#define CRC32_H_

#include <stdint.h>

/*
 * CRC32 and CRC32C using optional ARMv8 instructions
 * https://patchwork.kernel.org/patch/5339581/
 *
 * From: Yazen Ghannam <yazen.ghannam@linaro.org>
 * To: linux-kernel@vger.kernel.org, linux-crypto@vger.kernel.org
 * Cc: herbert@gondor.apana.org.au, Yazen Ghannam <yazen.ghannam@linaro.org>
*/
#define CRC32X( crc, value ) __asm__("crc32x %w[c], %w[c], %x[v]":[c]"+r"(crc):[v]"r"(value))
#define CRC32W( crc, value ) __asm__("crc32w %w[c], %w[c], %w[v]":[c]"+r"(crc):[v]"r"(value))
#define CRC32H( crc, value ) __asm__("crc32h %w[c], %w[c], %w[v]":[c]"+r"(crc):[v]"r"(value))
#define CRC32B( crc, value ) __asm__("crc32b %w[c], %w[c], %w[v]":[c]"+r"(crc):[v]"r"(value))
#define CRC32CX( crc, value ) __asm__("crc32cx %w[c], %w[c], %x[v]":[c]"+r"(crc):[v]"r"(value))
#define CRC32CW( crc, value ) __asm__("crc32cw %w[c], %w[c], %w[v]":[c]"+r"(crc):[v]"r"(value))
#define CRC32CH( crc, value ) __asm__("crc32ch %w[c], %w[c], %w[v]":[c]"+r"(crc):[v]"r"(value))
#define CRC32CB( crc, value ) __asm__("crc32cb %w[c], %w[c], %w[v]":[c]"+r"(crc):[v]"r"(value))


/*
 * Calculate crc32 of a given Value
 * Retuns: crc Calculated value
*/
uint32_t crc32_arm64_le_hw( uint32_t crc, const uint8_t *p, unsigned int len )

/*
 * Calculate crc32c of a given Value
 * Retuns: crc Calculated value
*/
uint32_t crc32c_arm64_le_hw( uint32_t crc, const uint8_t *p, unsigned int len )

#endif