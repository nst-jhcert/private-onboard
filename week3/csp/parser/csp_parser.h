#ifndef CSP_PARSER_H_
#define CSP_PARSER_H_

#include <stdint.h>

// CSP Header field sizes (bits).
#define CSP_ID_PRIO_SIZE 2
#define CSP_ID_HOST_SIZE 5
#define CSP_ID_PORT_SIZE 6
#define CSP_ID_FLAGS_SIZE 8

// CSP Header field max values.
#define CSP_ID_PRIO_MAX ((1 << CSP_ID_PRIO_SIZE) - 1)
#define CSP_ID_HOST_MAX ((1 << CSP_ID_HOST_SIZE) - 1)
#define CSP_ID_PORT_MAX ((1 << CSP_ID_PORT_SIZE) - 1)
#define CSP_ID_FLAGS_MAX ((1 << CSP_ID_FLAGS_SIZE) - 1)

// Bit shift amounts for each field (big-endian wire format).
#define CSP_ID_FLAGS_SHIFT 0
#define CSP_ID_SPORT_SHIFT (CSP_ID_FLAGS_SIZE)
#define CSP_ID_DPORT_SHIFT (CSP_ID_FLAGS_SIZE + CSP_ID_PORT_SIZE)
#define CSP_ID_DST_SHIFT (CSP_ID_FLAGS_SIZE + 2 * CSP_ID_PORT_SIZE)
#define CSP_ID_SRC_SHIFT \
  (CSP_ID_FLAGS_SIZE + 2 * CSP_ID_PORT_SIZE + CSP_ID_HOST_SIZE)
#define CSP_ID_PRIO_SHIFT \
  (CSP_ID_FLAGS_SIZE + 2 * CSP_ID_PORT_SIZE + 2 * CSP_ID_HOST_SIZE)

// Bit masks.
#define CSP_ID_PRIO_MASK ((uint32_t)CSP_ID_PRIO_MAX << CSP_ID_PRIO_SHIFT)
#define CSP_ID_SRC_MASK ((uint32_t)CSP_ID_HOST_MAX << CSP_ID_SRC_SHIFT)
#define CSP_ID_DST_MASK ((uint32_t)CSP_ID_HOST_MAX << CSP_ID_DST_SHIFT)
#define CSP_ID_DPORT_MASK ((uint32_t)CSP_ID_PORT_MAX << CSP_ID_DPORT_SHIFT)
#define CSP_ID_SPORT_MASK ((uint32_t)CSP_ID_PORT_MAX << CSP_ID_SPORT_SHIFT)
#define CSP_ID_FLAGS_MASK ((uint32_t)CSP_ID_FLAGS_MAX << CSP_ID_FLAGS_SHIFT)

// Flag bit definitions.
#define CSP_FRES1 0x80
#define CSP_FRES2 0x40
#define CSP_FRES3 0x20
#define CSP_FFRAG 0x10
#define CSP_FHMAC 0x08
#define CSP_FXTEA 0x04
#define CSP_FRDP 0x02
#define CSP_FCRC32 0x01

// Priority levels.
typedef enum {
  kCspPrioCritical = 0,
  kCspPrioHigh = 1,
  kCspPrioNorm = 2,
  kCspPrioLow = 3,
} CspPriority;

// Parsed CSP header.
typedef struct {
  uint8_t priority;
  uint8_t source;
  uint8_t destination;
  uint8_t dport;
  uint8_t sport;
  uint8_t flags;
} CspHeader;

// Parses a 32-bit raw CSP header (big-endian wire format) into structured
// fields. Returns 0 on success, -1 on error.
int CspHeaderParse(uint32_t raw, CspHeader *header);

// Serializes structured CSP header fields into a 32-bit raw value (big-endian
// wire format). Returns 0 on success, -1 on error (field out of range).
int CspHeaderSerialize(const CspHeader *header, uint32_t *raw);

// Parses a 4-byte buffer (network byte order) into structured fields.
// Returns 0 on success, -1 on error.
int CspHeaderFromBytes(const uint8_t buf[4], CspHeader *header);

// Serializes structured fields into a 4-byte buffer (network byte order).
// Returns 0 on success, -1 on error.
int CspHeaderToBytes(const CspHeader *header, uint8_t buf[4]);

// Prints CSP header fields to stdout for debugging.
void CspHeaderPrint(const CspHeader *header);

#endif  // CSP_PARSER_H_
