#include "KBD.h"
.intel_syntax



.global _assemblyHandler

.text

_assemblyHandler:

begin:
mov ecx,STAT_REG
test ecx,STATUS_READY_OUT
jnz testError1 //test Parity error

testError1:
test ecx,PARITY
jnz  begin

testError2:
test ecx,TIMEOUT
jnz begin

in eax,KBD_OUT_BUF
ret

.end _assemblyHandler





