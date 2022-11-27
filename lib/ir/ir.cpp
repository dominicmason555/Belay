#include "ir.hpp"


void enqueue_ir(ir_ev_t ev, Queues& queues)
{
    queues.ir_q.events[queues.ir_q.head] = ev;
    queues.ir_q.head = (queues.ir_q.head + 1) % IR_Q_LEN;
}


void Ir::init()
{
    receiver.enableIRIn();
}


void Ir::tick(Queues& queues)
{
    if (receiver.decode(&results)) {
        if (results.value > 0) {
            Serial.print("IR code: ");
            Serial.println(results.value);
            switch (results.value) {
                case 16738455:
                    enqueue_ir(ir_ev_t::STAR, queues);
                    break;
                case 16756815:
                    enqueue_ir(ir_ev_t::CRUNCH, queues);
                    break;
            }
        }
    }
}