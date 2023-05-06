# FPGA
Record the learn in FPGA.

Be familiar with Github.

时序约束：
    建立时间：时钟到来之前数据应该保持稳定的时间；Tsu = Tclk - Thd.
    保持时间：时钟到来之后数据应该保持稳定的时间；Thd = Tco + Tlogic - Tskew.

    时序路径： 输入端口-第一级触发器；内部之间的触发器；末端触发器-输出端口；输入端口-输出端口。

verilog 语法：
    有符号&无符号
