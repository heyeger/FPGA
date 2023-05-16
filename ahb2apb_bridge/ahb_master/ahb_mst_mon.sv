 `ifndef __AHB_MST_MON
 `define __AHB_MST_MON
 
 class ahb_mst_mon extends uvm_monitor;
    
    `uvm_component_utils(ahb_mst_mon);
    
    uvm_analysis_port #(ahb_mst_trans) ap   ;
    ahb_mst_trans                      pkt  ;
    ahb_mst_if                         vif  ;

    function new(string name = "ahb_mst_mon", uvm_component parent);
        super.new(name, parent);
        ap = new("ap",this);
    endfunction: new
    
    function void build_phase(uvm_phase phase);
        /*  note: Do not call super.build_phase() from any class that is extended from an UVM base class!  */
        /*  For more information see UVM Cookbook v1800.2 p.503  */
        super.build_phase(phase);
        
        if(uvm_config_db#(virtual ahb_mst_trans)::get(this, "", "vif", vif))
            `uvm_fatal("No connect", "vif should be set!")
    endfunction: build_phase
    

    //  Function: run_phase
    extern virtual task run_phase(uvm_phase phase);

endclass

    task ahb_mst_mon::run_phase(uvm_phase phase);
        while(1)begin
            @(posedge vif.ahb_mst_mon_ckb)
            if(!vif.hresetn)begin
                pkt = null;
            end
            else begin
                if(vif.ahb_mst_mon_ckb.hready)begin
                    samp_addr_phase();
                end
                else begin
                end
            end

        end

    endtask: run_phase
    





 `endif
