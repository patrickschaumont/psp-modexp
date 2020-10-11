module powtb;

	reg clk;
	reg rst;
	reg ld;
	reg [31:0] x;
	reg [31:0] e;
	wire [31:0] y;
	wire done;

	pow32 DUT(  .clk(clk),
				.rst(rst),
				.ld(ld),
				.done(done),
				.x(x),
				.e(e),
				.y(y));

	always
	begin
	clk = 1'd0;
	#25 clk = 1'd1;
	#25;
	end

	initial
	begin
	rst = 1'd0;
	@(posedge clk) ;
	rst = 1'd1;
	ld = 1'd0;
	x  = 32'hABCDEF;
	e  = 32'h654321;
	@(posedge clk) ;
	ld = 1'd1;	
	@(posedge clk) ;
	ld = 1'd0;	
	@(posedge done) ;
	$display("x %h", x);
	$display("e %h", e);
	$display("y %h", y);
	$finish;
	end

endmodule