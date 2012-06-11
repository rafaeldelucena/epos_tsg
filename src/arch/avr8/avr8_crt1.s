# 1 "avr8_crt1.S"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "avr8_crt1.S"
        .file "avr8_crt1.s"

# This work is licensed under the EPOS Software License v1.0.
# A copy of this license is available at the EPOS system source tree root.
# A copy of this license is also available online at:
# http:
# Note that EPOS Software License applies to both source code and executables.

        .text
        .align 1
        .globl __epos_library_app_entry
__epos_library_app_entry:
 call __epos_free_init_mem
        call main
