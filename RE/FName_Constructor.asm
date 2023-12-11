LOP-Win64-Shipping.exe+20BA1F0 - 48 89 5C 24 08        - mov [rsp+08],rbx
LOP-Win64-Shipping.exe+20BA1F5 - 57                    - push rdi
LOP-Win64-Shipping.exe+20BA1F6 - 48 83 EC 30           - sub rsp,30 { 48 }
LOP-Win64-Shipping.exe+20BA1FA - 48 8B D9              - mov rbx,rcx
LOP-Win64-Shipping.exe+20BA1FD - 48 89 54 24 20        - mov [rsp+20],rdx
LOP-Win64-Shipping.exe+20BA202 - 33 C9                 - xor ecx,ecx
LOP-Win64-Shipping.exe+20BA204 - 41 8B F8              - mov edi,r8d
LOP-Win64-Shipping.exe+20BA207 - 4C 8B DA              - mov r11,rdx
LOP-Win64-Shipping.exe+20BA20A - 44 8B D1              - mov r10d,ecx
LOP-Win64-Shipping.exe+20BA20D - 4C 8B CA              - mov r9,rdx
LOP-Win64-Shipping.exe+20BA210 - 48 85 D2              - test rdx,rdx
LOP-Win64-Shipping.exe+20BA213 - 74 1E                 - je LOP-Win64-Shipping.exe+20BA233
LOP-Win64-Shipping.exe+20BA215 - 0FB7 02               - movzx eax,word ptr [rdx]
LOP-Win64-Shipping.exe+20BA218 - 66 85 C0              - test ax,ax
LOP-Win64-Shipping.exe+20BA21B - 74 16                 - je LOP-Win64-Shipping.exe+20BA233
LOP-Win64-Shipping.exe+20BA21D - 0F1F 00               - nop dword ptr [rax]
LOP-Win64-Shipping.exe+20BA220 - 49 83 C1 02           - add r9,02 { 2 }
LOP-Win64-Shipping.exe+20BA224 - 0FB7 C0               - movzx eax,ax
LOP-Win64-Shipping.exe+20BA227 - 44 0B D0              - or r10d,eax
LOP-Win64-Shipping.exe+20BA22A - 41 0FB7 01            - movzx eax,word ptr [r9]
LOP-Win64-Shipping.exe+20BA22E - 66 85 C0              - test ax,ax
LOP-Win64-Shipping.exe+20BA231 - 75 ED                 - jne LOP-Win64-Shipping.exe+20BA220
LOP-Win64-Shipping.exe+20BA233 - 41 F7 C2 80FFFFFF     - test r10d,FFFFFF80 { (0) }
LOP-Win64-Shipping.exe+20BA23A - 0F95 44 24 2C         - setne byte ptr [rsp+2C]
LOP-Win64-Shipping.exe+20BA23F - 4D 2B CB              - sub r9,r11
LOP-Win64-Shipping.exe+20BA242 - 49 D1 F9              - sar r9,1
LOP-Win64-Shipping.exe+20BA245 - 44 89 4C 24 28        - mov [rsp+28],r9d
LOP-Win64-Shipping.exe+20BA24A - 0F28 44 24 20         - movaps xmm0,[rsp+20]
LOP-Win64-Shipping.exe+20BA24F - 66 0F7F 44 24 20      - movdqa [rsp+20],xmm0
LOP-Win64-Shipping.exe+20BA255 - 45 85 C9              - test r9d,r9d
LOP-Win64-Shipping.exe+20BA258 - 75 11                 - jne LOP-Win64-Shipping.exe+20BA26B
LOP-Win64-Shipping.exe+20BA25A - 48 89 0B              - mov [rbx],rcx
LOP-Win64-Shipping.exe+20BA25D - 48 8B C3              - mov rax,rbx
LOP-Win64-Shipping.exe+20BA260 - 48 8B 5C 24 40        - mov rbx,[rsp+40]
LOP-Win64-Shipping.exe+20BA265 - 48 83 C4 30           - add rsp,30 { 48 }
LOP-Win64-Shipping.exe+20BA269 - 5F                    - pop rdi
LOP-Win64-Shipping.exe+20BA26A - C3                    - ret 
LOP-Win64-Shipping.exe+20BA26B - 48 8D 54 24 28        - lea rdx,[rsp+28]
LOP-Win64-Shipping.exe+20BA270 - 49 8B CB              - mov rcx,r11
LOP-Win64-Shipping.exe+20BA273 - E8 E8870000           - call LOP-Win64-Shipping.exe+20C2A60
LOP-Win64-Shipping.exe+20BA278 - 0F28 44 24 20         - movaps xmm0,[rsp+20]
LOP-Win64-Shipping.exe+20BA27D - 48 8D 54 24 20        - lea rdx,[rsp+20]
LOP-Win64-Shipping.exe+20BA282 - 44 8B C8              - mov r9d,eax
LOP-Win64-Shipping.exe+20BA285 - 66 0F7F 44 24 20      - movdqa [rsp+20],xmm0
LOP-Win64-Shipping.exe+20BA28B - 44 8B C7              - mov r8d,edi
LOP-Win64-Shipping.exe+20BA28E - 48 8B CB              - mov rcx,rbx
LOP-Win64-Shipping.exe+20BA291 - E8 EAFAFFFF           - call LOP-Win64-Shipping.exe+20B9D80
LOP-Win64-Shipping.exe+20BA296 - 48 8B C3              - mov rax,rbx
LOP-Win64-Shipping.exe+20BA299 - 48 8B 5C 24 40        - mov rbx,[rsp+40]
LOP-Win64-Shipping.exe+20BA29E - 48 83 C4 30           - add rsp,30 { 48 }
LOP-Win64-Shipping.exe+20BA2A2 - 5F                    - pop rdi
LOP-Win64-Shipping.exe+20BA2A3 - C3                    - ret 
