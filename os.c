struct bridge {     
     int north_waiting;
     int north_crossing; 
     int north_consecutive;    
     int south_waiting;     
     int south_crossing;     
     int south_consecutive;     
     struct lock lock;     
     struct condition northbound_done;     
     struct condition southbound_done; 
     }

void bridge_init(struct bridge *b)
    { 
       b->north_waiting = 0;
       b->north_crossing = 0;   
       b->north_consecutive = 0;     
       b->south_waiting = 0;     
       b->south_crossing = 0     
       b->south_consecutive = 0;     
       lock_init(&b->lock);     
       cond_init(&b->northbound_done);     
       cond_init(&b->southbound_done); 
    } 

int bridge_arrive_north(struct bridge *b)
    {     
       lock_acquire(&b->lock);     
       b->north_waiting++;     
       while ((b->south_crossing > 0) || 
       ((b->south_waiting > 0) && (b->northConsecutive >= 5)) {         
       cond_wait(&b->southbound_done, &b->lock);    
        }     
       b->north_waiting--;     
       b->north_crossing++;     
       b->northConsecutive++;     
       b->southConsecutive = 0;     
       lock_release(&b->lock); 
    }

int bridge_leave_north(struct bridge *b) 
    {     
       lock_acquire(&b->lock);     
       b->north_crossing--;     
       if (b->north_crossing == 0) {         
          cond_broadcast(&b->northbound_done, &b->lock);     
       }     
       lock_release(&b->lock); 
    }


    //Additional working space for Problem 5, if needed.  


int bridge_arrive_south(struct bridge *b)
    {     
       lock_acquire(&b->lock);     
       b->south_waiting++;     
       while ((b->north_crossing > 0) ||             
              ((b->north_waiting > 0) && (b->southConsecutive >= 5)) {         
           cond_wait(&b->northbound_done, &b->lock); 
       }     
       b->south_waiting--;     
       b->south_crossing++;     
       b->southConsecutive++;     
       b->northConsecutive = 0;     
       lock_release(&b->lock); 
    }  

int bridge_leave_south(struct bridge *b) 
    {
         lock_acquire(&b->lock);     
         b->south_crossing--;     
         if (b->south_crossing == 0) {         
            cond_broadcast(&b->southbound_done, &b->lock);     
         }     
         lock_release(&b->lock); 
    }