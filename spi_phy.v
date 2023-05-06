module apb_spi_phy(
    input  i_clk,
    input  i_rst_n,
    
    // apb slave interface  //AMBA 4.0
    input [31:0]  i_paddr,
    input         i_pwrite,
    input         i_psel,
    input         i_penable,
    input [31:0]  i_pwdata
    
    output        o_pready,
    output [31:0] o_prdata,
    output        o_pslverr,
    
    // spi interface
    output o_spi_csn,
    output o_spi_clk,
    output o_spi_ioe,
    input  i_spi_sdi,
    output o_spi_sdo
    );

parameter S_IDLE    = 4'b0001;
parameter S_SETUP   = 4'b0010;
parameter S_TRANSFER= 4'b0100;
parameter S_ACCESSS = 4'b1000;

reg [2:0] current_state;
reg [2:0] next_state;

always@(posedge i_clk or negedge i_rst_n)begin
    if(!i_rst_n)begin
        current_state <= S_IDLE;
    end
    else begin
        current_state <= next_state;
    end
end

always@(*)begin
    case(current_state)
        S_IDLE    : next_state =  ((i_psel == 1'b1)&&(i_penable == 1'b0))                    ?S_SETUP   :current_state;
        S_SETUP   : next_state =  ((i_psel == 1'b1)&&(i_penable == 1'b1)&&(o_pready == 1'b0))?S_TRANSFER:current_state;
        S_TRANSFER: next_state =  ((i_psel == 1'b1)&&(i_penable == 1'b1)&&(o_pready == 1'b1))?S_ACCESSS :current_state;
        S_ACCESSS : next_state =  ((i_psel == 1'b0)&&(i_penable == 1'b0)&&(o_pready == 1'b0))?S_IDLE    :current_state;
        default   : next_state =  S_IDLE;
    endcase
end

reg [5:0]counter;
reg [23:0] spi_parallel_data;

always@(posedge i_clk or negedge i_rst_n)begin
    if(!i_rst_n)begin
        counter <= 6'd0;
    end
    else if(current_state == S_TRANSFER)begin
        counter <= counter + 1'b1;
    end
    else begin
        counter <= 6'd0;
    end
end

always@(posedge i_clk or negedge i_rst_n)begin
    if(!i_rst_n)begin
        spi_parallel_data <= 24'd0;
    end
    else if(current_state == S_SETUP)begin
        spi_parallel_data <= {~i_pwrite,3'b0,i_paddr[11:0],i_pwdata[7:0]};
    end
    else if (counter[0])begin
        spi_parallel_data <= spi_parallel_data >> 1'b1;
    end
    else begin
        spi_parallel_data <= spi_parallel_data;
    end
end


assign o_spi_clk = counter[0];
assign o_spi_sdo = spi_parallel_data[0];
assign o_spi_csn = ~(current_state == S_TRANSFER);

assign o_pready = (counter == 6'd48)?1'b1:1'b0;



//spi write & read in AD3683
//4'b0000：cmd;12’d0:address;8'd:data;




endmodule
