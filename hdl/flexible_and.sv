// Flexible AND Gate
// =================
//
// The flexible AND gate is a simple HDL block that is sufficiently complex
// enough to demonstrate using Verilator and GTest as a simulation environment
// for HDL development
//
// Truth table:
//
// |    A/B     | Invert A/B | Flexed A/B |
// |------------|------------|------------|
// |     0      |     0      |     0      |
// |     0      |     1      |     1      |
// |     1      |     0      |     1      |
// |     1      |     1      |     0      |
//
// | Invert Y | Flexed A | Flexed B |    Y     |
// |----------|----------|----------|----------|
// |    0     |    0     |    0     |    0     |
// |    0     |    0     |    1     |    0     |
// |    0     |    1     |    0     |    0     |
// |    0     |    1     |    1     |    1     |
// |    1     |    0     |    0     |    1     |
// |    1     |    0     |    1     |    1     |
// |    1     |    1     |    0     |    1     |
// |    1     |    1     |    1     |    0     |
//

module flexible_and (
    input  logic        clock,
    input  logic        reset,

    // control signals
    input  logic        invert_a,
    input  logic        invert_b,
    input  logic        invert_y,

    // logic interface
    input  logic[7:0]   a,
    input  logic[7:0]   b,
    output logic[7:0]   y
);

logic[7:0] q_a;
logic[7:0] q_b;
logic q_invert_a;
logic q_invert_b;
logic q_invert_y;

logic[7:0] flexed_a;
logic[7:0] flexed_b;
logic[7:0] unflexed_y;
logic[7:0] comb_y;

assign flexed_a   = (q_invert_a) ? ~q_a : q_a;
assign flexed_b   = (q_invert_b) ? ~q_b : q_b;

// Break up the computation of Y into two parts. The first part is the actual
// AND'ing. The second part is the application of the inversion control signal.
assign unflexed_y = flexed_a & flexed_b;
assign comb_y     = (q_invert_y) ? ~unflexed_y : unflexed_y;

always_ff @ (posedge clock or posedge reset)
begin
    // input registers
    q_a        <= (reset) ? '0 : a;
    q_b        <= (reset) ? '0 : b;
    q_invert_a <= (reset) ? '0 : invert_a;
    q_invert_b <= (reset) ? '0 : invert_b;
    q_invert_y <= (reset) ? '0 : invert_y;

    // output registers
    y <= (reset) ? '0 : comb_y;
end

endmodule
