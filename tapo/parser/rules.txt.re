condition head == 1
type DATA_UNAVAILABLE
detail "File begin stall."

condition cur_pkt_dir == 1 
type PACKET_DELAY
detail "stall as the ack packet delay."

condition rwnd < max_snd_seg_size
type ZERO_RWND
detail "Rwnd limited"

condition init_rwnd <= 4096 && outstanding <= 3*max_snd_seg_size
			&& cur_pkt_lost_num >=1 && cur_pkt_dir == 2 
			&& sacked_out > 0 && outstanding == (sacked_out + max_snd_seg_size) 
type RE_RECOVER_RETRANS_INIT_RWND_LIMITED
detail "re recover such retrans that the init_rwnd is small, just 4096."

condition init_rwnd <= 4096 && outstanding <= 3*max_snd_seg_size
			&& cur_pkt_lost_num >=1 && cur_pkt_dir == 2 
type RETRANS_INIT_RWND_LIMITED
detail "retrans that the init_rwnd is small, just 4096."

condition cur_pkt_lost_num >= 1 && tail == 1 && cur_pkt_dir == 2 &&
snd_nxt-cur_pkt_seq <= 3*max_snd_seg_size
type TAIL_RETRANS
detail "tail retrans."

condition cur_pkt_spurious_num + cur_pkt_lost_num == 0 && tail == 1
type CLIENT_IDLE
detail "Tail stall as the server send fin."

condition cur_pkt_lost_num >= 1 && cur_pkt_dir == 2
			&& outstanding <= 3*max_snd_seg_size && rwnd > 3*max_snd_seg_size
            && sacked_out > 0 && outstanding == (sacked_out + max_snd_seg_size) 
type RE_RECOVER_SMALL_RETRANS_CWND_LIMITED
detail "re recover the retrans that cwnd limited and init rwnd limited, last packet is in"

condition cur_pkt_lost_num >= 1 && cur_pkt_dir == 2
			&& outstanding <= 3*max_snd_seg_size && rwnd > 3*max_snd_seg_size
type SMALL_RETRANS_CWND_LIMITED_IN
detail "retrans that cwnd limited and init rwnd limited, last packet is in"

condition cur_pkt_lost_num >= 1 && cur_pkt_dir == 2
			&& outstanding <= 3*max_snd_seg_size && rwnd <= 3*max_snd_seg_size
            && sacked_out > 0 && outstanding == (sacked_out + max_snd_seg_size) 
type RE_RECOVER_SMALL_RETRANS_RWND_LIMITED
detail "re recover the retrans that rwnd limited and init rwnd limited"

condition cur_pkt_lost_num >= 1 && cur_pkt_dir == 2
			&& outstanding <= 3*max_snd_seg_size && rwnd <= 3*max_snd_seg_size
type SMALL_RETRANS_RWND_LIMITED
detail "retrans that rwnd limited and init rwnd limited"

condition cur_pkt_spurious_num + cur_pkt_lost_num >= 2 && cur_pkt_dir == 2
type RETRANS_DOUBLE
detail "retrans, because last retrans packet delay"

condition cur_pkt_spurious_num == 1 && cur_pkt_lost_num == 0 && cur_pkt_dir == 2
type RETRANS_ACK_DELAY
detail "retrans, because ack delay"

condition lost*max_snd_seg_size == outstanding &&  cur_pkt_dir == 2 && cur_pkt_spurious_num + cur_pkt_lost_num >= 1
type RETRANS_SERIES_RETRANS
detail "retrans, because series packets lost"

condition cur_pkt_dir == 2 && cur_pkt_spurious_num + cur_pkt_lost_num >= 1
type RETRANS_UNKNOWN
detail "retrans, unknown"

condition cur_pkt_dir == 2
type RESOURCE_CONSTRAINT
detail "resource constraint"

