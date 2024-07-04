
import "DPI-C" function int call_ebreak();
module ebreak(
    input reg halt
);
if(halt)
begin
    call_ebreak();
end
endmodule