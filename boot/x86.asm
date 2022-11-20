global _bootMain
global _doInt
global _enterLong

_doInt:
    int [eax]

_enterLong:
    mov ax, 0
    mov bx, 0
    mov gs, 0

_bootMain:
    mov [0xb8000], 'A'
    mov [0xb8001], 2