`ifndef __AHB_MST_DRV
`define __AHB_MST_DRV


class ahb_mst_drv extends uvm_driver#(ahb_mst_trans);
    `uvm_component_utils(ahb_mst_drv);
    
    virtual ahb_mst_if vif;

    protected ahb_mst_trans pkt_addr_phase;
    protected ahb_mst_trans pkt_data_phase;

    //  Constructor: new
    function new(string name = "ahb_mst_drv", uvm_component parent);
        super.new(name, parent);
    endfunction: new

//  Function: build_phase
    function void ahb_mst_drv::build_phase(uvm_phase phase);
        /*  note: Do not call super.build_phase() from any class that is extended from an UVM base class!  */
        /*  For more information see UVM Cookbook v1800.2 p.503  */
        super.build_phase(phase);
        if(!uvm_config_db#(virtual ahb_mst_if)::get(this, "", "vif", vif))
            `uvm_fatal( "vif not connect", "located between testbench and ahb_mst_drv!")
    endfunction: build_phase
    
    
    extern virtual task run_phase(uvm_phase phase);
    extern virtual function void drv_one_pkt_addr_phase(ref ahb_mst_trans pkt);
    extern virtual function void drv_one_pkt_data_phase(ref ahb_mst_trans pkt);
    extern virtual function void drv_one_pkt_idle_state();
endclass: ahb_mst_drv
    
    task ahb_mst_drv::run_phase(uvm_phase phase);
        while(1) begin
            @(vif.ahb_mst_drv_ckb)
            if(!hresetn)begin
                vif.ahb_mst_drv_ckb.hsel    =   1'b0;
                vif.ahb_mst_drv_ckb.haddr   =   32'h0;
                vif.ahb_mst_drv_ckb.htrans  =   2'b0;
                vif.ahb_mst_drv_ckb.hsize   =   3'b0;
                vif.ahb_mst_drv_ckb.hburst  =   3'b0;
                vif.ahb_mst_drv_ckb.hport   =   4'b0;
                vif.ahb_mst_drv_ckb.hwrite  =   1'b0;
                vif.ahb_mst_drv_ckb.hwdata  =   32'h0;
            end
            else begin
                if(pkt_data_phase != null)begin
                    drv_one_pkt_data_phase(pkt_data_phase);
                end
                else if(vif.ahb_mst_drv_ckb.hready & ((vif.ahb_mst_drv_ckb.htrans == SINGLE)|(pkt_data_phase.is_last_beat())))begin
                    seq_item_port.item_done();
                    pkt_addr_phase = null;
                    pkt_data_phase = null;
                end

                if(pkt_addr_phase != null)begin
                    drv_one_pkt_addr_phase(pkt_addr_phase);
                end
                else begin
                    seq_item_port.try_next_item(pkt_addr_phase);
                    if(pkt_addr_phase != null)begin
                        drv_one_pkt_addr_phase(pkt_addr_phase);
                    end
                    else begin
                        drv_one_pkt_idle_state();
                    end
                end    
            end
        end
    endtask

    function ahb_mst_drv::drv_one_pkt_addr_phase(ref ahb_mst_trans pkt);
        vif.ahb_mst_drv_ckb.hsel    <=   pkt.hsel;
        vif.ahb_mst_drv_ckb.haddr   <=   ((pkt.htrans == SEQ)|(pkt.htrans == NSEQ))? pkt.next_haddr() :vif.haddr;
        vif.ahb_mst_drv_ckb.htrans  <=   pkt.next_htrans();
        vif.ahb_mst_drv_ckb.hsize   <=   pkt.hsize;
        vif.ahb_mst_drv_ckb.hburst  <=   pkt.hburst;
        vif.ahb_mst_drv_ckb.hport   <=   pkt.hprot;
        vif.ahb_mst_drv_ckb.hwrite  <=   pkt.hwrite;
    endfunction
    
    function ahb_mst_drv::drv_one_pkt_data_phase(ref ahb_mst_trans pkt);
        if(vif.ahb_mst_drv_ckb.hready)begin
            vif.ahb_mst_drv_ckb.hwdata <= pkt.hwrite ? pkt.next_hrwdata() : 32'h0 ;
        end
    endfunction

    function ahb_mst_drv::drv_one_pkt_idle_state();
        vif.ahb_mst_drv_ckb.hsel    <=   1'b0;
        vif.ahb_mst_drv_ckb.haddr   <=   32'h0;
        vif.ahb_mst_drv_ckb.htrans  <=   IDLE;
        vif.ahb_mst_drv_ckb.hsize   <=   BYTE;
        vif.ahb_mst_drv_ckb.hburst  <=   SINGLE;
        vif.ahb_mst_drv_ckb.hport   <=   4'h0;
        vif.ahb_mst_drv_ckb.hwrite  <=   1'b0;
    endfunction

`endif
