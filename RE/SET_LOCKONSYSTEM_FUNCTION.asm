LOP-Win64-Shipping.exe+E179EC0 - 48 83 EC 28           - sub rsp,28 { 40 }
LOP-Win64-Shipping.exe+E179EC4 - 48 8B 05 6D7808F9     - mov rax,[LOP-Win64-Shipping.exe+7201738] { (9C793740) }
LOP-Win64-Shipping.exe+E179ECB - 48 85 C0              - test rax,rax
LOP-Win64-Shipping.exe+E179ECE - 0F85 0C010000         - jne LOP-Win64-Shipping.exe+E179FE0
LOP-Win64-Shipping.exe+E179ED4 - 44 8B 05 110FD5F8     - mov r8d,[LOP-Win64-Shipping.exe+6ECADEC] { (1144) }
LOP-Win64-Shipping.exe+E179EDB - 48 89 5C 24 30        - mov [rsp+30],rbx
LOP-Win64-Shipping.exe+E179EE0 - 45 85 C0              - test r8d,r8d
LOP-Win64-Shipping.exe+E179EE3 - 0F84 C6000000         - je LOP-Win64-Shipping.exe+E179FAF
LOP-Win64-Shipping.exe+E179EE9 - 48 8B 05 F80ED5F8     - mov rax,[LOP-Win64-Shipping.exe+6ECADE8] { (30368) }
LOP-Win64-Shipping.exe+E179EF0 - 85 C0                 - test eax,eax
LOP-Win64-Shipping.exe+E179EF2 - 0F88 B7000000         - js LOP-Win64-Shipping.exe+E179FAF
LOP-Win64-Shipping.exe+E179EF8 - 3B 05 9602DBF8        - cmp eax,[LOP-Win64-Shipping.exe+6F2A194] { (115671) }
LOP-Win64-Shipping.exe+E179EFE - 0F8D AB000000         - jnl LOP-Win64-Shipping.exe+E179FAF
LOP-Win64-Shipping.exe+E179F04 - 99                    - cdq 
LOP-Win64-Shipping.exe+E179F05 - 0FB7 D2               - movzx edx,dx
LOP-Win64-Shipping.exe+E179F08 - 01 D0                 - add eax,edx
LOP-Win64-Shipping.exe+E179F0A - 89 C1                 - mov ecx,eax
LOP-Win64-Shipping.exe+E179F0C - 0FB7 C0               - movzx eax,ax
LOP-Win64-Shipping.exe+E179F0F - 29 D0                 - sub eax,edx
LOP-Win64-Shipping.exe+E179F11 - C1 F9 10              - sar ecx,10 { 16 }
LOP-Win64-Shipping.exe+E179F14 - 48 98                 - cdqe 
LOP-Win64-Shipping.exe+E179F16 - 48 63 C9              - movsxd  rcx,ecx
LOP-Win64-Shipping.exe+E179F19 - 48 8D 14 40           - lea rdx,[rax+rax*2]
LOP-Win64-Shipping.exe+E179F1D - 48 8B 05 5C02DBF8     - mov rax,[LOP-Win64-Shipping.exe+6F2A180] { (3E7C0900) }
LOP-Win64-Shipping.exe+E179F24 - 48 8B 0C C8           - mov rcx,[rax+rcx*8]
LOP-Win64-Shipping.exe+E179F28 - 48 8D 04 D1           - lea rax,[rcx+rdx*8]
LOP-Win64-Shipping.exe+E179F2C - 48 85 C0              - test rax,rax
LOP-Win64-Shipping.exe+E179F2F - 74 7E                 - je LOP-Win64-Shipping.exe+E179FAF
LOP-Win64-Shipping.exe+E179F31 - 8B 48 10              - mov ecx,[rax+10]
LOP-Win64-Shipping.exe+E179F34 - 44 39 C1              - cmp ecx,r8d
LOP-Win64-Shipping.exe+E179F37 - 75 76                 - jne LOP-Win64-Shipping.exe+E179FAF
LOP-Win64-Shipping.exe+E179F39 - F7 40 08 00000030     - test [rax+08],30000000 { 805306368 }
LOP-Win64-Shipping.exe+E179F40 - 75 6D                 - jne LOP-Win64-Shipping.exe+E179FAF
LOP-Win64-Shipping.exe+E179F42 - 48 89 7C 24 20        - mov [rsp+20],rdi
LOP-Win64-Shipping.exe+E179F47 - 44 39 C1              - cmp ecx,r8d
LOP-Win64-Shipping.exe+E179F4A - 75 05                 - jne LOP-Win64-Shipping.exe+E179F51
LOP-Win64-Shipping.exe+E179F4C - 48 8B 38              - mov rdi,[rax]
LOP-Win64-Shipping.exe+E179F4F - EB 02                 - jmp LOP-Win64-Shipping.exe+E179F53
LOP-Win64-Shipping.exe+E179F51 - 31 FF                 - xor edi,edi
LOP-Win64-Shipping.exe+E179F53 - E8 08EBBAF3           - call LOP-Win64-Shipping.exe+1D28A60
LOP-Win64-Shipping.exe+E179F58 - 48 89 C3              - mov rbx,rax
LOP-Win64-Shipping.exe+E179F5B - 48 85 C0              - test rax,rax
LOP-Win64-Shipping.exe+E179F5E - 74 24                 - je LOP-Win64-Shipping.exe+E179F84
LOP-Win64-Shipping.exe+E179F60 - E8 FBEABAF3           - call LOP-Win64-Shipping.exe+1D28A60
LOP-Win64-Shipping.exe+E179F65 - 48 85 C0              - test rax,rax
LOP-Win64-Shipping.exe+E179F68 - 74 1A                 - je LOP-Win64-Shipping.exe+E179F84
LOP-Win64-Shipping.exe+E179F6A - 48 8D 50 30           - lea rdx,[rax+30]
LOP-Win64-Shipping.exe+E179F6E - 48 63 40 38           - movsxd  rax,dword ptr [rax+38]
LOP-Win64-Shipping.exe+E179F72 - 3B 43 38              - cmp eax,[rbx+38]
LOP-Win64-Shipping.exe+E179F75 - 7F 0D                 - jg LOP-Win64-Shipping.exe+E179F84
LOP-Win64-Shipping.exe+E179F77 - 48 89 C1              - mov rcx,rax
LOP-Win64-Shipping.exe+E179F7A - 48 8B 43 30           - mov rax,[rbx+30]
LOP-Win64-Shipping.exe+E179F7E - 48 39 14 C8           - cmp [rax+rcx*8],rdx
LOP-Win64-Shipping.exe+E179F82 - 74 02                 - je LOP-Win64-Shipping.exe+E179F86
LOP-Win64-Shipping.exe+E179F84 - 31 DB                 - xor ebx,ebx
LOP-Win64-Shipping.exe+E179F86 - 8B 15 F46AA507        - mov edx,[LOP-Win64-Shipping.exe+15BD0A80] { (256647367) }
LOP-Win64-Shipping.exe+E179F8C - 81 EA E71F4C0F        - sub edx,0F4C1FE7 { (0) }
LOP-Win64-Shipping.exe+E179F92 - 48 8D 0C 17           - lea rcx,[rdi+rdx]
LOP-Win64-Shipping.exe+E179F96 - 48 89 DA              - mov rdx,rbx
LOP-Win64-Shipping.exe+E179F99 - E8 929FE8F5           - call LOP-Win64-Shipping.exe+4003F30
LOP-Win64-Shipping.exe+E179F9E - 48 8B 7C 24 20        - mov rdi,[rsp+20]
LOP-Win64-Shipping.exe+E179FA3 - 48 89 05 8E7708F9     - mov [LOP-Win64-Shipping.exe+7201738],rax { (9C793740) }
LOP-Win64-Shipping.exe+E179FAA - 48 85 C0              - test rax,rax
LOP-Win64-Shipping.exe+E179FAD - 75 2C                 - jne LOP-Win64-Shipping.exe+E179FDB
LOP-Win64-Shipping.exe+E179FAF - E8 ACEABAF3           - call LOP-Win64-Shipping.exe+1D28A60
LOP-Win64-Shipping.exe+E179FB4 - E8 A7EABAF3           - call LOP-Win64-Shipping.exe+1D28A60
LOP-Win64-Shipping.exe+E179FB9 - 48 89 C3              - mov rbx,rax
LOP-Win64-Shipping.exe+E179FBC - 48 8B 80 18010000     - mov rax,[rax+00000118]
LOP-Win64-Shipping.exe+E179FC3 - 48 85 C0              - test rax,rax
LOP-Win64-Shipping.exe+E179FC6 - 75 13                 - jne LOP-Win64-Shipping.exe+E179FDB
LOP-Win64-Shipping.exe+E179FC8 - 48 8B 13              - mov rdx,[rbx]
LOP-Win64-Shipping.exe+E179FCB - 48 89 D9              - mov rcx,rbx
LOP-Win64-Shipping.exe+E179FCE - FF 92 A0030000        - call qword ptr [rdx+000003A0]
LOP-Win64-Shipping.exe+E179FD4 - 48 8B 83 18010000     - mov rax,[rbx+00000118]
LOP-Win64-Shipping.exe+E179FDB - 48 8B 5C 24 30        - mov rbx,[rsp+30]
LOP-Win64-Shipping.exe+E179FE0 - 48 83 C4 28           - add rsp,28 { 40 }
LOP-Win64-Shipping.exe+E179FE4 - C3                    - ret 
