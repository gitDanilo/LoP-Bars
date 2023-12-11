LOP-Win64-Shipping.exe+E54A00 - 48 89 5C 24 08        - mov [rsp+08],rbx
LOP-Win64-Shipping.exe+E54A05 - 48 89 6C 24 10        - mov [rsp+10],rbp
LOP-Win64-Shipping.exe+E54A0A - 48 89 74 24 18        - mov [rsp+18],rsi
LOP-Win64-Shipping.exe+E54A0F - 57                    - push rdi
LOP-Win64-Shipping.exe+E54A10 - 48 83 EC 60           - sub rsp,60 { 96 }
LOP-Win64-Shipping.exe+E54A14 - 49 8B C0              - mov rax,r8
LOP-Win64-Shipping.exe+E54A17 - 49 8B D8              - mov rbx,r8
LOP-Win64-Shipping.exe+E54A1A - 48 C1 E8 20           - shr rax,20 { 32 }
LOP-Win64-Shipping.exe+E54A1E - 41 8B F1              - mov esi,r9d
LOP-Win64-Shipping.exe+E54A21 - 85 C0                 - test eax,eax
LOP-Win64-Shipping.exe+E54A23 - 48 8B EA              - mov rbp,rdx
LOP-Win64-Shipping.exe+E54A26 - 48 8B F9              - mov rdi,rcx
LOP-Win64-Shipping.exe+E54A29 - 41 0F94 C0            - sete r8b
LOP-Win64-Shipping.exe+E54A2D - 3B 1D CDF43806        - cmp ebx,[LOP-Win64-Shipping.exe+71E3F00] { (0) }
LOP-Win64-Shipping.exe+E54A33 - 0F94 C0               - sete al
LOP-Win64-Shipping.exe+E54A36 - 44 84 C0              - test al,r8b
LOP-Win64-Shipping.exe+E54A39 - 74 05                 - je LOP-Win64-Shipping.exe+E54A40
LOP-Win64-Shipping.exe+E54A3B - E8 E02B4901           - call LOP-Win64-Shipping.exe+22E7620
LOP-Win64-Shipping.exe+E54A40 - 33 C0                 - xor eax,eax
LOP-Win64-Shipping.exe+E54A42 - 48 89 6C 24 20        - mov [rsp+20],rbp
LOP-Win64-Shipping.exe+E54A47 - 0F57 C0               - xorps xmm0,xmm0
LOP-Win64-Shipping.exe+E54A4A - 89 44 24 3C           - mov [rsp+3C],eax
LOP-Win64-Shipping.exe+E54A4E - 48 8D 4C 24 20        - lea rcx,[rsp+20]
LOP-Win64-Shipping.exe+E54A53 - 66 89 44 24 40        - mov [rsp+40],ax
LOP-Win64-Shipping.exe+E54A58 - 48 89 44 24 48        - mov [rsp+48],rax
LOP-Win64-Shipping.exe+E54A5D - 66 0F7F 44 24 50      - movdqa [rsp+50],xmm0
LOP-Win64-Shipping.exe+E54A63 - 48 89 7C 24 28        - mov [rsp+28],rdi
LOP-Win64-Shipping.exe+E54A68 - 48 89 5C 24 30        - mov [rsp+30],rbx
LOP-Win64-Shipping.exe+E54A6D - 89 74 24 38           - mov [rsp+38],esi
LOP-Win64-Shipping.exe+E54A71 - E8 FA294901           - call LOP-Win64-Shipping.exe+22E7470
LOP-Win64-Shipping.exe+E54A76 - 48 8B 5C 24 70        - mov rbx,[rsp+70]
LOP-Win64-Shipping.exe+E54A7B - 48 8B 6C 24 78        - mov rbp,[rsp+78]
LOP-Win64-Shipping.exe+E54A80 - 48 8B B4 24 80000000  - mov rsi,[rsp+00000080]
LOP-Win64-Shipping.exe+E54A88 - 48 83 C4 60           - add rsp,60 { 96 }
LOP-Win64-Shipping.exe+E54A8C - 5F                    - pop rdi
LOP-Win64-Shipping.exe+E54A8D - C3                    - ret 
