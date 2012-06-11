# 1 "avr8_crtend.S"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "avr8_crtend.S"
        .file "avr8_crtend.s"

# This work is licensed under the EPOS Software License v1.0.
# A copy of this license is available at the EPOS system source tree root.
# A copy of this license is also available online at:
# http:
# Note that EPOS Software License applies to both source code and executables.

 .section .text
 .global exit
exit:
 jmp _exit
