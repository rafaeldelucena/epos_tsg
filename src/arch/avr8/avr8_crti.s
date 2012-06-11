# 1 "avr8_crti.S"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "avr8_crti.S"


# This work is licensed under the EPOS Software License v1.0.
# A copy of this license is available at the EPOS system source tree root.
# A copy of this license is also available online at:
# http:
# Note that EPOS Software License applies to both source code and executables.
.weak __epos_library_app_entry
        .type __epos_library_app_entry,@function
__epos_library_app_entry:


# 1 "avr8/macros.inc" 1
# 33 "avr8/macros.inc"
# 1 "avr8/io.h" 1
# 86 "avr8/io.h"
# 1 "avr8/sfr_defs.h" 1
# 87 "avr8/io.h" 2
# 168 "avr8/io.h"
# 1 "avr8/mcu/iom128.h" 1
# 169 "avr8/io.h" 2
# 238 "avr8/io.h"
# 1 "avr8/portpins.h" 1
# 239 "avr8/io.h" 2
# 34 "avr8/macros.inc" 2
# 124 "avr8/macros.inc"
 .macro X_movw dest src
  .if ((\src) - (\dest))
   .if (((\src) | (\dest)) & 0x01)
    .if (((\src)-(\dest)) & 0x80)
     mov (\dest)+1, (\src)+1
     mov (\dest), (\src)
    .else
     mov (\dest), (\src)
     mov (\dest)+1, (\src)+1
    .endif
   .else

    movw (\dest), (\src)




   .endif
  .endif
 .endm
# 176 "avr8/macros.inc"
 .macro LPM_R0_ZPLUS_INIT hhi


 out ((((0x3B) + 0x20)) - 0x20), \hhi


 .endm

 .macro LPM_R0_ZPLUS_NEXT hhi



 elpm r0, Z+
# 206 "avr8/macros.inc"
 .endm

 .macro LPM_R0_ZP

 lpm r0, Z+




 .endm
# 14 "avr8_crti.S" 2

 .macro vector name
 .if (. - __vectors < 140)
 .weak \name
 .set \name, __epos_dynamic_handler
 call \name

 .endif
 .endm

 .section .vectors,"ax",@progbits
 .global __vectors
 .func __vectors
__vectors:
 jmp __init
 vector __vector_1
 vector __vector_2
 vector __vector_3
 vector __vector_4
 vector __vector_5
 vector __vector_6
 vector __vector_7
 vector __vector_8
 vector __vector_9
 vector __vector_10
 vector __vector_11
 vector __vector_12
 vector __vector_13
 vector __vector_14
 vector __vector_15
 vector __vector_16
 vector __vector_17
 vector __vector_18
 vector __vector_19
 vector __vector_20
 vector __vector_21
 vector __vector_22
 vector __vector_23
 vector __vector_24
 vector __vector_25
 vector __vector_26
 vector __vector_27
 vector __vector_28
 vector __vector_29
 vector __vector_30
 vector __vector_31
 vector __vector_32
 vector __vector_33
 vector __vector_34
 vector __vector_35
 vector __vector_36
 vector __vector_37
 vector __vector_38
 vector __vector_39
 vector __vector_40
 vector __vector_41
 vector __vector_42
 vector __vector_43
 vector __vector_44
 vector __vector_45
 vector __vector_46
 vector __vector_47
 vector __vector_48
 vector __vector_49
 vector __vector_50
 vector __vector_51
 vector __vector_52
 vector __vector_53
 vector __vector_54
 vector __vector_55
 vector __vector_56
 .endfunc



 .text
 .global __epos_dynamic_handler
 .func __epos_dynamic_handler
__epos_dynamic_handler:


 push r1
 push r0
 in r0, 0x3f
 push r0

 push r24

 push r28
 push r29

 in r29, 0x3e
 in r28, 0x3d
 ldd r24, Y+8

 ldd r1, Y+2
 std Y+8, r1
 ldd r1, Y+1
 std Y+7, r1
 adiw r28, 2
 out 0x3e, r29
 out 0x3d, r28

 clr r1

 push r18
 push r19
 push r20
 push r21
 push r22
 push r23

 push r25
 push r26
 push r27
 push r30
 push r31

 lsr r24
 subi r24,1

 call __epos_call_handler


 pop r31
 pop r30
 pop r27
 pop r26
 pop r25

 pop r23
 pop r22
 pop r21
 pop r20
 pop r19
 pop r18

 pop r24

 pop r0
 out 0x3f, r0
 pop r0
 pop r1

 pop r29
 pop r28

 reti
 .endfunc

 .section .init0,"ax",@progbits
 .weak __init
; .func __init
__init:


 .weak __stack
 .set __stack, 0x10FF







 .weak __heap_end
 .set __heap_end, 0

 .section .init2,"ax",@progbits
 clr r1
 out ((((0x3F) + 0x20)) - 0x20), r1
 ldi r28,lo8(__stack)

 ldi r29,hi8(__stack)
 out ((((0x3E) + 0x20)) - 0x20), r29

 out ((((0x3D) + 0x20)) - 0x20), r28





 .section .init4,"ax",@progbits
 .global __do_copy_data
__do_copy_data:
 ldi r17, hi8(__data_end)
 ldi r26, lo8(__data_start)
 ldi r27, hi8(__data_start)
 ldi r30, lo8(__data_load_start)
 ldi r31, hi8(__data_load_start)





 ldi r16, hh8(__data_load_start)





 out ((((0x3B) + 0x20)) - 0x20), r16
 rjmp .__do_copy_data_start
.__do_copy_data_loop:

 elpm r0, Z+



 st X+, r0




.__do_copy_data_start:
 cpi r26, lo8(__data_end)
 cpc r27, r17
 brne .__do_copy_data_loop




 .section .init9,"ax",@progbits
 jmp main
; .endfunc
