LOP-Win64-Shipping.exe+D5C5EF9 - FF                    - db -01
LOP-Win64-Shipping.exe+D5C5EFA - FF                    - db -01
LOP-Win64-Shipping.exe+D5C5EFB - FF                    - db -01
LOP-Win64-Shipping.exe+D5C5EFC - FF 0F                 - dec [rdi]
LOP-Win64-Shipping.exe+D5C5EFE - 1F                    - pop ds
LOP-Win64-Shipping.exe+D5C5EFF - 00 40 57              - add [rax+57],al
LOP-Win64-Shipping.exe+D5C5F02 - 48 83 EC 20           - sub rsp,20 { 32 }
LOP-Win64-Shipping.exe+D5C5F06 - 48 8B B9 38030000     - mov rdi,[rcx+00000338]
LOP-Win64-Shipping.exe+D5C5F0D - 48 85 FF              - test rdi,rdi
LOP-Win64-Shipping.exe+D5C5F10 - 0F84 87000000         - je LOP-Win64-Shipping.exe+D5C5F9D
LOP-Win64-Shipping.exe+D5C5F16 - 48 89 5C 24 30        - mov [rsp+30],rbx
LOP-Win64-Shipping.exe+D5C5F1B - 48 63 5F 50           - movsxd  rbx,dword ptr [rdi+50]
LOP-Win64-Shipping.exe+D5C5F1F - E8 EC9D78F4           - call LOP-Win64-Shipping.exe+1D4FD10
LOP-Win64-Shipping.exe+D5C5F24 - 8B 97 D0000000        - mov edx,[rdi+000000D0]
LOP-Win64-Shipping.exe+D5C5F2A - 48 89 C1              - mov rcx,rax
LOP-Win64-Shipping.exe+D5C5F2D - E8 1E796EF4           - call LOP-Win64-Shipping.exe+1CAD850
LOP-Win64-Shipping.exe+D5C5F32 - 48 85 C0              - test rax,rax
LOP-Win64-Shipping.exe+D5C5F35 - 74 59                 - je LOP-Win64-Shipping.exe+D5C5F90
LOP-Win64-Shipping.exe+D5C5F37 - 48 89 D9              - mov rcx,rbx
LOP-Win64-Shipping.exe+D5C5F3A - 85 DB                 - test ebx,ebx
LOP-Win64-Shipping.exe+D5C5F3C - 74 50                 - je LOP-Win64-Shipping.exe+D5C5F8E
LOP-Win64-Shipping.exe+D5C5F3E - 48 63 80 AC000000     - movsxd  rax,dword ptr [rax+000000AC]
LOP-Win64-Shipping.exe+D5C5F45 - 48 85 C0              - test rax,rax
LOP-Win64-Shipping.exe+D5C5F48 - 74 44                 - je LOP-Win64-Shipping.exe+D5C5F8E
LOP-Win64-Shipping.exe+D5C5F4A - 48 3D 10270000        - cmp rax,00002710 { 10000 }
LOP-Win64-Shipping.exe+D5C5F50 - 74 3E                 - je LOP-Win64-Shipping.exe+D5C5F90
LOP-Win64-Shipping.exe+D5C5F52 - 48 3D F0D8FFFF        - cmp rax,FFFFFFFFFFFFD8F0 { (3167848) }
LOP-Win64-Shipping.exe+D5C5F58 - 75 0F                 - jne LOP-Win64-Shipping.exe+D5C5F69
LOP-Win64-Shipping.exe+D5C5F5A - F7 DB                 - neg ebx
LOP-Win64-Shipping.exe+D5C5F5C - 89 D8                 - mov eax,ebx
LOP-Win64-Shipping.exe+D5C5F5E - 48 8B 5C 24 30        - mov rbx,[rsp+30]
LOP-Win64-Shipping.exe+D5C5F63 - 48 83 C4 20           - add rsp,20 { 32 }
LOP-Win64-Shipping.exe+D5C5F67 - 5F                    - pop rdi
LOP-Win64-Shipping.exe+D5C5F68 - C3                    - ret 
LOP-Win64-Shipping.exe+D5C5F69 - 0F57 C0               - xorps xmm0,xmm0
LOP-Win64-Shipping.exe+D5C5F6C - 48 0FAF C8            - imul rcx,rax
LOP-Win64-Shipping.exe+D5C5F70 - F3 48 0F2A C1         - cvtsi2ss xmm0,rcx
LOP-Win64-Shipping.exe+D5C5F75 - F3 0F59 05 B38638F9   - mulss xmm0,[LOP-Win64-Shipping.exe+694E630] { (0.00) }
LOP-Win64-Shipping.exe+D5C5F7D - F3 0F2C D8            - cvttss2si ebx,xmm0
LOP-Win64-Shipping.exe+D5C5F81 - 89 D8                 - mov eax,ebx
LOP-Win64-Shipping.exe+D5C5F83 - 48 8B 5C 24 30        - mov rbx,[rsp+30]
LOP-Win64-Shipping.exe+D5C5F88 - 48 83 C4 20           - add rsp,20 { 32 }
LOP-Win64-Shipping.exe+D5C5F8C - 5F                    - pop rdi
LOP-Win64-Shipping.exe+D5C5F8D - C3                    - ret 
LOP-Win64-Shipping.exe+D5C5F8E - 31 DB                 - xor ebx,ebx
LOP-Win64-Shipping.exe+D5C5F90 - 89 D8                 - mov eax,ebx
LOP-Win64-Shipping.exe+D5C5F92 - 48 8B 5C 24 30        - mov rbx,[rsp+30]
LOP-Win64-Shipping.exe+D5C5F97 - 48 83 C4 20           - add rsp,20 { 32 }
LOP-Win64-Shipping.exe+D5C5F9B - 5F                    - pop rdi
LOP-Win64-Shipping.exe+D5C5F9C - C3                    - ret 
