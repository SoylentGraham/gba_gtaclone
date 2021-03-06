@********************************************************************
@*          crt0.s                                                  *
@  This file is a hack. It is not meant for serious work.           *
@********************************************************************
    .TEXT

    .GLOBAL     _start
_start:
        .ALIGN
        .CODE 32
        @ Start Vector
rom_header:     b       rom_header_end

        @ Nintendo Logo Character Data (8000004h)
                .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                .byte   0x00,0x00,0x00,0x00

        @ Software Titles (80000A0h)
                .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                .byte   0x00,0x00,0x00,0x00

        @ Initial Code (80000ACh)
                .byte   0x00,0x00,0x00,0x00

        @ Maker Code (80000B0h)
                .byte   0x30,0x31

        @ Fixed Value (80000B2h)
                .byte   0x96

        @ Main Unit Code (80000B3h)
                .byte   0x00

        @ Device Type (80000B4h)
                .byte   0x00

        @ Unused Data (7Byte) (80000B5h)
                .byte   0x00,0x00,0x00,0x00,0x00,0x00,0x00

        @ Software Version No (80000BCh)
                .byte   0x00

        @ Complement Check (80000BDh)
                .byte   0xf0

        @ Check Sum (80000BEh)
                .byte   0x00,0x00

rom_header_end:

@--------------------------------------------------------------------
@-                          Reset                                   -
@--------------------------------------------------------------------
    .EXTERN     AgbMain
    .GLOBAL     start_vector
    .CODE 32
    .ALIGN
start_vector:
        mov     r0, #0x12               @ Switch to IRQ Mode
        msr     cpsr, r0
        ldr     sp, sp_irq              @ Set SP_irq
        mov     r0, #0x1f               @ Switch to System Mode
        msr     cpsr, r0
        ldr     sp, sp_usr              @ Set SP_usr
        str     r0, [r1]
        ldr     r1, =AgbMain            @ Start & Switch to 16bit Code
        mov     lr, pc
        bx      r1
        b       start_vector            @ Reset

    .ALIGN
sp_usr: .word   0x3008000 - 0x100
sp_irq: .word   0x3008000 - 0x60

    .ALIGN
    .CODE 32

    .END

