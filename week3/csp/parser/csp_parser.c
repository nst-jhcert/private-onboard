#include "csp_parser.h"

#include <stdio.h>

int CspHeaderParse(uint32_t raw, CspHeader *header) {
  if (!header) {
    return -1;
  }

  header->priority = (raw & CSP_ID_PRIO_MASK) >> CSP_ID_PRIO_SHIFT;
  header->source = (raw & CSP_ID_SRC_MASK) >> CSP_ID_SRC_SHIFT;
  header->destination = (raw & CSP_ID_DST_MASK) >> CSP_ID_DST_SHIFT;
  header->dport = (raw & CSP_ID_DPORT_MASK) >> CSP_ID_DPORT_SHIFT;
  header->sport = (raw & CSP_ID_SPORT_MASK) >> CSP_ID_SPORT_SHIFT;
  header->flags = (raw & CSP_ID_FLAGS_MASK) >> CSP_ID_FLAGS_SHIFT;

  return 0;
}

int CspHeaderSerialize(const CspHeader *header, uint32_t *raw) {
  if (!header || !raw) {
    return -1;
  }

  if (header->priority > CSP_ID_PRIO_MAX ||
      header->source > CSP_ID_HOST_MAX ||
      header->destination > CSP_ID_HOST_MAX ||
      header->dport > CSP_ID_PORT_MAX ||
      header->sport > CSP_ID_PORT_MAX) {
    return -1;
  }

  *raw = ((uint32_t)header->priority << CSP_ID_PRIO_SHIFT) |
         ((uint32_t)header->source << CSP_ID_SRC_SHIFT) |
         ((uint32_t)header->destination << CSP_ID_DST_SHIFT) |
         ((uint32_t)header->dport << CSP_ID_DPORT_SHIFT) |
         ((uint32_t)header->sport << CSP_ID_SPORT_SHIFT) |
         ((uint32_t)header->flags << CSP_ID_FLAGS_SHIFT);

  return 0;
}

int CspHeaderFromBytes(const uint8_t buf[4], CspHeader *header) {
  if (!buf || !header) {
    return -1;
  }

  uint32_t raw = ((uint32_t)buf[0] << 24) |
                 ((uint32_t)buf[1] << 16) |
                 ((uint32_t)buf[2] << 8) |
                 ((uint32_t)buf[3]);

  return CspHeaderParse(raw, header);
}

int CspHeaderToBytes(const CspHeader *header, uint8_t buf[4]) {
  if (!header || !buf) {
    return -1;
  }

  uint32_t raw;
  if (CspHeaderSerialize(header, &raw) != 0) {
    return -1;
  }

  buf[0] = (raw >> 24) & 0xFF;
  buf[1] = (raw >> 16) & 0xFF;
  buf[2] = (raw >> 8) & 0xFF;
  buf[3] = raw & 0xFF;

  return 0;
}

void CspHeaderPrint(const CspHeader *header) {
  if (!header) {
    return;
  }

  static const char *kPrioNames[] = {"CRITICAL", "HIGH", "NORM", "LOW"};

  printf("CSP Header:\n");
  printf("  Priority    : %u (%s)\n", header->priority,
         header->priority <= kCspPrioLow ? kPrioNames[header->priority]
                                         : "UNKNOWN");
  printf("  Source      : %u\n", header->source);
  printf("  Destination : %u\n", header->destination);
  printf("  Dest Port   : %u\n", header->dport);
  printf("  Src Port    : %u\n", header->sport);
  printf("  Flags       : 0x%02X", header->flags);

  if (header->flags) {
    printf(" [");
    int first = 1;
    if (header->flags & CSP_FCRC32) { printf("CRC32"); first = 0; }
    if (header->flags & CSP_FRDP) { printf("%sRDP", first ? "" : "|"); first = 0; }
    if (header->flags & CSP_FXTEA) { printf("%sXTEA", first ? "" : "|"); first = 0; }
    if (header->flags & CSP_FHMAC) { printf("%sHMAC", first ? "" : "|"); first = 0; }
    if (header->flags & CSP_FFRAG) { printf("%sFRAG", first ? "" : "|"); first = 0; }
    printf("]");
  }
  printf("\n");
}
