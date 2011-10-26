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
	FNROOT	_main
	global	_INTCON
psect	maintext,global,class=CODE,delta=2
global __pmaintext
__pmaintext:
_INTCON	set	11
	global	_PORTA
_PORTA	set	5
	global	_PORTB
_PORTB	set	6
	global	_PORTD
_PORTD	set	8
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
	global	_SPEN
_SPEN	set	199
	global	_TMR0IE
_TMR0IE	set	93
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
	global	_PS0
_PS0	set	1032
	global	_PS1
_PS1	set	1033
	global	_PS2
_PS2	set	1034
	global	_PSA
_PSA	set	1035
	global	_RCIE
_RCIE	set	1125
	global	_T0CS
_T0CS	set	1037
	global	_TXEN
_TXEN	set	1221
	global	_TXIE
_TXIE	set	1124
	file	"envoie_trame.as"
	line	#
psect cinit,class=CODE,delta=2
global start_initialization
start_initialization:

psect cinit,class=CODE,delta=2
global end_of_initialization

;End of C runtime variable initialization code

end_of_initialization:
clrf status
ljmp _main	;jump to C main() function
psect	cstackCOMMON,class=COMMON,space=1
global __pcstackCOMMON
__pcstackCOMMON:
	global	?_main
?_main:	; 0 bytes @ 0x0
	global	??_main
??_main:	; 0 bytes @ 0x0
	ds	1
	global	main@j
main@j:	; 1 bytes @ 0x1
	ds	1
	global	main@couple
main@couple:	; 1 bytes @ 0x2
	ds	1
;;Data sizes: Strings 0, constant 0, data 0, bss 0, persistent 0 stack 0
;;Auto spaces:   Size  Autos    Used
;; COMMON          14      3       3
;; BANK0           80      0       0
;; BANK1           80      0       0
;; BANK3           96      0       0
;; BANK2           96      0       0

;;
;; Pointer list with targets:



;;
;; Critical Paths under _main in COMMON
;;
;;   None.
;;
;; Critical Paths under _main in BANK0
;;
;;   None.
;;
;; Critical Paths under _main in BANK1
;;
;;   None.
;;
;; Critical Paths under _main in BANK3
;;
;;   None.
;;
;; Critical Paths under _main in BANK2
;;
;;   None.

;;
;;Main: autosize = 0, tempsize = 1, incstack = 0, save=0
;;

;;
;;Call Graph Tables:
;;
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (0) _main                                                 6     6      0      60
;;                                              0 COMMON     3     3      0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 0
;; ---------------------------------------------------------------------------------

;; Call Graph Graphs:

;; _main (ROOT)
;;

;; Address spaces:

;;Name               Size   Autos  Total    Cost      Usage
;;BITCOMMON            E      0       0       0        0.0%
;;EEDATA             100      0       0       0        0.0%
;;NULL                 0      0       0       0        0.0%
;;CODE                 0      0       0       0        0.0%
;;COMMON               E      3       3       1       21.4%
;;BITSFR0              0      0       0       1        0.0%
;;SFR0                 0      0       0       1        0.0%
;;BITSFR1              0      0       0       2        0.0%
;;SFR1                 0      0       0       2        0.0%
;;STACK                0      0       0       2        0.0%
;;ABS                  0      0       0       3        0.0%
;;BITBANK0            50      0       0       4        0.0%
;;BITSFR3              0      0       0       4        0.0%
;;SFR3                 0      0       0       4        0.0%
;;BANK0               50      0       0       5        0.0%
;;BITSFR2              0      0       0       5        0.0%
;;SFR2                 0      0       0       5        0.0%
;;BITBANK1            50      0       0       6        0.0%
;;BANK1               50      0       0       7        0.0%
;;BITBANK3            60      0       0       8        0.0%
;;BANK3               60      0       0       9        0.0%
;;BITBANK2            60      0       0      10        0.0%
;;BANK2               60      0       0      11        0.0%
;;DATA                 0      0       0      12        0.0%

	global	_main
psect	maintext

;; *************** function _main *****************
;; Defined at:
;;		line 26 in file "C:\Users\Yoann\Documents\MIQ5\S1\Miqmobile\Pic\envoie_trame\envoie_trame.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  couple          1    2[COMMON] unsigned char 
;;  j               1    1[COMMON] unsigned char 
;;  i               1    0        unsigned char 
;;  check           1    0        unsigned char 
;;  code            1    0        unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 17F/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK3   BANK2
;;      Params:         0       0       0       0       0
;;      Locals:         2       0       0       0       0
;;      Temps:          1       0       0       0       0
;;      Totals:         3       0       0       0       0
;;Total ram usage:        3 bytes
;; This function calls:
;;		Nothing
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext
	file	"C:\Users\Yoann\Documents\MIQ5\S1\Miqmobile\Pic\envoie_trame\envoie_trame.c"
	line	26
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
	opt	stack 8
; Regs used in _main: [wreg+status,2+status,0]
	line	47
	
l1045:	
;envoie_trame.c: 30: char code;
;envoie_trame.c: 31: char check;
;envoie_trame.c: 32: char i,j;
;envoie_trame.c: 33: char couple;
;envoie_trame.c: 47: TXSTA=0b00000110;
	movlw	(06h)
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	movwf	(152)^080h	;volatile
	line	48
;envoie_trame.c: 48: RCSTA=0b10001110;
	movlw	(08Eh)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(24)	;volatile
	line	49
;envoie_trame.c: 49: SPBRG=20;
	movlw	(014h)
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	movwf	(153)^080h	;volatile
	line	51
	
l1047:	
;envoie_trame.c: 51: INTCON=0;
	clrf	(11)	;volatile
	line	52
	
l1049:	
;envoie_trame.c: 52: PIE1=0;
	clrf	(140)^080h	;volatile
	line	53
	
l1051:	
;envoie_trame.c: 53: TXEN=1;
	bsf	(1221/8)^080h,(1221)&7
	line	54
	
l1053:	
;envoie_trame.c: 54: SPEN=1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(199/8),(199)&7
	line	55
	
l1055:	
;envoie_trame.c: 55: TXIE=1;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bsf	(1124/8)^080h,(1124)&7
	line	56
	
l1057:	
;envoie_trame.c: 56: CREN=1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(196/8),(196)&7
	line	57
	
l1059:	
;envoie_trame.c: 57: GIE=0;
	bcf	(95/8),(95)&7
	line	58
	
l1061:	
;envoie_trame.c: 58: PEIE=1;
	bsf	(94/8),(94)&7
	line	59
	
l1063:	
;envoie_trame.c: 59: RCIE=1;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bsf	(1125/8)^080h,(1125)&7
	line	62
	
l1065:	
;envoie_trame.c: 62: TMR0IE=1;
	bsf	(93/8),(93)&7
	line	63
	
l1067:	
;envoie_trame.c: 63: T0CS=0;
	bcf	(1037/8)^080h,(1037)&7
	line	64
	
l1069:	
;envoie_trame.c: 64: PSA=1;
	bsf	(1035/8)^080h,(1035)&7
	line	65
	
l1071:	
;envoie_trame.c: 65: PS2=1;
	bsf	(1034/8)^080h,(1034)&7
	line	66
	
l1073:	
;envoie_trame.c: 66: PS1=1;
	bsf	(1033/8)^080h,(1033)&7
	line	67
	
l1075:	
;envoie_trame.c: 67: PS0=1;
	bsf	(1032/8)^080h,(1032)&7
	line	72
	
l1077:	
;envoie_trame.c: 72: TRISA=0b00000000;
	clrf	(133)^080h	;volatile
	line	73
	
l1079:	
;envoie_trame.c: 73: TRISB=0b11111111;
	movlw	(0FFh)
	movwf	(134)^080h	;volatile
	line	74
;envoie_trame.c: 74: TRISD=0b00000000;
	clrf	(136)^080h	;volatile
	line	75
;envoie_trame.c: 75: PORTA=0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(5)	;volatile
	line	76
;envoie_trame.c: 76: PORTD=0;
	clrf	(8)	;volatile
	goto	l1081
	line	78
;envoie_trame.c: 78: while(1){
	
l641:	
	line	80
	
l1081:	
;envoie_trame.c: 80: for(j=0;j<1000;j++){
	clrf	(main@j)
	goto	l1085
	
l1083:	
	goto	l1097
	
l642:	
	line	81
	
l1085:	
;envoie_trame.c: 81: TXREG=0b11011001;
	movlw	(0D9h)
	movwf	(25)	;volatile
	line	82
;envoie_trame.c: 82: while(!TXIF);
	goto	l644
	
l645:	
	
l644:	
	btfss	(100/8),(100)&7
	goto	u11
	goto	u10
u11:
	goto	l644
u10:
	
l646:	
	line	83
;envoie_trame.c: 83: TXIF=0;
	bcf	(100/8),(100)&7
	line	84
	
l1087:	
;envoie_trame.c: 84: TXREG=153;
	movlw	(099h)
	movwf	(25)	;volatile
	line	85
;envoie_trame.c: 85: while(!TXIF);
	goto	l647
	
l648:	
	
l647:	
	btfss	(100/8),(100)&7
	goto	u21
	goto	u20
u21:
	goto	l647
u20:
	
l649:	
	line	86
;envoie_trame.c: 86: TXIF=0;
	bcf	(100/8),(100)&7
	line	87
	
l1089:	
;envoie_trame.c: 87: TXREG=139;
	movlw	(08Bh)
	movwf	(25)	;volatile
	line	88
;envoie_trame.c: 88: while(!TXIF);
	goto	l650
	
l651:	
	
l650:	
	btfss	(100/8),(100)&7
	goto	u31
	goto	u30
u31:
	goto	l650
u30:
	
l652:	
	line	89
;envoie_trame.c: 89: TXIF=0;
	bcf	(100/8),(100)&7
	line	90
	
l1091:	
;envoie_trame.c: 90: couple =PORTB;
	movf	(6),w	;volatile
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(main@couple)
	line	91
;envoie_trame.c: 91: TXREG=couple;
	movf	(main@couple),w
	movwf	(25)	;volatile
	line	92
;envoie_trame.c: 92: while(!TXIF);
	goto	l653
	
l654:	
	
l653:	
	btfss	(100/8),(100)&7
	goto	u41
	goto	u40
u41:
	goto	l653
u40:
	
l655:	
	line	93
;envoie_trame.c: 93: TXIF=0;
	bcf	(100/8),(100)&7
	line	94
	
l1093:	
;envoie_trame.c: 94: TXREG=139 +couple;
	movf	(main@couple),w
	addlw	08Bh
	movwf	(25)	;volatile
	line	95
;envoie_trame.c: 95: while(!TXIF);
	goto	l656
	
l657:	
	
l656:	
	btfss	(100/8),(100)&7
	goto	u51
	goto	u50
u51:
	goto	l656
u50:
	
l658:	
	line	96
;envoie_trame.c: 96: TXIF=0;
	bcf	(100/8),(100)&7
	line	80
	
l1095:	
	movlw	(01h)
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	addwf	(main@j),f
	goto	l1085
	
l643:	
	line	104
	
l1097:	
;envoie_trame.c: 100: }
;envoie_trame.c: 104: TXREG=0b11011001;
	movlw	(0D9h)
	movwf	(25)	;volatile
	line	105
;envoie_trame.c: 105: while(!TXIF);
	goto	l659
	
l660:	
	
l659:	
	btfss	(100/8),(100)&7
	goto	u61
	goto	u60
u61:
	goto	l659
u60:
	
l661:	
	line	106
;envoie_trame.c: 106: TXIF=0;
	bcf	(100/8),(100)&7
	line	107
	
l1099:	
;envoie_trame.c: 107: TXREG=153;
	movlw	(099h)
	movwf	(25)	;volatile
	line	108
;envoie_trame.c: 108: while(!TXIF);
	goto	l662
	
l663:	
	
l662:	
	btfss	(100/8),(100)&7
	goto	u71
	goto	u70
u71:
	goto	l662
u70:
	
l664:	
	line	109
;envoie_trame.c: 109: TXIF=0;
	bcf	(100/8),(100)&7
	line	110
	
l1101:	
;envoie_trame.c: 110: TXREG=139;
	movlw	(08Bh)
	movwf	(25)	;volatile
	line	111
;envoie_trame.c: 111: while(!TXIF);
	goto	l665
	
l666:	
	
l665:	
	btfss	(100/8),(100)&7
	goto	u81
	goto	u80
u81:
	goto	l665
u80:
	
l667:	
	line	112
;envoie_trame.c: 112: TXIF=0;
	bcf	(100/8),(100)&7
	line	113
	
l1103:	
;envoie_trame.c: 113: couple =139;
	movlw	(08Bh)
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(main@couple)
	line	114
;envoie_trame.c: 114: TXREG=couple;
	movf	(main@couple),w
	movwf	(25)	;volatile
	line	115
;envoie_trame.c: 115: while(!TXIF);
	goto	l668
	
l669:	
	
l668:	
	btfss	(100/8),(100)&7
	goto	u91
	goto	u90
u91:
	goto	l668
u90:
	
l670:	
	line	116
;envoie_trame.c: 116: TXIF=0;
	bcf	(100/8),(100)&7
	line	117
	
l1105:	
;envoie_trame.c: 117: TXREG=139 +couple;
	movf	(main@couple),w
	addlw	08Bh
	movwf	(25)	;volatile
	line	118
;envoie_trame.c: 118: while(!TXIF);
	goto	l671
	
l672:	
	
l671:	
	btfss	(100/8),(100)&7
	goto	u101
	goto	u100
u101:
	goto	l671
u100:
	
l673:	
	line	119
;envoie_trame.c: 119: TXIF=0;
	bcf	(100/8),(100)&7
	goto	l1081
	line	121
	
l674:	
	line	78
	goto	l1081
	
l675:	
	line	123
	
l676:	
	global	start
	ljmp	start
	opt stack 0
GLOBAL	__end_of_main
	__end_of_main:
;; =============== function _main ends ============

	signat	_main,88
psect	maintext
	global	btemp
	btemp set 07Eh

	DABS	1,126,2	;btemp
	global	wtemp0
	wtemp0 set btemp
	end
