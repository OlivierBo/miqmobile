opt subtitle "HI-TECH Software Omniscient Code Generator (Lite mode) build 7503"

opt pagewidth 120

	opt lm

	processor	16F877
clrc	macro
	bcf	3,0
	endm
clrz	macro
	bcf	3,2
	endm
setc	macro
	bsf	3,0
	endm
setz	macro
	bsf	3,2
	endm
skipc	macro
	btfss	3,0
	endm
skipz	macro
	btfss	3,2
	endm
skipnc	macro
	btfsc	3,0
	endm
skipnz	macro
	btfsc	3,2
	endm
indf	equ	0
indf0	equ	0
pc	equ	2
pcl	equ	2
status	equ	3
fsr	equ	4
fsr0	equ	4
c	equ	1
z	equ	0
pclath	equ	10
	FNCALL	_main,_send_usart
	FNCALL	_main,_longueur_trame
	FNCALL	_main,_decalage_buffer
	FNROOT	_main
	FNCALL	intlevel1,_reception
	global	intlevel1
	FNROOT	intlevel1
	global	_buffer
	global	_top_buffer
	global	_INTCON
psect	text144,local,class=CODE,delta=2
global __ptext144
__ptext144:
_INTCON	set	11
	global	_PORTA
_PORTA	set	5
	global	_PORTB
_PORTB	set	6
	global	_PORTD
_PORTD	set	8
	global	_RCREG
_RCREG	set	26
	global	_RCSTA
_RCSTA	set	24
	global	_TXREG
_TXREG	set	25
	global	_CREN
_CREN	set	196
	global	_GIE
_GIE	set	95
	global	_PEIE
_PEIE	set	94
	global	_RB0
_RB0	set	48
	global	_RCIF
_RCIF	set	101
	global	_SPEN
_SPEN	set	199
	global	_TXIF
_TXIF	set	100
	global	_PIE1
_PIE1	set	140
	global	_SPBRG
_SPBRG	set	153
	global	_TRISA
_TRISA	set	133
	global	_TRISB
_TRISB	set	134
	global	_TRISD
_TRISD	set	136
	global	_TXSTA
_TXSTA	set	152
	global	_RCIE
_RCIE	set	1125
	global	_TXEN
_TXEN	set	1221
	file	"serial_communication_3.0.as"
	line	#
psect cinit,class=CODE,delta=2
global start_initialization
start_initialization:

psect	bssBANK0,class=BANK0,space=1
global __pbssBANK0
__pbssBANK0:
_buffer:
       ds      50

_top_buffer:
       ds      1

psect clrtext,class=CODE,delta=2
global clear_ram
;	Called with FSR containing the base address, and
;	W with the last address+1
clear_ram:
	clrwdt			;clear the watchdog before getting into this loop
clrloop:
	clrf	indf		;clear RAM location pointed to by FSR
	incf	fsr,f		;increment pointer
	xorwf	fsr,w		;XOR with final address
	btfsc	status,2	;have we reached the end yet?
	retlw	0		;all done for this memory range, return
	xorwf	fsr,w		;XOR again to restore value
	goto	clrloop		;do the next byte

; Clear objects allocated to BANK0
psect cinit,class=CODE,delta=2
	bcf	status, 7	;select IRP bank0
	movlw	low(__pbssBANK0)
	movwf	fsr
	movlw	low((__pbssBANK0)+033h)
	fcall	clear_ram
psect cinit,class=CODE,delta=2
global end_of_initialization

;End of C runtime variable initialization code

end_of_initialization:
clrf status
ljmp _main	;jump to C main() function
psect	cstackCOMMON,class=COMMON,space=1
global __pcstackCOMMON
__pcstackCOMMON:
	global	?_reception
?_reception:	; 0 bytes @ 0x0
	global	??_reception
??_reception:	; 0 bytes @ 0x0
	global	?_decalage_buffer
?_decalage_buffer:	; 0 bytes @ 0x0
	global	?_send_usart
?_send_usart:	; 0 bytes @ 0x0
	global	?_main
?_main:	; 0 bytes @ 0x0
	global	?_longueur_trame
?_longueur_trame:	; 1 bytes @ 0x0
	ds	5
	global	??_decalage_buffer
??_decalage_buffer:	; 0 bytes @ 0x5
	global	??_send_usart
??_send_usart:	; 0 bytes @ 0x5
	global	??_longueur_trame
??_longueur_trame:	; 0 bytes @ 0x5
	global	send_usart@octet
send_usart@octet:	; 1 bytes @ 0x5
	ds	1
	global	longueur_trame@titre
longueur_trame@titre:	; 1 bytes @ 0x6
	ds	1
	global	longueur_trame@curTrameLength
longueur_trame@curTrameLength:	; 1 bytes @ 0x7
	ds	2
psect	cstackBANK0,class=BANK0,space=1
global __pcstackBANK0
__pcstackBANK0:
	global	decalage_buffer@ind
decalage_buffer@ind:	; 1 bytes @ 0x0
	ds	1
	global	decalage_buffer@i
decalage_buffer@i:	; 1 bytes @ 0x1
	ds	1
	global	??_main
??_main:	; 0 bytes @ 0x2
	ds	5
	global	main@consigne_couple
main@consigne_couple:	; 1 bytes @ 0x7
	ds	1
	global	main@check_sum
main@check_sum:	; 1 bytes @ 0x8
	ds	1
	global	main@data_type
main@data_type:	; 1 bytes @ 0x9
	ds	1
	global	main@i
main@i:	; 1 bytes @ 0xA
	ds	1
	global	main@frame_length
main@frame_length:	; 1 bytes @ 0xB
	ds	1
	global	main@indice
main@indice:	; 1 bytes @ 0xC
	ds	1
;;Data sizes: Strings 0, constant 0, data 0, bss 51, persistent 0 stack 0
;;Auto spaces:   Size  Autos    Used
;; COMMON          14      9       9
;; BANK0           80     13      64
;; BANK1           80      0       0
;; BANK3           96      0       0
;; BANK2           96      0       0

;;
;; Pointer list with targets:



;;
;; Critical Paths under _main in COMMON
;;
;;   _main->_decalage_buffer
;;
;; Critical Paths under _reception in COMMON
;;
;;   None.
;;
;; Critical Paths under _main in BANK0
;;
;;   _main->_decalage_buffer
;;
;; Critical Paths under _reception in BANK0
;;
;;   None.
;;
;; Critical Paths under _main in BANK1
;;
;;   None.
;;
;; Critical Paths under _reception in BANK1
;;
;;   None.
;;
;; Critical Paths under _main in BANK3
;;
;;   None.
;;
;; Critical Paths under _reception in BANK3
;;
;;   None.
;;
;; Critical Paths under _main in BANK2
;;
;;   None.
;;
;; Critical Paths under _reception in BANK2
;;
;;   None.

;;
;;Main: autosize = 0, tempsize = 5, incstack = 0, save=0
;;

;;
;;Call Graph Tables:
;;
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (0) _main                                                13    13      0    1151
;;                                              2 BANK0     11    11      0
;;                         _send_usart
;;                     _longueur_trame
;;                    _decalage_buffer
;; ---------------------------------------------------------------------------------
;; (1) _longueur_trame                                       3     3      0      50
;;                                              5 COMMON     3     3      0
;; ---------------------------------------------------------------------------------
;; (1) _send_usart                                           1     1      0      22
;;                                              5 COMMON     1     1      0
;; ---------------------------------------------------------------------------------
;; (1) _decalage_buffer                                      6     6      0     134
;;                                              5 COMMON     4     4      0
;;                                              0 BANK0      2     2      0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 1
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (2) _reception                                            5     5      0       0
;;                                              0 COMMON     5     5      0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 2
;; ---------------------------------------------------------------------------------

;; Call Graph Graphs:

;; _main (ROOT)
;;   _send_usart
;;   _longueur_trame
;;   _decalage_buffer
;;
;; _reception (ROOT)
;;

;; Address spaces:

;;Name               Size   Autos  Total    Cost      Usage
;;BITCOMMON            E      0       0       0        0.0%
;;EEDATA             100      0       0       0        0.0%
;;NULL                 0      0       0       0        0.0%
;;CODE                 0      0       0       0        0.0%
;;COMMON               E      9       9       1       64.3%
;;BITSFR0              0      0       0       1        0.0%
;;SFR0                 0      0       0       1        0.0%
;;BITSFR1              0      0       0       2        0.0%
;;SFR1                 0      0       0       2        0.0%
;;STACK                0      0       1       2        0.0%
;;ABS                  0      0      49       3        0.0%
;;BITBANK0            50      0       0       4        0.0%
;;BITSFR3              0      0       0       4        0.0%
;;SFR3                 0      0       0       4        0.0%
;;BANK0               50      D      40       5       80.0%
;;BITSFR2              0      0       0       5        0.0%
;;SFR2                 0      0       0       5        0.0%
;;BITBANK1            50      0       0       6        0.0%
;;BANK1               50      0       0       7        0.0%
;;BITBANK3            60      0       0       8        0.0%
;;BANK3               60      0       0       9        0.0%
;;BITBANK2            60      0       0      10        0.0%
;;BANK2               60      0       0      11        0.0%
;;DATA                 0      0      4A      12        0.0%

	global	_main
psect	maintext,global,class=CODE,delta=2
global __pmaintext
__pmaintext:

;; *************** function _main *****************
;; Defined at:
;;		line 102 in file "C:\Users\Yoann\Documents\MIQ5\S1\Miqmobile\Pic\serial_communication_3.0\serial_communication_3.0.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  indice          1   12[BANK0 ] unsigned char 
;;  frame_length    1   11[BANK0 ] unsigned char 
;;  i               1   10[BANK0 ] unsigned char 
;;  data_type       1    9[BANK0 ] unsigned char 
;;  check_sum       1    8[BANK0 ] unsigned char 
;;  consigne_cou    1    7[BANK0 ] unsigned char 
;;  data_nb         1    0        unsigned char 
;;  j               1    0        unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 17F/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK3   BANK2
;;      Params:         0       0       0       0       0
;;      Locals:         0       6       0       0       0
;;      Temps:          0       5       0       0       0
;;      Totals:         0      11       0       0       0
;;Total ram usage:       11 bytes
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_send_usart
;;		_longueur_trame
;;		_decalage_buffer
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext
	file	"C:\Users\Yoann\Documents\MIQ5\S1\Miqmobile\Pic\serial_communication_3.0\serial_communication_3.0.c"
	line	102
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
	opt	stack 6
; Regs used in _main: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	106
	
l2040:	
;serial_communication_3.0.c: 104: char i;
;serial_communication_3.0.c: 105: char j;
;serial_communication_3.0.c: 106: char check_sum=0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(main@check_sum)
	line	115
	
l2042:	
;serial_communication_3.0.c: 107: char consigne_couple;
;serial_communication_3.0.c: 108: char indice;
;serial_communication_3.0.c: 109: char frame_length;
;serial_communication_3.0.c: 110: char data_nb;
;serial_communication_3.0.c: 111: char data_type;
;serial_communication_3.0.c: 115: TXSTA=0b00000110;
	movlw	(06h)
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	movwf	(152)^080h	;volatile
	line	116
;serial_communication_3.0.c: 116: RCSTA=0b10001110;
	movlw	(08Eh)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(24)	;volatile
	line	117
;serial_communication_3.0.c: 117: SPBRG=20;
	movlw	(014h)
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	movwf	(153)^080h	;volatile
	line	119
	
l2044:	
;serial_communication_3.0.c: 119: INTCON=0;
	clrf	(11)	;volatile
	line	120
	
l2046:	
;serial_communication_3.0.c: 120: PIE1=0;
	clrf	(140)^080h	;volatile
	line	121
	
l2048:	
;serial_communication_3.0.c: 121: TXEN=1;
	bsf	(1221/8)^080h,(1221)&7
	line	122
	
l2050:	
;serial_communication_3.0.c: 122: SPEN=1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(199/8),(199)&7
	line	123
	
l2052:	
;serial_communication_3.0.c: 123: CREN=1;
	bsf	(196/8),(196)&7
	line	124
	
l2054:	
;serial_communication_3.0.c: 124: GIE=1;
	bsf	(95/8),(95)&7
	line	125
	
l2056:	
;serial_communication_3.0.c: 125: PEIE=1;
	bsf	(94/8),(94)&7
	line	126
	
l2058:	
;serial_communication_3.0.c: 126: RCIE=1;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bsf	(1125/8)^080h,(1125)&7
	line	128
	
l2060:	
;serial_communication_3.0.c: 128: TRISA=0b00000000;
	clrf	(133)^080h	;volatile
	line	129
	
l2062:	
;serial_communication_3.0.c: 129: TRISB=0b00000000;
	clrf	(134)^080h	;volatile
	line	130
	
l2064:	
;serial_communication_3.0.c: 130: TRISD=0b00000000;
	clrf	(136)^080h	;volatile
	line	131
	
l2066:	
;serial_communication_3.0.c: 131: PORTA=0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(5)	;volatile
	line	132
	
l2068:	
;serial_communication_3.0.c: 132: PORTB=0;
	clrf	(6)	;volatile
	line	133
	
l2070:	
;serial_communication_3.0.c: 133: PORTD=0;
	clrf	(8)	;volatile
	line	139
	
l2072:	
;serial_communication_3.0.c: 139: send_usart(153);
	movlw	(099h)
	fcall	_send_usart
	line	140
	
l2074:	
;serial_communication_3.0.c: 140: send_usart(25);
	movlw	(019h)
	fcall	_send_usart
	line	141
	
l2076:	
;serial_communication_3.0.c: 141: send_usart(25+153);
	movlw	(0B2h)
	fcall	_send_usart
	goto	l2078
	line	145
;serial_communication_3.0.c: 145: while (1){
	
l674:	
	line	150
	
l2078:	
;serial_communication_3.0.c: 150: RB0=!RB0;
	movlw	1<<((48)&7)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	xorwf	((48)/8),f
	line	154
	
l2080:	
;serial_communication_3.0.c: 154: indice=0;
	clrf	(main@indice)
	line	156
;serial_communication_3.0.c: 156: while(indice+4 < top_buffer){
	goto	l2146
	
l676:	
	line	159
;serial_communication_3.0.c: 159: while((buffer[indice])!=153 && indice < top_buffer){
	goto	l2084
	
l678:	
	line	160
	
l2082:	
;serial_communication_3.0.c: 160: indice++;
	movlw	(01h)
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	addwf	(main@indice),f
	goto	l2084
	line	161
	
l677:	
	line	159
	
l2084:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(main@indice),w
	addlw	_buffer&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank0
	movf	indf,w
	xorlw	099h
	skipnz
	goto	u2321
	goto	u2320
u2321:
	goto	l2088
u2320:
	
l2086:	
	movf	(_top_buffer),w
	subwf	(main@indice),w
	skipc
	goto	u2331
	goto	u2330
u2331:
	goto	l2082
u2330:
	goto	l2088
	
l680:	
	goto	l2088
	
l681:	
	line	164
	
l2088:	
;serial_communication_3.0.c: 161: }
;serial_communication_3.0.c: 164: if(indice+1 < top_buffer){
	movf	(main@indice),w
	addlw	low(01h)
	movwf	(??_main+0)+0
	movlw	high(01h)
	skipnc
	movlw	(high(01h)+1)&0ffh
	movwf	((??_main+0)+0)+1
	movf	1+(??_main+0)+0,w
	xorlw	80h
	movwf	(??_main+2)+0
	movlw	80h
	subwf	(??_main+2)+0,w
	skipz
	goto	u2345
	movf	(_top_buffer),w
	subwf	0+(??_main+0)+0,w
u2345:

	skipnc
	goto	u2341
	goto	u2340
u2341:
	goto	l2146
u2340:
	line	166
	
l2090:	
;serial_communication_3.0.c: 166: data_type = buffer[indice+1];
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(main@indice),w
	addlw	01h
	addlw	_buffer&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank0
	movf	indf,w
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(main@data_type)
	line	168
;serial_communication_3.0.c: 168: switch(data_type){
	goto	l2144
	line	170
;serial_communication_3.0.c: 170: case 139:
	
l684:	
	line	171
	
l2092:	
;serial_communication_3.0.c: 171: frame_length = longueur_trame(data_type);
	movf	(main@data_type),w
	fcall	_longueur_trame
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(main@frame_length)
	line	172
	
l2094:	
;serial_communication_3.0.c: 172: check_sum=0;
	clrf	(main@check_sum)
	line	174
	
l2096:	
;serial_communication_3.0.c: 174: if(indice + frame_length -1 < top_buffer){
	movf	(main@indice),w
	addwf	(main@frame_length),w
	movwf	(??_main+0)+0
	clrf	(??_main+0)+0+1
	rlf	1+(??_main+0)+0,f
	
	movf	0+(??_main+0)+0,w
	addlw	low(-1)
	movwf	(??_main+2)+0
	movf	1+(??_main+0)+0,w
	skipnc
	addlw	1
	addlw	high(-1)
	movwf	1+(??_main+2)+0
	movf	1+(??_main+2)+0,w
	xorlw	80h
	movwf	(??_main+4)+0
	movlw	80h
	subwf	(??_main+4)+0,w
	skipz
	goto	u2355
	movf	(_top_buffer),w
	subwf	0+(??_main+2)+0,w
u2355:

	skipnc
	goto	u2351
	goto	u2350
u2351:
	goto	l2146
u2350:
	line	175
	
l2098:	
;serial_communication_3.0.c: 175: for(i=indice+1;i<indice + frame_length -1;i++){
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(main@indice),w
	addlw	01h
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(main@i)
	goto	l2104
	
l687:	
	line	176
	
l2100:	
;serial_communication_3.0.c: 176: check_sum+=buffer[i];
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(main@i),w
	addlw	_buffer&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank0
	movf	indf,w
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	addwf	(main@check_sum),f
	line	175
	
l2102:	
	movlw	(01h)
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	addwf	(main@i),f
	goto	l2104
	
l686:	
	
l2104:	
	movf	(main@indice),w
	addwf	(main@frame_length),w
	movwf	(??_main+0)+0
	clrf	(??_main+0)+0+1
	rlf	1+(??_main+0)+0,f
	
	movf	0+(??_main+0)+0,w
	addlw	low(-1)
	movwf	(??_main+2)+0
	movf	1+(??_main+0)+0,w
	skipnc
	addlw	1
	addlw	high(-1)
	movwf	1+(??_main+2)+0
	movf	1+(??_main+2)+0,w
	xorlw	80h
	sublw	080h
	skipz
	goto	u2365
	movf	0+(??_main+2)+0,w
	subwf	(main@i),w
u2365:

	skipc
	goto	u2361
	goto	u2360
u2361:
	goto	l2100
u2360:
	goto	l2106
	
l688:	
	line	179
	
l2106:	
;serial_communication_3.0.c: 177: }
;serial_communication_3.0.c: 179: if(buffer[indice + frame_length - 1 ] == check_sum){
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(main@frame_length),w
	addwf	(main@indice),w
	addlw	0FFh
	addlw	_buffer&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank0
	movf	indf,w
	xorwf	(main@check_sum),w
	skipz
	goto	u2371
	goto	u2370
u2371:
	goto	l2114
u2370:
	line	180
	
l2108:	
;serial_communication_3.0.c: 180: consigne_couple = buffer[indice+2];
	movf	(main@indice),w
	addlw	02h
	addlw	_buffer&0ffh
	movwf	fsr0
	movf	indf,w
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(main@consigne_couple)
	line	181
	
l2110:	
;serial_communication_3.0.c: 181: PORTD = consigne_couple;
	movf	(main@consigne_couple),w
	movwf	(8)	;volatile
	line	182
	
l2112:	
;serial_communication_3.0.c: 182: indice = indice+frame_length;
	movf	(main@frame_length),w
	addwf	(main@indice),w
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(main@indice)
	line	183
;serial_communication_3.0.c: 183: }
	goto	l2146
	line	184
	
l689:	
	
l2114:	
;serial_communication_3.0.c: 184: else{indice = indice+frame_length;}
	movf	(main@frame_length),w
	addwf	(main@indice),w
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(main@indice)
	goto	l2146
	
l690:	
	goto	l2146
	line	185
	
l685:	
	line	186
;serial_communication_3.0.c: 185: }
;serial_communication_3.0.c: 186: break;
	goto	l2146
	line	188
;serial_communication_3.0.c: 188: case 138:
	
l692:	
	line	189
	
l2116:	
;serial_communication_3.0.c: 189: frame_length = longueur_trame(data_type);
	movf	(main@data_type),w
	fcall	_longueur_trame
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(main@frame_length)
	line	190
	
l2118:	
;serial_communication_3.0.c: 190: check_sum=0;
	clrf	(main@check_sum)
	line	192
	
l2120:	
;serial_communication_3.0.c: 192: if(indice + frame_length -1 < top_buffer){
	movf	(main@indice),w
	addwf	(main@frame_length),w
	movwf	(??_main+0)+0
	clrf	(??_main+0)+0+1
	rlf	1+(??_main+0)+0,f
	
	movf	0+(??_main+0)+0,w
	addlw	low(-1)
	movwf	(??_main+2)+0
	movf	1+(??_main+0)+0,w
	skipnc
	addlw	1
	addlw	high(-1)
	movwf	1+(??_main+2)+0
	movf	1+(??_main+2)+0,w
	xorlw	80h
	movwf	(??_main+4)+0
	movlw	80h
	subwf	(??_main+4)+0,w
	skipz
	goto	u2385
	movf	(_top_buffer),w
	subwf	0+(??_main+2)+0,w
u2385:

	skipnc
	goto	u2381
	goto	u2380
u2381:
	goto	l2146
u2380:
	line	193
	
l2122:	
;serial_communication_3.0.c: 193: for(i=indice+1;i<indice + frame_length -1;i++){
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(main@indice),w
	addlw	01h
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(main@i)
	goto	l2128
	
l695:	
	line	194
	
l2124:	
;serial_communication_3.0.c: 194: check_sum+=buffer[i];
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(main@i),w
	addlw	_buffer&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank0
	movf	indf,w
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	addwf	(main@check_sum),f
	line	193
	
l2126:	
	movlw	(01h)
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	addwf	(main@i),f
	goto	l2128
	
l694:	
	
l2128:	
	movf	(main@indice),w
	addwf	(main@frame_length),w
	movwf	(??_main+0)+0
	clrf	(??_main+0)+0+1
	rlf	1+(??_main+0)+0,f
	
	movf	0+(??_main+0)+0,w
	addlw	low(-1)
	movwf	(??_main+2)+0
	movf	1+(??_main+0)+0,w
	skipnc
	addlw	1
	addlw	high(-1)
	movwf	1+(??_main+2)+0
	movf	1+(??_main+2)+0,w
	xorlw	80h
	sublw	080h
	skipz
	goto	u2395
	movf	0+(??_main+2)+0,w
	subwf	(main@i),w
u2395:

	skipc
	goto	u2391
	goto	u2390
u2391:
	goto	l2124
u2390:
	goto	l2130
	
l696:	
	line	197
	
l2130:	
;serial_communication_3.0.c: 195: }
;serial_communication_3.0.c: 197: if(buffer[indice + frame_length - 1 ] == check_sum){
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(main@frame_length),w
	addwf	(main@indice),w
	addlw	0FFh
	addlw	_buffer&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank0
	movf	indf,w
	xorwf	(main@check_sum),w
	skipz
	goto	u2401
	goto	u2400
u2401:
	goto	l2138
u2400:
	line	198
	
l2132:	
;serial_communication_3.0.c: 198: consigne_couple = buffer[indice+2];
	movf	(main@indice),w
	addlw	02h
	addlw	_buffer&0ffh
	movwf	fsr0
	movf	indf,w
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(main@consigne_couple)
	line	199
	
l2134:	
;serial_communication_3.0.c: 199: PORTD = consigne_couple;
	movf	(main@consigne_couple),w
	movwf	(8)	;volatile
	line	200
	
l2136:	
;serial_communication_3.0.c: 200: indice = indice+frame_length;
	movf	(main@frame_length),w
	addwf	(main@indice),w
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(main@indice)
	line	201
;serial_communication_3.0.c: 201: }
	goto	l2146
	line	202
	
l697:	
	
l2138:	
;serial_communication_3.0.c: 202: else{indice = indice+frame_length;}
	movf	(main@frame_length),w
	addwf	(main@indice),w
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(main@indice)
	goto	l2146
	
l698:	
	goto	l2146
	line	203
	
l693:	
	line	204
;serial_communication_3.0.c: 203: }
;serial_communication_3.0.c: 204: break;
	goto	l2146
	line	206
;serial_communication_3.0.c: 206: default:indice = indice+4;break;
	
l699:	
	
l2140:	
	movf	(main@indice),w
	addlw	04h
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(main@indice)
	goto	l2146
	line	207
	
l2142:	
;serial_communication_3.0.c: 207: }
	goto	l2146
	line	168
	
l683:	
	
l2144:	
	movf	(main@data_type),w
	; Switch size 1, requested type "space"
; Number of cases is 2, Range of values is 138 to 139
; switch strategies available:
; Name         Instructions Cycles
; simple_byte            7     4 (average)
; direct_byte           17    11 (fixed)
; jumptable            263     9 (fixed)
;	Chosen strategy is simple_byte

	opt asmopt_off
	xorlw	138^0	; case 138
	skipnz
	goto	l2116
	xorlw	139^138	; case 139
	skipnz
	goto	l2092
	goto	l2140
	opt asmopt_on

	line	207
	
l691:	
	goto	l2146
	line	212
	
l682:	
	goto	l2146
	line	214
	
l675:	
	line	156
	
l2146:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(main@indice),w
	addlw	low(04h)
	movwf	(??_main+0)+0
	movlw	high(04h)
	skipnc
	movlw	(high(04h)+1)&0ffh
	movwf	((??_main+0)+0)+1
	movf	1+(??_main+0)+0,w
	xorlw	80h
	movwf	(??_main+2)+0
	movlw	80h
	subwf	(??_main+2)+0,w
	skipz
	goto	u2415
	movf	(_top_buffer),w
	subwf	0+(??_main+0)+0,w
u2415:

	skipc
	goto	u2411
	goto	u2410
u2411:
	goto	l2084
u2410:
	goto	l2148
	
l700:	
	line	218
	
l2148:	
;serial_communication_3.0.c: 212: }
;serial_communication_3.0.c: 214: }
;serial_communication_3.0.c: 218: decalage_buffer(indice);
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(main@indice),w
	fcall	_decalage_buffer
	goto	l2078
	line	222
	
l701:	
	line	145
	goto	l2078
	
l702:	
	line	226
	
l703:	
	global	start
	ljmp	start
	opt stack 0
GLOBAL	__end_of_main
	__end_of_main:
;; =============== function _main ends ============

	signat	_main,88
	global	_longueur_trame
psect	text145,local,class=CODE,delta=2
global __ptext145
__ptext145:

;; *************** function _longueur_trame *****************
;; Defined at:
;;		line 85 in file "C:\Users\Yoann\Documents\MIQ5\S1\Miqmobile\Pic\serial_communication_3.0\serial_communication_3.0.c"
;; Parameters:    Size  Location     Type
;;  titre           1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  titre           1    6[COMMON] unsigned char 
;;  curTrameLeng    1    7[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK3   BANK2
;;      Params:         0       0       0       0       0
;;      Locals:         2       0       0       0       0
;;      Temps:          1       0       0       0       0
;;      Totals:         3       0       0       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text145
	file	"C:\Users\Yoann\Documents\MIQ5\S1\Miqmobile\Pic\serial_communication_3.0\serial_communication_3.0.c"
	line	85
	global	__size_of_longueur_trame
	__size_of_longueur_trame	equ	__end_of_longueur_trame-_longueur_trame
	
_longueur_trame:	
	opt	stack 6
; Regs used in _longueur_trame: [wreg-fsr0h+status,2+status,0]
;longueur_trame@titre stored from wreg
	movwf	(longueur_trame@titre)
	line	87
	
l2018:	
;serial_communication_3.0.c: 86: char curTrameLength;
;serial_communication_3.0.c: 87: switch (titre){
	goto	l2034
	line	88
;serial_communication_3.0.c: 88: case 138: curTrameLength= 1 + 3; break;
	
l664:	
	
l2020:	
	movlw	(04h)
	movwf	(??_longueur_trame+0)+0
	movf	(??_longueur_trame+0)+0,w
	movwf	(longueur_trame@curTrameLength)
	goto	l2036
	line	89
;serial_communication_3.0.c: 89: case 139: curTrameLength= 1 + 3 ; break;
	
l666:	
	
l2022:	
	movlw	(04h)
	movwf	(??_longueur_trame+0)+0
	movf	(??_longueur_trame+0)+0,w
	movwf	(longueur_trame@curTrameLength)
	goto	l2036
	line	90
;serial_communication_3.0.c: 90: case 10: curTrameLength= 1 + 3 ; break;
	
l667:	
	
l2024:	
	movlw	(04h)
	movwf	(??_longueur_trame+0)+0
	movf	(??_longueur_trame+0)+0,w
	movwf	(longueur_trame@curTrameLength)
	goto	l2036
	line	91
;serial_communication_3.0.c: 91: case 11: curTrameLength= 1 + 3 ; break;
	
l668:	
	
l2026:	
	movlw	(04h)
	movwf	(??_longueur_trame+0)+0
	movf	(??_longueur_trame+0)+0,w
	movwf	(longueur_trame@curTrameLength)
	goto	l2036
	line	92
;serial_communication_3.0.c: 92: case 12: curTrameLength= 1 + 3 ; break;
	
l669:	
	
l2028:	
	movlw	(04h)
	movwf	(??_longueur_trame+0)+0
	movf	(??_longueur_trame+0)+0,w
	movwf	(longueur_trame@curTrameLength)
	goto	l2036
	line	95
;serial_communication_3.0.c: 95: default : curTrameLength = 4;break;
	
l670:	
	
l2030:	
	movlw	(04h)
	movwf	(??_longueur_trame+0)+0
	movf	(??_longueur_trame+0)+0,w
	movwf	(longueur_trame@curTrameLength)
	goto	l2036
	line	96
	
l2032:	
;serial_communication_3.0.c: 96: }
	goto	l2036
	line	87
	
l663:	
	
l2034:	
	movf	(longueur_trame@titre),w
	; Switch size 1, requested type "space"
; Number of cases is 5, Range of values is 10 to 139
; switch strategies available:
; Name         Instructions Cycles
; simple_byte           16     9 (average)
; jumptable            263     9 (fixed)
;	Chosen strategy is simple_byte

	opt asmopt_off
	xorlw	10^0	; case 10
	skipnz
	goto	l2024
	xorlw	11^10	; case 11
	skipnz
	goto	l2026
	xorlw	12^11	; case 12
	skipnz
	goto	l2028
	xorlw	138^12	; case 138
	skipnz
	goto	l2020
	xorlw	139^138	; case 139
	skipnz
	goto	l2022
	goto	l2030
	opt asmopt_on

	line	96
	
l665:	
	line	97
	
l2036:	
;serial_communication_3.0.c: 97: return curTrameLength;
	movf	(longueur_trame@curTrameLength),w
	goto	l671
	
l2038:	
	line	98
	
l671:	
	return
	opt stack 0
GLOBAL	__end_of_longueur_trame
	__end_of_longueur_trame:
;; =============== function _longueur_trame ends ============

	signat	_longueur_trame,4217
	global	_send_usart
psect	text146,local,class=CODE,delta=2
global __ptext146
__ptext146:

;; *************** function _send_usart *****************
;; Defined at:
;;		line 78 in file "C:\Users\Yoann\Documents\MIQ5\S1\Miqmobile\Pic\serial_communication_3.0\serial_communication_3.0.c"
;; Parameters:    Size  Location     Type
;;  octet           1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  octet           1    5[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK3   BANK2
;;      Params:         0       0       0       0       0
;;      Locals:         1       0       0       0       0
;;      Temps:          0       0       0       0       0
;;      Totals:         1       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text146
	file	"C:\Users\Yoann\Documents\MIQ5\S1\Miqmobile\Pic\serial_communication_3.0\serial_communication_3.0.c"
	line	78
	global	__size_of_send_usart
	__size_of_send_usart	equ	__end_of_send_usart-_send_usart
	
_send_usart:	
	opt	stack 6
; Regs used in _send_usart: [wreg]
;send_usart@octet stored from wreg
	movwf	(send_usart@octet)
	line	79
	
l2016:	
;serial_communication_3.0.c: 79: TXREG=octet;
	movf	(send_usart@octet),w
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(25)	;volatile
	line	80
;serial_communication_3.0.c: 80: while(!TXIF);
	goto	l657
	
l658:	
	
l657:	
	btfss	(100/8),(100)&7
	goto	u2311
	goto	u2310
u2311:
	goto	l657
u2310:
	
l659:	
	line	81
;serial_communication_3.0.c: 81: TXIF=0;
	bcf	(100/8),(100)&7
	line	82
	
l660:	
	return
	opt stack 0
GLOBAL	__end_of_send_usart
	__end_of_send_usart:
;; =============== function _send_usart ends ============

	signat	_send_usart,4216
	global	_decalage_buffer
psect	text147,local,class=CODE,delta=2
global __ptext147
__ptext147:

;; *************** function _decalage_buffer *****************
;; Defined at:
;;		line 70 in file "C:\Users\Yoann\Documents\MIQ5\S1\Miqmobile\Pic\serial_communication_3.0\serial_communication_3.0.c"
;; Parameters:    Size  Location     Type
;;  ind             1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  ind             1    0[BANK0 ] unsigned char 
;;  i               1    1[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK3   BANK2
;;      Params:         0       0       0       0       0
;;      Locals:         0       2       0       0       0
;;      Temps:          4       0       0       0       0
;;      Totals:         4       2       0       0       0
;;Total ram usage:        6 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text147
	file	"C:\Users\Yoann\Documents\MIQ5\S1\Miqmobile\Pic\serial_communication_3.0\serial_communication_3.0.c"
	line	70
	global	__size_of_decalage_buffer
	__size_of_decalage_buffer	equ	__end_of_decalage_buffer-_decalage_buffer
	
_decalage_buffer:	
	opt	stack 6
; Regs used in _decalage_buffer: [wreg-fsr0h+status,2+status,0]
;decalage_buffer@ind stored from wreg
	line	72
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(decalage_buffer@ind)
	
l2006:	
;serial_communication_3.0.c: 71: char i;
;serial_communication_3.0.c: 72: for(i=0;i<(top_buffer - ind);i++){
	clrf	(decalage_buffer@i)
	goto	l2012
	
l652:	
	line	73
	
l2008:	
;serial_communication_3.0.c: 73: buffer[i]=buffer[i+ind];
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(decalage_buffer@ind),w
	addwf	(decalage_buffer@i),w
	addlw	_buffer&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank0
	movf	indf,w
	movwf	(??_decalage_buffer+0)+0
	movf	(decalage_buffer@i),w
	addlw	_buffer&0ffh
	movwf	fsr0
	movf	(??_decalage_buffer+0)+0,w
	movwf	indf
	line	72
	
l2010:	
	movlw	(01h)
	movwf	(??_decalage_buffer+0)+0
	movf	(??_decalage_buffer+0)+0,w
	addwf	(decalage_buffer@i),f
	goto	l2012
	
l651:	
	
l2012:	
	movf	(decalage_buffer@ind),w
	movwf	(??_decalage_buffer+0)+0
	clrf	(??_decalage_buffer+0)+0+1
	comf	(??_decalage_buffer+0)+0,f
	comf	(??_decalage_buffer+0)+1,f
	incf	(??_decalage_buffer+0)+0,f
	skipnz
	incf	(??_decalage_buffer+0)+1,f
	movf	(_top_buffer),w
	addwf	0+(??_decalage_buffer+0)+0,w
	movwf	(??_decalage_buffer+2)+0
	movf	1+(??_decalage_buffer+0)+0,w
	skipnc
	incf	1+(??_decalage_buffer+0)+0,w
	movwf	((??_decalage_buffer+2)+0)+1
	movf	1+(??_decalage_buffer+2)+0,w
	xorlw	80h
	sublw	080h
	skipz
	goto	u2305
	movf	0+(??_decalage_buffer+2)+0,w
	subwf	(decalage_buffer@i),w
u2305:

	skipc
	goto	u2301
	goto	u2300
u2301:
	goto	l2008
u2300:
	goto	l2014
	
l653:	
	line	75
	
l2014:	
;serial_communication_3.0.c: 74: }
;serial_communication_3.0.c: 75: top_buffer -= ind;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(decalage_buffer@ind),w
	subwf	(_top_buffer),f
	line	76
	
l654:	
	return
	opt stack 0
GLOBAL	__end_of_decalage_buffer
	__end_of_decalage_buffer:
;; =============== function _decalage_buffer ends ============

	signat	_decalage_buffer,4216
	global	_reception
psect	text148,local,class=CODE,delta=2
global __ptext148
__ptext148:

;; *************** function _reception *****************
;; Defined at:
;;		line 57 in file "C:\Users\Yoann\Documents\MIQ5\S1\Miqmobile\Pic\serial_communication_3.0\serial_communication_3.0.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK3   BANK2
;;      Params:         0       0       0       0       0
;;      Locals:         0       0       0       0       0
;;      Temps:          5       0       0       0       0
;;      Totals:         5       0       0       0       0
;;Total ram usage:        5 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		Interrupt level 1
;; This function uses a non-reentrant model
;;
psect	text148
	file	"C:\Users\Yoann\Documents\MIQ5\S1\Miqmobile\Pic\serial_communication_3.0\serial_communication_3.0.c"
	line	57
	global	__size_of_reception
	__size_of_reception	equ	__end_of_reception-_reception
	
_reception:	
	opt	stack 6
; Regs used in _reception: [wreg-fsr0h+status,2+status,0]
psect	intentry,class=CODE,delta=2
global __pintentry
__pintentry:
global interrupt_function
interrupt_function:
	global saved_w
	saved_w	set	btemp+0
	movwf	saved_w
	swapf	status,w
	movwf	(??_reception+1)
	movf	fsr0,w
	movwf	(??_reception+2)
	movf	pclath,w
	movwf	(??_reception+3)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	btemp+1,w
	movwf	(??_reception+4)
	ljmp	_reception
psect	text148
	
i1l1994:	
	btfss	(101/8),(101)&7
	goto	u228_21
	goto	u228_20
u228_21:
	goto	i1l648
u228_20:
	line	58
	
i1l1996:	
;serial_communication_3.0.c: 58: if (top_buffer < 50 -1)
	movlw	(031h)
	subwf	(_top_buffer),w
	skipnc
	goto	u229_21
	goto	u229_20
u229_21:
	goto	i1l2004
u229_20:
	line	59
	
i1l1998:	
;serial_communication_3.0.c: 59: {buffer[top_buffer]=RCREG;
	movf	(26),w	;volatile
	movwf	(??_reception+0)+0
	movf	(_top_buffer),w
	addlw	_buffer&0ffh
	movwf	fsr0
	movf	(??_reception+0)+0,w
	bcf	status, 7	;select IRP bank0
	movwf	indf
	line	60
	
i1l2000:	
;serial_communication_3.0.c: 60: RCREG=0;
	clrf	(26)	;volatile
	line	61
	
i1l2002:	
;serial_communication_3.0.c: 61: top_buffer++;
	movlw	(01h)
	movwf	(??_reception+0)+0
	movf	(??_reception+0)+0,w
	addwf	(_top_buffer),f
	line	62
;serial_communication_3.0.c: 62: }
	goto	i1l648
	line	63
	
i1l646:	
	
i1l2004:	
;serial_communication_3.0.c: 63: else {top_buffer = 1;
	clrf	(_top_buffer)
	bsf	status,0
	rlf	(_top_buffer),f
	goto	i1l648
	line	64
	
i1l647:	
	goto	i1l648
	line	65
	
i1l645:	
	line	67
	
i1l648:	
	movf	(??_reception+4),w
	movwf	btemp+1
	movf	(??_reception+3),w
	movwf	pclath
	movf	(??_reception+2),w
	movwf	fsr0
	swapf	(??_reception+1)^0FFFFFF80h,w
	movwf	status
	swapf	saved_w,f
	swapf	saved_w,w
	retfie
	opt stack 0
GLOBAL	__end_of_reception
	__end_of_reception:
;; =============== function _reception ends ============

	signat	_reception,88
psect	text149,local,class=CODE,delta=2
global __ptext149
__ptext149:
	global	btemp
	btemp set 07Eh

	DABS	1,126,2	;btemp
	global	wtemp0
	wtemp0 set btemp
	end
