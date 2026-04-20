```
  /* DMA buffers must not be placed in DTCMRAM (DMA inaccessible on H7). */
  .dma_buffer (NOLOAD) : ALIGN(32)
  {
    *(.dma_buffer)
    *(.dma_buffer*)
    . = ALIGN(32);
  } >RAM_D2
```
