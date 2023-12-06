LOP-Win64-Shipping.exe+DB60E4B - 0F1F 44 00 00         - nop dword ptr [rax+rax+00]
LOP-Win64-Shipping.exe+DB60E50 - 48 89 5C 24 08        - mov [rsp+08],rbx { LOCKON OBJ REF = RDX }
LOP-Win64-Shipping.exe+DB60E55 - 57                    - push rdi
LOP-Win64-Shipping.exe+DB60E56 - 48 83 EC 20           - sub rsp,20 { 32 }
LOP-Win64-Shipping.exe+DB60E5A - 48 89 D7              - mov rdi,rdx
LOP-Win64-Shipping.exe+DB60E5D - 48 89 CB              - mov rbx,rcx
LOP-Win64-Shipping.exe+DB60E60 - 48 85 D2              - test rdx,rdx
LOP-Win64-Shipping.exe+DB60E63 - 0F84 86000000         - je LOP-Win64-Shipping.exe+DB60EEF
LOP-Win64-Shipping.exe+DB60E69 - E8 32C215F4           - call LOP-Win64-Shipping.exe+1CBD0A0
LOP-Win64-Shipping.exe+DB60E6E - 48 8B 57 10           - mov rdx,[rdi+10]
LOP-Win64-Shipping.exe+DB60E72 - 4C 8D 40 30           - lea r8,[rax+30]
LOP-Win64-Shipping.exe+DB60E76 - 48 63 40 38           - movsxd  rax,dword ptr [rax+38]
LOP-Win64-Shipping.exe+DB60E7A - 3B 42 38              - cmp eax,[rdx+38]
LOP-Win64-Shipping.exe+DB60E7D - 7F 2C                 - jg LOP-Win64-Shipping.exe+DB60EAB
LOP-Win64-Shipping.exe+DB60E7F - 48 89 C1              - mov rcx,rax
LOP-Win64-Shipping.exe+DB60E82 - 48 8B 42 30           - mov rax,[rdx+30]
LOP-Win64-Shipping.exe+DB60E86 - 4C 39 04 C8           - cmp [rax+rcx*8],r8
LOP-Win64-Shipping.exe+DB60E8A - 75 1F                 - jne LOP-Win64-Shipping.exe+DB60EAB
LOP-Win64-Shipping.exe+DB60E8C - 48 89 BB 98000000     - mov [rbx+00000098],rdi
LOP-Win64-Shipping.exe+DB60E93 - 66 8B 3D D9C73E0A     - mov di,[LOP-Win64-Shipping.exe+17F4D673] { (47) }
LOP-Win64-Shipping.exe+DB60E9A - 21 3D ED118C09        - and [LOP-Win64-Shipping.exe+1742208D],edi { (10) }
LOP-Win64-Shipping.exe+DB60EA0 - 48 8B 5C 24 30        - mov rbx,[rsp+30]
LOP-Win64-Shipping.exe+DB60EA5 - 48 83 C4 20           - add rsp,20 { 32 }
LOP-Win64-Shipping.exe+DB60EA9 - 5F                    - pop rdi
LOP-Win64-Shipping.exe+DB60EAA - C3                    - ret 
LOP-Win64-Shipping.exe+DB60EAB - 48 C7 83 98000000 00000000 - mov qword ptr [rbx+00000098],00000000 { 0 }
LOP-Win64-Shipping.exe+DB60EB6 - E8 E5C115F4           - call LOP-Win64-Shipping.exe+1CBD0A0
LOP-Win64-Shipping.exe+DB60EBB - 48 89 C7              - mov rdi,rax
LOP-Win64-Shipping.exe+DB60EBE - 48 8B 80 18010000     - mov rax,[rax+00000118]
LOP-Win64-Shipping.exe+DB60EC5 - 48 85 C0              - test rax,rax
LOP-Win64-Shipping.exe+DB60EC8 - 75 13                 - jne LOP-Win64-Shipping.exe+DB60EDD
LOP-Win64-Shipping.exe+DB60ECA - 48 8B 17              - mov rdx,[rdi]
LOP-Win64-Shipping.exe+DB60ECD - 48 89 F9              - mov rcx,rdi
LOP-Win64-Shipping.exe+DB60ED0 - FF 92 A0030000        - call qword ptr [rdx+000003A0]
LOP-Win64-Shipping.exe+DB60ED6 - 48 8B 87 18010000     - mov rax,[rdi+00000118]
LOP-Win64-Shipping.exe+DB60EDD - 48 89 83 98000000     - mov [rbx+00000098],rax
LOP-Win64-Shipping.exe+DB60EE4 - 48 8B 5C 24 30        - mov rbx,[rsp+30]
LOP-Win64-Shipping.exe+DB60EE9 - 48 83 C4 20           - add rsp,20 { 32 }
LOP-Win64-Shipping.exe+DB60EED - 5F                    - pop rdi
LOP-Win64-Shipping.exe+DB60EEE - C3                    - ret 
