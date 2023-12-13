LOP-Win64-Shipping.exe+1B36F80 - 41 54                 - push r12
LOP-Win64-Shipping.exe+1B36F82 - 41 57                 - push r15
LOP-Win64-Shipping.exe+1B36F84 - 48 83 EC 48           - sub rsp,48 { 72 }
LOP-Win64-Shipping.exe+1B36F88 - 4C 8B F9              - mov r15,rcx
LOP-Win64-Shipping.exe+1B36F8B - 0F29 74 24 20         - movaps [rsp+20],xmm6
LOP-Win64-Shipping.exe+1B36F90 - 48 83 C1 08           - add rcx,08 { 8 }
LOP-Win64-Shipping.exe+1B36F94 - 0F28 F1               - movaps xmm6,xmm1
LOP-Win64-Shipping.exe+1B36F97 - E8 B41F7C00           - call LOP-Win64-Shipping.exe+22F8F50
LOP-Win64-Shipping.exe+1B36F9C - 84 C0                 - test al,al
LOP-Win64-Shipping.exe+1B36F9E - 0F84 90030000         - je LOP-Win64-Shipping.exe+1B37334
LOP-Win64-Shipping.exe+1B36FA4 - 49 8D 4F 08           - lea rcx,[r15+08]
LOP-Win64-Shipping.exe+1B36FA8 - 4C 89 74 24 30        - mov [rsp+30],r14
LOP-Win64-Shipping.exe+1B36FAD - E8 FE1F7C00           - call LOP-Win64-Shipping.exe+22F8FB0
LOP-Win64-Shipping.exe+1B36FB2 - 48 8B C8              - mov rcx,rax
LOP-Win64-Shipping.exe+1B36FB5 - E8 56B3FFFF           - call LOP-Win64-Shipping.exe+1B32310
LOP-Win64-Shipping.exe+1B36FBA - 49 8D 4F 08           - lea rcx,[r15+08]
LOP-Win64-Shipping.exe+1B36FBE - 4C 8B F0              - mov r14,rax
LOP-Win64-Shipping.exe+1B36FC1 - E8 EA1F7C00           - call LOP-Win64-Shipping.exe+22F8FB0
LOP-Win64-Shipping.exe+1B36FC6 - 48 8B C8              - mov rcx,rax
LOP-Win64-Shipping.exe+1B36FC9 - E8 A2B2FFFF           - call LOP-Win64-Shipping.exe+1B32270
LOP-Win64-Shipping.exe+1B36FCE - 4C 8B C8              - mov r9,rax
LOP-Win64-Shipping.exe+1B36FD1 - 4D 85 F6              - test r14,r14
LOP-Win64-Shipping.exe+1B36FD4 - 0F84 55030000         - je LOP-Win64-Shipping.exe+1B3732F
LOP-Win64-Shipping.exe+1B36FDA - 4C 8B 05 B3313F05     - mov r8,[LOP-Win64-Shipping.exe+6F2A194] { (373851) }
LOP-Win64-Shipping.exe+1B36FE1 - 41 8B 46 0C           - mov eax,[r14+0C]
LOP-Win64-Shipping.exe+1B36FE5 - 4C 8B 15 94313F05     - mov r10,[LOP-Win64-Shipping.exe+6F2A180] { (3E7C0900) }
LOP-Win64-Shipping.exe+1B36FEC - 41 3B C0              - cmp eax,r8d
LOP-Win64-Shipping.exe+1B36FEF - 7D 23                 - jnl LOP-Win64-Shipping.exe+1B37014
LOP-Win64-Shipping.exe+1B36FF1 - 99                    - cdq 
LOP-Win64-Shipping.exe+1B36FF2 - 0FB7 D2               - movzx edx,dx
LOP-Win64-Shipping.exe+1B36FF5 - 03 C2                 - add eax,edx
LOP-Win64-Shipping.exe+1B36FF7 - 8B C8                 - mov ecx,eax
LOP-Win64-Shipping.exe+1B36FF9 - 0FB7 C0               - movzx eax,ax
LOP-Win64-Shipping.exe+1B36FFC - 2B C2                 - sub eax,edx
LOP-Win64-Shipping.exe+1B36FFE - C1 F9 10              - sar ecx,10 { 16 }
LOP-Win64-Shipping.exe+1B37001 - 48 63 D1              - movsxd  rdx,ecx
LOP-Win64-Shipping.exe+1B37004 - 48 98                 - cdqe 
LOP-Win64-Shipping.exe+1B37006 - 48 8D 0C 40           - lea rcx,[rax+rax*2]
LOP-Win64-Shipping.exe+1B3700A - 49 8B 04 D2           - mov rax,[r10+rdx*8]
LOP-Win64-Shipping.exe+1B3700E - 48 8D 14 C8           - lea rdx,[rax+rcx*8]
LOP-Win64-Shipping.exe+1B37012 - EB 02                 - jmp LOP-Win64-Shipping.exe+1B37016
LOP-Win64-Shipping.exe+1B37014 - 33 D2                 - xor edx,edx
LOP-Win64-Shipping.exe+1B37016 - 8B 42 08              - mov eax,[rdx+08]
LOP-Win64-Shipping.exe+1B37019 - C1 E8 1D              - shr eax,1D { 29 }
LOP-Win64-Shipping.exe+1B3701C - A8 01                 - test al,01 { 1 }
LOP-Win64-Shipping.exe+1B3701E - 0F85 0B030000         - jne LOP-Win64-Shipping.exe+1B3732F
LOP-Win64-Shipping.exe+1B37024 - 4D 85 C9              - test r9,r9
LOP-Win64-Shipping.exe+1B37027 - 0F84 02030000         - je LOP-Win64-Shipping.exe+1B3732F
LOP-Win64-Shipping.exe+1B3702D - 41 8B 41 0C           - mov eax,[r9+0C]
LOP-Win64-Shipping.exe+1B37031 - 41 3B C0              - cmp eax,r8d
LOP-Win64-Shipping.exe+1B37034 - 7D 23                 - jnl LOP-Win64-Shipping.exe+1B37059
LOP-Win64-Shipping.exe+1B37036 - 99                    - cdq 
LOP-Win64-Shipping.exe+1B37037 - 0FB7 D2               - movzx edx,dx
LOP-Win64-Shipping.exe+1B3703A - 03 C2                 - add eax,edx
LOP-Win64-Shipping.exe+1B3703C - 8B C8                 - mov ecx,eax
LOP-Win64-Shipping.exe+1B3703E - 0FB7 C0               - movzx eax,ax
LOP-Win64-Shipping.exe+1B37041 - 2B C2                 - sub eax,edx
LOP-Win64-Shipping.exe+1B37043 - C1 F9 10              - sar ecx,10 { 16 }
LOP-Win64-Shipping.exe+1B37046 - 48 63 D1              - movsxd  rdx,ecx
LOP-Win64-Shipping.exe+1B37049 - 48 98                 - cdqe 
LOP-Win64-Shipping.exe+1B3704B - 48 8D 0C 40           - lea rcx,[rax+rax*2]
LOP-Win64-Shipping.exe+1B3704F - 49 8B 04 D2           - mov rax,[r10+rdx*8]
LOP-Win64-Shipping.exe+1B37053 - 48 8D 14 C8           - lea rdx,[rax+rcx*8]
LOP-Win64-Shipping.exe+1B37057 - EB 02                 - jmp LOP-Win64-Shipping.exe+1B3705B
LOP-Win64-Shipping.exe+1B37059 - 33 D2                 - xor edx,edx
LOP-Win64-Shipping.exe+1B3705B - 8B 42 08              - mov eax,[rdx+08]
LOP-Win64-Shipping.exe+1B3705E - C1 E8 1D              - shr eax,1D { 29 }
LOP-Win64-Shipping.exe+1B37061 - A8 01                 - test al,01 { 1 }
LOP-Win64-Shipping.exe+1B37063 - 0F85 C6020000         - jne LOP-Win64-Shipping.exe+1B3732F
LOP-Win64-Shipping.exe+1B37069 - 48 89 74 24 70        - mov [rsp+70],rsi
LOP-Win64-Shipping.exe+1B3706E - 49 8B B6 48020000     - mov rsi,[r14+00000248]
LOP-Win64-Shipping.exe+1B37075 - 48 85 F6              - test rsi,rsi
LOP-Win64-Shipping.exe+1B37078 - 0F84 AC020000         - je LOP-Win64-Shipping.exe+1B3732A
LOP-Win64-Shipping.exe+1B3707E - 8B 46 0C              - mov eax,[rsi+0C]
LOP-Win64-Shipping.exe+1B37081 - 41 3B C0              - cmp eax,r8d
LOP-Win64-Shipping.exe+1B37084 - 7D 23                 - jnl LOP-Win64-Shipping.exe+1B370A9
LOP-Win64-Shipping.exe+1B37086 - 99                    - cdq 
LOP-Win64-Shipping.exe+1B37087 - 0FB7 D2               - movzx edx,dx
LOP-Win64-Shipping.exe+1B3708A - 03 C2                 - add eax,edx
LOP-Win64-Shipping.exe+1B3708C - 8B C8                 - mov ecx,eax
LOP-Win64-Shipping.exe+1B3708E - 0FB7 C0               - movzx eax,ax
LOP-Win64-Shipping.exe+1B37091 - 2B C2                 - sub eax,edx
LOP-Win64-Shipping.exe+1B37093 - C1 F9 10              - sar ecx,10 { 16 }
LOP-Win64-Shipping.exe+1B37096 - 48 63 D1              - movsxd  rdx,ecx
LOP-Win64-Shipping.exe+1B37099 - 48 98                 - cdqe 
LOP-Win64-Shipping.exe+1B3709B - 48 8D 0C 40           - lea rcx,[rax+rax*2]
LOP-Win64-Shipping.exe+1B3709F - 49 8B 04 D2           - mov rax,[r10+rdx*8]
LOP-Win64-Shipping.exe+1B370A3 - 48 8D 14 C8           - lea rdx,[rax+rcx*8]
LOP-Win64-Shipping.exe+1B370A7 - EB 02                 - jmp LOP-Win64-Shipping.exe+1B370AB
LOP-Win64-Shipping.exe+1B370A9 - 33 D2                 - xor edx,edx
LOP-Win64-Shipping.exe+1B370AB - 8B 42 08              - mov eax,[rdx+08]
LOP-Win64-Shipping.exe+1B370AE - C1 E8 1D              - shr eax,1D { 29 }
LOP-Win64-Shipping.exe+1B370B1 - A8 01                 - test al,01 { 1 }
LOP-Win64-Shipping.exe+1B370B3 - 0F85 71020000         - jne LOP-Win64-Shipping.exe+1B3732A
LOP-Win64-Shipping.exe+1B370B9 - 49 8B 86 88080000     - mov rax,[r14+00000888]
LOP-Win64-Shipping.exe+1B370C0 - 48 85 C0              - test rax,rax
LOP-Win64-Shipping.exe+1B370C3 - 0F84 61020000         - je LOP-Win64-Shipping.exe+1B3732A
LOP-Win64-Shipping.exe+1B370C9 - 8B 40 0C              - mov eax,[rax+0C]
LOP-Win64-Shipping.exe+1B370CC - 41 3B C0              - cmp eax,r8d
LOP-Win64-Shipping.exe+1B370CF - 7D 23                 - jnl LOP-Win64-Shipping.exe+1B370F4
LOP-Win64-Shipping.exe+1B370D1 - 99                    - cdq 
LOP-Win64-Shipping.exe+1B370D2 - 0FB7 D2               - movzx edx,dx
LOP-Win64-Shipping.exe+1B370D5 - 03 C2                 - add eax,edx
LOP-Win64-Shipping.exe+1B370D7 - 8B C8                 - mov ecx,eax
LOP-Win64-Shipping.exe+1B370D9 - 0FB7 C0               - movzx eax,ax
LOP-Win64-Shipping.exe+1B370DC - 2B C2                 - sub eax,edx
LOP-Win64-Shipping.exe+1B370DE - C1 F9 10              - sar ecx,10 { 16 }
LOP-Win64-Shipping.exe+1B370E1 - 48 63 D1              - movsxd  rdx,ecx
LOP-Win64-Shipping.exe+1B370E4 - 48 98                 - cdqe 
LOP-Win64-Shipping.exe+1B370E6 - 48 8D 0C 40           - lea rcx,[rax+rax*2]
LOP-Win64-Shipping.exe+1B370EA - 49 8B 04 D2           - mov rax,[r10+rdx*8]
LOP-Win64-Shipping.exe+1B370EE - 48 8D 14 C8           - lea rdx,[rax+rcx*8]
LOP-Win64-Shipping.exe+1B370F2 - EB 02                 - jmp LOP-Win64-Shipping.exe+1B370F6
LOP-Win64-Shipping.exe+1B370F4 - 33 D2                 - xor edx,edx
LOP-Win64-Shipping.exe+1B370F6 - 8B 42 08              - mov eax,[rdx+08]
LOP-Win64-Shipping.exe+1B370F9 - C1 E8 1D              - shr eax,1D { 29 }
LOP-Win64-Shipping.exe+1B370FC - A8 01                 - test al,01 { 1 }
LOP-Win64-Shipping.exe+1B370FE - 0F85 26020000         - jne LOP-Win64-Shipping.exe+1B3732A
LOP-Win64-Shipping.exe+1B37104 - 48 89 5C 24 60        - mov [rsp+60],rbx
LOP-Win64-Shipping.exe+1B37109 - 49 8D 4F 08           - lea rcx,[r15+08]
LOP-Win64-Shipping.exe+1B3710D - 48 89 6C 24 68        - mov [rsp+68],rbp
LOP-Win64-Shipping.exe+1B37112 - 48 89 7C 24 40        - mov [rsp+40],rdi
LOP-Win64-Shipping.exe+1B37117 - 4C 89 6C 24 38        - mov [rsp+38],r13
LOP-Win64-Shipping.exe+1B3711C - E8 8F1E7C00           - call LOP-Win64-Shipping.exe+22F8FB0
LOP-Win64-Shipping.exe+1B37121 - 33 D2                 - xor edx,edx
LOP-Win64-Shipping.exe+1B37123 - 49 8B CE              - mov rcx,r14
LOP-Win64-Shipping.exe+1B37126 - 48 8B E8              - mov rbp,rax
LOP-Win64-Shipping.exe+1B37129 - E8 52EFF8FF           - call LOP-Win64-Shipping.exe+1AC6080
LOP-Win64-Shipping.exe+1B3712E - 49 8B 96 88080000     - mov rdx,[r14+00000888]
LOP-Win64-Shipping.exe+1B37135 - 44 0FB6 E8            - movzx r13d,al
LOP-Win64-Shipping.exe+1B37139 - 4C 63 82 D0020000     - movsxd  r8,dword ptr [rdx+000002D0]
LOP-Win64-Shipping.exe+1B37140 - 41 8D 48 FF           - lea ecx,[r8-01]
LOP-Win64-Shipping.exe+1B37144 - 85 C9                 - test ecx,ecx
LOP-Win64-Shipping.exe+1B37146 - 0F88 9B000000         - js LOP-Win64-Shipping.exe+1B371E7
LOP-Win64-Shipping.exe+1B3714C - 48 8B 8A C8020000     - mov rcx,[rdx+000002C8]
LOP-Win64-Shipping.exe+1B37153 - 4D 8D 50 FF           - lea r10,[r8-01]
LOP-Win64-Shipping.exe+1B37157 - 48 8B 1D 36303F05     - mov rbx,[LOP-Win64-Shipping.exe+6F2A194] { (373851) }
LOP-Win64-Shipping.exe+1B3715E - 48 8B 3D 1B303F05     - mov rdi,[LOP-Win64-Shipping.exe+6F2A180] { (3E7C0900) }
LOP-Win64-Shipping.exe+1B37165 - 4E 8D 1C D1           - lea r11,[rcx+r10*8]
LOP-Win64-Shipping.exe+1B37169 - 0F1F 80 00000000      - nop dword ptr [rax+00000000]
LOP-Win64-Shipping.exe+1B37170 - 4D 8B 03              - mov r8,[r11]
LOP-Win64-Shipping.exe+1B37173 - 4D 85 C0              - test r8,r8
LOP-Win64-Shipping.exe+1B37176 - 74 65                 - je LOP-Win64-Shipping.exe+1B371DD
LOP-Win64-Shipping.exe+1B37178 - 45 8B 48 0C           - mov r9d,[r8+0C]
LOP-Win64-Shipping.exe+1B3717C - 44 3B CB              - cmp r9d,ebx
LOP-Win64-Shipping.exe+1B3717F - 7D 30                 - jnl LOP-Win64-Shipping.exe+1B371B1
LOP-Win64-Shipping.exe+1B37181 - 41 0FB7 C9            - movzx ecx,r9w
LOP-Win64-Shipping.exe+1B37185 - 41 8B C1              - mov eax,r9d
LOP-Win64-Shipping.exe+1B37188 - 45 85 C9              - test r9d,r9d
LOP-Win64-Shipping.exe+1B3718B - 79 0D                 - jns LOP-Win64-Shipping.exe+1B3719A
LOP-Win64-Shipping.exe+1B3718D - 41 8D 81 FFFF0000     - lea eax,[r9+0000FFFF]
LOP-Win64-Shipping.exe+1B37194 - 81 E9 00000100        - sub ecx,00010000 { (0) }
LOP-Win64-Shipping.exe+1B3719A - C1 F8 10              - sar eax,10 { 16 }
LOP-Win64-Shipping.exe+1B3719D - 48 63 D0              - movsxd  rdx,eax
LOP-Win64-Shipping.exe+1B371A0 - 48 63 C1              - movsxd  rax,ecx
LOP-Win64-Shipping.exe+1B371A3 - 48 8D 0C 40           - lea rcx,[rax+rax*2]
LOP-Win64-Shipping.exe+1B371A7 - 48 8B 04 D7           - mov rax,[rdi+rdx*8]
LOP-Win64-Shipping.exe+1B371AB - 48 8D 14 C8           - lea rdx,[rax+rcx*8]
LOP-Win64-Shipping.exe+1B371AF - EB 02                 - jmp LOP-Win64-Shipping.exe+1B371B3
LOP-Win64-Shipping.exe+1B371B1 - 33 D2                 - xor edx,edx
LOP-Win64-Shipping.exe+1B371B3 - 8B 42 08              - mov eax,[rdx+08]
LOP-Win64-Shipping.exe+1B371B6 - C1 E8 1D              - shr eax,1D { 29 }
LOP-Win64-Shipping.exe+1B371B9 - A8 01                 - test al,01 { 1 }
LOP-Win64-Shipping.exe+1B371BB - 75 20                 - jne LOP-Win64-Shipping.exe+1B371DD
LOP-Win64-Shipping.exe+1B371BD - 41 80 B8 C0000000 00  - cmp byte ptr [r8+000000C0],00 { 0 }
LOP-Win64-Shipping.exe+1B371C5 - 74 16                 - je LOP-Win64-Shipping.exe+1B371DD
LOP-Win64-Shipping.exe+1B371C7 - 41 0FB6 50 68         - movzx edx,byte ptr [r8+68]
LOP-Win64-Shipping.exe+1B371CC - 8B CA                 - mov ecx,edx
LOP-Win64-Shipping.exe+1B371CE - 83 E9 2B              - sub ecx,2B { 43 }
LOP-Win64-Shipping.exe+1B371D1 - 74 0A                 - je LOP-Win64-Shipping.exe+1B371DD
LOP-Win64-Shipping.exe+1B371D3 - 83 F9 01              - cmp ecx,01 { 1 }
LOP-Win64-Shipping.exe+1B371D6 - 74 05                 - je LOP-Win64-Shipping.exe+1B371DD
LOP-Win64-Shipping.exe+1B371D8 - 80 FA 1E              - cmp dl,1E { 30 }
LOP-Win64-Shipping.exe+1B371DB - 75 57                 - jne LOP-Win64-Shipping.exe+1B37234
LOP-Win64-Shipping.exe+1B371DD - 49 83 EB 08           - sub r11,08 { 8 }
LOP-Win64-Shipping.exe+1B371E1 - 49 83 EA 01           - sub r10,01 { 1 }
LOP-Win64-Shipping.exe+1B371E5 - 79 89                 - jns LOP-Win64-Shipping.exe+1B37170
LOP-Win64-Shipping.exe+1B371E7 - 40 32 FF              - xor dil,dil
LOP-Win64-Shipping.exe+1B371EA - F3 0F10 86 C4000000   - movss xmm0,[rsi+000000C4]
LOP-Win64-Shipping.exe+1B371F2 - F3 0F10 0D 2687E104   - movss xmm1,[LOP-Win64-Shipping.exe+694F920] { (Nan) }
LOP-Win64-Shipping.exe+1B371FA - F3 0F10 15 E63BE104   - movss xmm2,[LOP-Win64-Shipping.exe+694ADE8] { (0.00) }
LOP-Win64-Shipping.exe+1B37202 - 0F54 C1               - andps xmm0,xmm1
LOP-Win64-Shipping.exe+1B37205 - 0F2F C2               - comiss xmm0,xmm2
LOP-Win64-Shipping.exe+1B37208 - 77 77                 - ja LOP-Win64-Shipping.exe+1B37281
LOP-Win64-Shipping.exe+1B3720A - F3 0F10 86 C8000000   - movss xmm0,[rsi+000000C8]
LOP-Win64-Shipping.exe+1B37212 - 0F54 C1               - andps xmm0,xmm1
LOP-Win64-Shipping.exe+1B37215 - 0F2F C2               - comiss xmm0,xmm2
LOP-Win64-Shipping.exe+1B37218 - 77 67                 - ja LOP-Win64-Shipping.exe+1B37281
LOP-Win64-Shipping.exe+1B3721A - F3 0F10 86 CC000000   - movss xmm0,[rsi+000000CC]
LOP-Win64-Shipping.exe+1B37222 - 0F54 C1               - andps xmm0,xmm1
LOP-Win64-Shipping.exe+1B37225 - 0F2F C2               - comiss xmm0,xmm2
LOP-Win64-Shipping.exe+1B37228 - 77 57                 - ja LOP-Win64-Shipping.exe+1B37281
LOP-Win64-Shipping.exe+1B3722A - 41 80 FD 0D           - cmp r13b,0D { 13 }
LOP-Win64-Shipping.exe+1B3722E - 74 51                 - je LOP-Win64-Shipping.exe+1B37281
LOP-Win64-Shipping.exe+1B37230 - 32 DB                 - xor bl,bl
LOP-Win64-Shipping.exe+1B37232 - EB 4F                 - jmp LOP-Win64-Shipping.exe+1B37283
LOP-Win64-Shipping.exe+1B37234 - 44 3B CB              - cmp r9d,ebx
LOP-Win64-Shipping.exe+1B37237 - 7D 26                 - jnl LOP-Win64-Shipping.exe+1B3725F
LOP-Win64-Shipping.exe+1B37239 - 41 8B C1              - mov eax,r9d
LOP-Win64-Shipping.exe+1B3723C - 99                    - cdq 
LOP-Win64-Shipping.exe+1B3723D - 0FB7 D2               - movzx edx,dx
LOP-Win64-Shipping.exe+1B37240 - 03 C2                 - add eax,edx
LOP-Win64-Shipping.exe+1B37242 - 8B C8                 - mov ecx,eax
LOP-Win64-Shipping.exe+1B37244 - 0FB7 C0               - movzx eax,ax
LOP-Win64-Shipping.exe+1B37247 - 2B C2                 - sub eax,edx
LOP-Win64-Shipping.exe+1B37249 - C1 F9 10              - sar ecx,10 { 16 }
LOP-Win64-Shipping.exe+1B3724C - 48 63 D1              - movsxd  rdx,ecx
LOP-Win64-Shipping.exe+1B3724F - 48 98                 - cdqe 
LOP-Win64-Shipping.exe+1B37251 - 48 8D 0C 40           - lea rcx,[rax+rax*2]
LOP-Win64-Shipping.exe+1B37255 - 48 8B 04 D7           - mov rax,[rdi+rdx*8]
LOP-Win64-Shipping.exe+1B37259 - 48 8D 14 C8           - lea rdx,[rax+rcx*8]
LOP-Win64-Shipping.exe+1B3725D - EB 02                 - jmp LOP-Win64-Shipping.exe+1B37261
LOP-Win64-Shipping.exe+1B3725F - 33 D2                 - xor edx,edx
LOP-Win64-Shipping.exe+1B37261 - 8B 42 08              - mov eax,[rdx+08]

LOP-Win64-Shipping.exe+1B37264 - C1 E8 1D              - shr eax,1D { 29 }
LOP-Win64-Shipping.exe+1B37267 - A8 01                 - test al,01 { 1 }
LOP-Win64-Shipping.exe+1B37269 - 0F85 78FFFFFF         - jne LOP-Win64-Shipping.exe+1B371E7
LOP-Win64-Shipping.exe+1B3726F - 41 80 FD 0D           - cmp r13b,0D { 13 }
LOP-Win64-Shipping.exe+1B37273 - 0F84 6EFFFFFF         - je LOP-Win64-Shipping.exe+1B371E7
LOP-Win64-Shipping.exe+1B37279 - 40 B7 01              - mov dil,01 { 1 }
LOP-Win64-Shipping.exe+1B3727C - E9 69FFFFFF           - jmp LOP-Win64-Shipping.exe+1B371EA
LOP-Win64-Shipping.exe+1B37281 - B3 01                 - mov bl,01 { 1 }
LOP-Win64-Shipping.exe+1B37283 - E8 D8862100           - call LOP-Win64-Shipping.exe+1D4F960 { was following this }
LOP-Win64-Shipping.exe+1B37288 - 45 0FB6 8E 90040000   - movzx r9d,byte ptr [r14+00000490]
LOP-Win64-Shipping.exe+1B37290 - 49 8D 4F 08           - lea rcx,[r15+08]

LOP-Win64-Shipping.exe+1B37294 - 41 80 E1 03           - and r9b,03 { 3 }
LOP-Win64-Shipping.exe+1B37298 - 44 0FB6 90 C0000000   - movzx r10d,byte ptr [rax+000000C0]
LOP-Win64-Shipping.exe+1B372A0 - E8 0B1D7C00           - call LOP-Win64-Shipping.exe+22F8FB0
LOP-Win64-Shipping.exe+1B372A5 - 4C 8B 6C 24 38        - mov r13,[rsp+38]
LOP-Win64-Shipping.exe+1B372AA - 80 B8 F22B0000 00     - cmp byte ptr [rax+00002BF2],00 { 0 }
LOP-Win64-Shipping.exe+1B372B1 - 74 54                 - je LOP-Win64-Shipping.exe+1B37307
LOP-Win64-Shipping.exe+1B372B3 - 8B 86 F0020000        - mov eax,[rsi+000002F0]
LOP-Win64-Shipping.exe+1B372B9 - 83 E0 03              - and eax,03 { 3 }
LOP-Win64-Shipping.exe+1B372BC - 3C 03                 - cmp al,03 { 3 }
LOP-Win64-Shipping.exe+1B372BE - 75 47                 - jne LOP-Win64-Shipping.exe+1B37307
LOP-Win64-Shipping.exe+1B372C0 - 84 DB                 - test bl,bl
LOP-Win64-Shipping.exe+1B372C2 - 74 43                 - je LOP-Win64-Shipping.exe+1B37307
LOP-Win64-Shipping.exe+1B372C4 - 40 84 FF              - test dil,dil
LOP-Win64-Shipping.exe+1B372C7 - 75 3E                 - jne LOP-Win64-Shipping.exe+1B37307
LOP-Win64-Shipping.exe+1B372C9 - 45 84 D2              - test r10b,r10b
LOP-Win64-Shipping.exe+1B372CC - 75 39                 - jne LOP-Win64-Shipping.exe+1B37307
LOP-Win64-Shipping.exe+1B372CE - 45 84 C9              - test r9b,r9b
LOP-Win64-Shipping.exe+1B372D1 - 75 34                 - jne LOP-Win64-Shipping.exe+1B37307
LOP-Win64-Shipping.exe+1B372D3 - 0F57 C0               - xorps xmm0,xmm0
LOP-Win64-Shipping.exe+1B372D6 - 0F2F F0               - comiss xmm6,xmm0
LOP-Win64-Shipping.exe+1B372D9 - 76 40                 - jna LOP-Win64-Shipping.exe+1B3731B
LOP-Win64-Shipping.exe+1B372DB - F3 41 0F10 47 24      - movss xmm0,[r15+24]
LOP-Win64-Shipping.exe+1B372E1 - 0F2F 85 082B0000      - comiss xmm0,[rbp+00002B08]
LOP-Win64-Shipping.exe+1B372E8 - 72 11                 - jb LOP-Win64-Shipping.exe+1B372FB
LOP-Win64-Shipping.exe+1B372EA - 0F28 CE               - movaps xmm1,xmm6
LOP-Win64-Shipping.exe+1B372ED - 48 8D 8D 082B0000     - lea rcx,[rbp+00002B08]
LOP-Win64-Shipping.exe+1B372F4 - E8 57B8FFFF           - call LOP-Win64-Shipping.exe+1B32B50
LOP-Win64-Shipping.exe+1B372F9 - EB 20                 - jmp LOP-Win64-Shipping.exe+1B3731B
LOP-Win64-Shipping.exe+1B372FB - F3 0F58 C6            - addss xmm0,xmm6
LOP-Win64-Shipping.exe+1B372FF - F3 41 0F11 47 24      - movss [r15+24],xmm0
LOP-Win64-Shipping.exe+1B37305 - EB 14                 - jmp LOP-Win64-Shipping.exe+1B3731B
LOP-Win64-Shipping.exe+1B37307 - 48 8D 8D 082B0000     - lea rcx,[rbp+00002B08]
LOP-Win64-Shipping.exe+1B3730E - E8 5DC1FFFF           - call LOP-Win64-Shipping.exe+1B33470
LOP-Win64-Shipping.exe+1B37313 - 41 C7 47 24 00000000  - mov [r15+24],00000000 { 0 }
LOP-Win64-Shipping.exe+1B3731B - 48 8B 7C 24 40        - mov rdi,[rsp+40]
LOP-Win64-Shipping.exe+1B37320 - 48 8B 6C 24 68        - mov rbp,[rsp+68]
LOP-Win64-Shipping.exe+1B37325 - 48 8B 5C 24 60        - mov rbx,[rsp+60]
LOP-Win64-Shipping.exe+1B3732A - 48 8B 74 24 70        - mov rsi,[rsp+70]
LOP-Win64-Shipping.exe+1B3732F - 4C 8B 74 24 30        - mov r14,[rsp+30]
LOP-Win64-Shipping.exe+1B37334 - 0F28 74 24 20         - movaps xmm6,[rsp+20]
LOP-Win64-Shipping.exe+1B37339 - 48 83 C4 48           - add rsp,48 { 72 }
LOP-Win64-Shipping.exe+1B3733D - 41 5F                 - pop r15
LOP-Win64-Shipping.exe+1B3733F - 41 5C                 - pop r12
LOP-Win64-Shipping.exe+1B37341 - C3                    - ret 


C1 E8 1D
A8 01
0F 85 ?? ?? ?? ??
41 80 FD 0D
0F 84 ?? ?? ?? ??
40 B7 01
E9 ?? ?? ?? ??
B3 01
E8 ?? ?? ?? ??
45 0F B6 8E ?? ?? ?? ??
49 8D 4F 08


D8 86 21 00
00 21 86 D8

141B37288

141D4F960