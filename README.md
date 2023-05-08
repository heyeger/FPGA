 # FPGA
Record the learn in FPGA.

Be familiar with Github.

时序约束：
    建立时间：时钟到来之前数据应该保持稳定的时间；Tsu = Tclk - Thd.
    保持时间：时钟到来之后数据应该保持稳定的时间；Thd = Tco + Tlogic - Tskew.

    时序路径： 输入端口-第一级触发器；内部之间的触发器；末端触发器-输出端口；输入端口-输出端口。

verilog 语法：

    1. 有符号&无符号
        普通的十进制数，一律认定为有符号数；
        未声明长度的，一律按照32位长度处理；
        verilog里如果有符号数和无符号数做运算，会强制当作无符号运算；可以通过$signed()函数来避免这个问题；
    2. 状态机 
        moore型状态机；状态机的输出至于当前的状态有关；
        mealy型状态机；状态机的输出不仅与当前的状态有关，还与当前的输入有关；
        状态编码：二进制编码(Binary)、格雷码(Gray-code)编码、独热码(One-hot)编码；  格雷码：右移一位并与原输入按位异或；

仿真：
    bces: branch/condition/express/statement


