
import "DPI-C" function int call_ebreak();
module ebreak_handler(
    input reg halt
);
if(halt)
begin
    call_ebreak();
end
endmodule