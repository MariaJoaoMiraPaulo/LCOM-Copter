#include "KBD.h"
.intel_syntax



.global _assemblyHandler

.text

_assemblyHandler:

begin:
mov ecx,STAT_REG     //read STAT_REG
test ecx,STATUS_READY_OUT
jnz testError1 //test Parity error

testError1:
test ecx,PARITY
jnz  begin

testError2:
test ecx,TIMEOUT //teste TIMEOUT error
jnz begin //starts again

in eax,KBD_OUT_BUF // read scancode in out_buf, returns eax
ret

.end _assemblyHandler





