module apb_spi_phy(
  input  i_clk,
  input  i_rst_n,
  
  // apb slave interface
  input [15:0]  i_paddr,
  input         i_pwrite,
  input         i_psel,
  input         i_penable,
  input [15:0]  i_pwdata
  
  output        o_pready,
  output [15:0] o_prdata,
  output        o_pslverr,
  
  
  // spi interface
  output o_spi_csn,
  output o_spi_clk,
  output o_spi_ioe,
  input  i_spi_sdi,
  output o_spi_sdo
  );




endmodule
