module pow32(input  wire clk,
			  input  wire rst, 
			  input  wire ld,
			  output wire done,
			  input  wire [31:0] x, 
			  input  wire [31:0] e, 
			  output wire [31:0] y);

	reg [31:0]  ry;
	reg [31:0]  re;
	reg [7:0]   rcnt;
	reg [2:0]   state;

	reg [31:0] next_y;
	reg [31:0] next_e;
	reg [7:0]   next_cnt;
	reg [7:0]   next_state;

	localparam S0 = 0, S1 = 1, S2 = 2, S3 = 3;

	always @(posedge clk)
	begin
		if (rst == 1'd0)
		begin
			ry = 32'd0;
			re = 32'd0;
			rcnt = 8'd0;
			state = S0;
		end else begin
			ry    = next_y;
			re    = next_e;
			rcnt  = next_cnt; 
			state = next_state;  
		end
	end

	reg [31:0] mula, mulb, mulq;

	always @(*)
		mulq = mula * mulb;

	assign done = (rcnt == 8'd0) && (state == S3);
	assign y = ry;

	always @(*)
	begin
		next_y     = ry;
		next_e     = re;
		next_cnt   = rcnt;
		next_state = state;
		mula       = 32'd0;
		mulb       = 32'd0;
		case (state)
			S0: if (ld)
				begin
				next_y = 32'd1;
				next_e = e;
				next_cnt = 8'd31;
				next_state = S1;
				end

			S1 : begin // squaring
				 mula = ry; mulb = ry; next_y = mulq;
				 next_state = S2;
				 end

			S2 : begin // multiply
				 if (re[31] == 1'd1)
				 begin
					mula = ry; mulb = x; next_y = mulq;
				 end
				 next_e = {re[30:0], 1'b0};
				 next_state = S3;
			     end

			S3 : begin
				 next_cnt = rcnt - 8'd1;
				 if (rcnt == 8'd0)
				 	next_state = S0;
				 else
				 	next_state = S1;
			end
		endcase
	end

endmodule