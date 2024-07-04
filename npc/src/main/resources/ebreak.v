import "DPI-C" function int call_ebreak();

module ebreak_handler(
    input reg halt
);
    always @(*) begin
        if (halt) begin
            call_ebreak();
        end
    end
endmodule
