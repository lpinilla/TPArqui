#define ACS_PRESENT 0x80 /* segmento presente en memoria */
#define ACS_INT_386 0x0E	/* Interrupt GATE 32 bits */
#define ACS_INT ( ACS_PRESENT | ACS_INT_386 )
#pragma pack(push)
#pragma pack(1)

typedef struct{
	uint16_t offset_1, selector, offset_m;
	uint8_t cero, access;
	uint32_t offset_h, other_cero;
} DESCR_INT;

#pragma pack(pop)

DESCR_INT * idt = (DESCR_INT *) 0x0;
void _irq00Handler(void);
void _irq01Handler(void);
void picMasterMask(int a);
void picSlaveMask(int a);
void _cli(void);
void _sti(void);
void setup_IDT_entry(int index, uint64_t offset);