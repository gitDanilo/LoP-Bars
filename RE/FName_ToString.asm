LOP-Win64-Shipping.exe+20BA610 - 48 89 5C 24 08        - mov [rsp+08],rbx
LOP-Win64-Shipping.exe+20BA615 - 48 89 6C 24 10        - mov [rsp+10],rbp
LOP-Win64-Shipping.exe+20BA61A - 48 89 74 24 18        - mov [rsp+18],rsi
LOP-Win64-Shipping.exe+20BA61F - 57                    - push rdi
LOP-Win64-Shipping.exe+20BA620 - 48 83 EC 20           - sub rsp,20 { 32 }
LOP-Win64-Shipping.exe+20BA624 - 48 8B DA              - mov rbx,rdx
LOP-Win64-Shipping.exe+20BA627 - 48 8B F1              - mov rsi,rcx
LOP-Win64-Shipping.exe+20BA62A - E8 81FFFFFF           - call LOP-Win64-Shipping.exe+20BA5B0
LOP-Win64-Shipping.exe+20BA62F - 44 8B 46 04           - mov r8d,[rsi+04]
LOP-Win64-Shipping.exe+20BA633 - 33 ED                 - xor ebp,ebp
LOP-Win64-Shipping.exe+20BA635 - 48 8B F8              - mov rdi,rax
LOP-Win64-Shipping.exe+20BA638 - 0FB7 10               - movzx edx,word ptr [rax]
LOP-Win64-Shipping.exe+20BA63B - C1 EA 06              - shr edx,06 { 6 }
LOP-Win64-Shipping.exe+20BA63E - 89 6B 08              - mov [rbx+08],ebp
LOP-Win64-Shipping.exe+20BA641 - 45 85 C0              - test r8d,r8d
LOP-Win64-Shipping.exe+20BA644 - 75 1A                 - jne LOP-Win64-Shipping.exe+20BA660
LOP-Win64-Shipping.exe+20BA646 - 39 53 0C              - cmp [rbx+0C],edx
LOP-Win64-Shipping.exe+20BA649 - 74 08                 - je LOP-Win64-Shipping.exe+20BA653
LOP-Win64-Shipping.exe+20BA64B - 48 8B CB              - mov rcx,rbx
LOP-Win64-Shipping.exe+20BA64E - E8 6D4DBFFE           - call LOP-Win64-Shipping.exe+CAF3C0
LOP-Win64-Shipping.exe+20BA653 - 48 8B D3              - mov rdx,rbx
LOP-Win64-Shipping.exe+20BA656 - 48 8B CF              - mov rcx,rdi
LOP-Win64-Shipping.exe+20BA659 - E8 E2EEFFFF           - call LOP-Win64-Shipping.exe+20B9540
LOP-Win64-Shipping.exe+20BA65E - EB 63                 - jmp LOP-Win64-Shipping.exe+20BA6C3
LOP-Win64-Shipping.exe+20BA660 - 83 C2 06              - add edx,06 { 6 }
LOP-Win64-Shipping.exe+20BA663 - 39 53 0C              - cmp [rbx+0C],edx
LOP-Win64-Shipping.exe+20BA666 - 74 08                 - je LOP-Win64-Shipping.exe+20BA670
LOP-Win64-Shipping.exe+20BA668 - 48 8B CB              - mov rcx,rbx
LOP-Win64-Shipping.exe+20BA66B - E8 504DBFFE           - call LOP-Win64-Shipping.exe+CAF3C0
LOP-Win64-Shipping.exe+20BA670 - 48 8B D3              - mov rdx,rbx
LOP-Win64-Shipping.exe+20BA673 - 48 8B CF              - mov rcx,rdi
LOP-Win64-Shipping.exe+20BA676 - E8 C5EEFFFF           - call LOP-Win64-Shipping.exe+20B9540
LOP-Win64-Shipping.exe+20BA67B - 8B 4B 08              - mov ecx,[rbx+08]
LOP-Win64-Shipping.exe+20BA67E - 8B C5                 - mov eax,ebp
LOP-Win64-Shipping.exe+20BA680 - 85 C9                 - test ecx,ecx
LOP-Win64-Shipping.exe+20BA682 - 0F9E C0               - setle al
LOP-Win64-Shipping.exe+20BA685 - 8D 79 FF              - lea edi,[rcx-01]
LOP-Win64-Shipping.exe+20BA688 - 0F4E FD               - cmovle edi,ebp
LOP-Win64-Shipping.exe+20BA68B - FF C0                 - inc eax
LOP-Win64-Shipping.exe+20BA68D - 03 C1                 - add eax,ecx
LOP-Win64-Shipping.exe+20BA68F - 89 43 08              - mov [rbx+08],eax
LOP-Win64-Shipping.exe+20BA692 - 3B 43 0C              - cmp eax,[rbx+0C]
LOP-Win64-Shipping.exe+20BA695 - 7E 08                 - jle LOP-Win64-Shipping.exe+20BA69F
LOP-Win64-Shipping.exe+20BA697 - 48 8B CB              - mov rcx,rbx
LOP-Win64-Shipping.exe+20BA69A - E8 E14DBFFE           - call LOP-Win64-Shipping.exe+CAF480
LOP-Win64-Shipping.exe+20BA69F - 48 8B 03              - mov rax,[rbx]
LOP-Win64-Shipping.exe+20BA6A2 - BA 5F000000           - mov edx,0000005F { 95 }
LOP-Win64-Shipping.exe+20BA6A7 - 48 63 CF              - movsxd  rcx,edi
LOP-Win64-Shipping.exe+20BA6AA - 66 89 14 48           - mov [rax+rcx*2],dx
LOP-Win64-Shipping.exe+20BA6AE - 48 8B 03              - mov rax,[rbx]
LOP-Win64-Shipping.exe+20BA6B1 - 66 89 6C 48 02        - mov [rax+rcx*2+02],bp
LOP-Win64-Shipping.exe+20BA6B6 - 48 8B CB              - mov rcx,rbx
LOP-Win64-Shipping.exe+20BA6B9 - 8B 56 04              - mov edx,[rsi+04]
LOP-Win64-Shipping.exe+20BA6BC - FF CA                 - dec edx
LOP-Win64-Shipping.exe+20BA6BE - E8 CD20ECFF           - call LOP-Win64-Shipping.exe+1F7C790
LOP-Win64-Shipping.exe+20BA6C3 - 48 8B 5C 24 30        - mov rbx,[rsp+30]
LOP-Win64-Shipping.exe+20BA6C8 - 48 8B 6C 24 38        - mov rbp,[rsp+38]
LOP-Win64-Shipping.exe+20BA6CD - 48 8B 74 24 40        - mov rsi,[rsp+40]
LOP-Win64-Shipping.exe+20BA6D2 - 48 83 C4 20           - add rsp,20 { 32 }
LOP-Win64-Shipping.exe+20BA6D6 - 5F                    - pop rdi
LOP-Win64-Shipping.exe+20BA6D7 - C3                    - ret 
