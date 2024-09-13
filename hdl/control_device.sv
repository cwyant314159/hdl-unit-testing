// A Sufficiently Complex Control Device
// =====================================
//
// The control device serves no real purpose other than to be a relatively
// complex device to run unit tests against. Data is strobed in via the task
// interface, and a result is strobed out per the definition below.
//
// A task word is a 32-bit value comprised of four (4) sections:
//  1. control bits (3-bits [31:29])
//  2. sequence number (13-bits [28:16])
//  3. operand A (8-bits [15:8])
//  4. operand B (8-bits [7:0])
//
// A result word is a 32-bit value comprised of four (4) sections:
//  1. control bits (3-bits [31:29])
//  2. sequence number (13-bits [28:16])
//  3. reserved bits (8-bits always 0 [15:8])
//  4. result (8-bits [7:0])
//
// The **control bits** are used to define what operations to perform with the
// task word's **A** and **B** operands. Result words will have the **result**
// field set to the operation's result. The control bits will be echo'ed in the
// control bits field of the response word.
//
// **Sequence numbers** are transparently passed from task word to result word
// for execution tracking.
//
// | Control Bits | Operation |
// |==============|===========|
// | 000          | A and B   |
// | 001          | A or  B   |
// | 010          | A xor B   |
// | 011          | not A     |
// | 100          | A nand B  |
// | 101          | A nor  B  |
// | 110          | A xnor B  |
// | 111          | not B     |
//
module control_device (
    input  logic       clock,
    input  logic       reset,
    input  logic       task_valid,
    input  logic[31:0] task_word,
    output logic       result_valid,
    output logic[31:0] result_word
);

typedef enum logic[2:0] {
    OP_AND   = 3'b000,
    OP_OR    = 3'b001,
    OP_XOR   = 3'b010,
    OP_NOT_A = 3'b011,
    OP_NAND  = 3'b100,
    OP_NOR   = 3'b101,
    OP_XNOR  = 3'b110,
    OP_NOT_B = 3'b111
} operation_t /*verilator public*/;

logic q_task_valid;

logic [2:0]  control_bits;
logic [12:0] sequence_num;
logic [7:0]  operand_a;
logic [7:0]  operand_b;

logic [7:0] operation_result;

logic        next_result_valid;
logic [31:0] next_result_word;

always_comb begin
    case(control_bits)
    OP_AND: operation_result = operand_a & operand_b;
    OP_OR:  operation_result = operand_a | operand_b;
    OP_XOR: operation_result = operand_a ^ operand_b;

    OP_NAND: operation_result = ~(operand_a & operand_b);
    OP_NOR:  operation_result = ~(operand_a | operand_b);
    OP_XNOR: operation_result = ~(operand_a ^ operand_b);

    OP_NOT_A: operation_result = ~operand_a;
    OP_NOT_B: operation_result = ~operand_b;
    endcase
end

assign next_result_valid       = q_task_valid;
assign next_result_word[31:29] = control_bits;
assign next_result_word[28:16] = sequence_num;
assign next_result_word[15:8]  = '0;
assign next_result_word[7:0]   = operation_result;

always_ff @ (posedge clock or posedge reset) begin
    result_valid <= (reset) ? '0 : next_result_valid;

    q_task_valid <= task_valid;
    control_bits <= task_word[31:29];
    sequence_num <= task_word[28:16];
    operand_a    <= task_word[15:8];
    operand_b    <= task_word[7:0];
    result_word  <= next_result_word;
end

endmodule
