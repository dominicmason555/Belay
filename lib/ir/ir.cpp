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
                case 16753245:
                    enqueue_ir(ir_ev_t::ONE, queues);
                    break;
                case 16736925:
                    enqueue_ir(ir_ev_t::TWO, queues);
                    break;
                case 16769565:
                    enqueue_ir(ir_ev_t::THREE, queues);
                    break;
                case 16720605:
                    enqueue_ir(ir_ev_t::FOUR, queues);
                    break;
                case 16712445:
                    enqueue_ir(ir_ev_t::FIVE, queues);
                    break;
                case 16761405:
                    enqueue_ir(ir_ev_t::SIX, queues);
                    break;
                case 16769055:
                    enqueue_ir(ir_ev_t::SEVEN, queues);
                    break;
                case 16754775:
                    enqueue_ir(ir_ev_t::EIGHT, queues);
                    break;
                case 16748655:
                    enqueue_ir(ir_ev_t::NINE, queues);
                    break;
                case 16738455:
                    enqueue_ir(ir_ev_t::STAR, queues);
                    break;
                case 16750695:
                    enqueue_ir(ir_ev_t::ZERO, queues);
                    break;
                case 16756815:
                    enqueue_ir(ir_ev_t::CRUNCH, queues);
                    break;
                case 16718055:
                    enqueue_ir(ir_ev_t::UP, queues);
                    break;
                case 16716015:
                    enqueue_ir(ir_ev_t::LEFT, queues);
                    break;
                case 16726215:
                    enqueue_ir(ir_ev_t::OK, queues);
                    break;
                case 16734885:
                    enqueue_ir(ir_ev_t::RIGHT, queues);
                    break;
                case 16730805:
                    enqueue_ir(ir_ev_t::DOWN, queues);
                    break;
            }
        }
    }
}