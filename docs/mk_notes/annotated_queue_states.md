```
AGC: sourceQueue_->popForRead() pops an item from sourceQueue_.read_ 

                  AGC                costas                   RRC
                   +                    +                      +
                   |                    |                      |
              +----+------+       +-----+-----+          +-----+-----+
  sourceQueue_            agcQueue_           costasQueue_           rrcQueue_
read_     write_      read_     write_      read_     write_      read_     write_

AGC: agcQueue_->popForWrite() pops an item from agcQueue_.write_
write_.size(): 1 element_size: 1 capacity_size: 2

                  AGC                costas                   RRC
                   +                    +                      +
                   |                    |                      |
              +----+------+       +-----+-----+          +-----+-----+
  sourceQueue_            agcQueue_           costasQueue_           rrcQueue_
read_     write_      read_     write_      read_     write_      read_     write_

AGC: sourceQueue_->pushRead() adds an item to sourceQueue_.write_
pushRead() calls notify_one(), but no threads blocked.

                  AGC                costas                   RRC
                   +                    +                      +
                   |                    |                      |
              +----+------+       +-----+-----+          +-----+-----+
  sourceQueue_            agcQueue_           costasQueue_           rrcQueue_
read_     write_      read_     write_      read_     write_      read_     write_

AGC: agcQueue_->pushWrite() adds an item to agcQueue_.read_
pushWrite() calls notify_one(), but no threads blocked.

                  AGC                costas                   RRC
                   +                    +                      +
                   |                    |                      |
              +----+------+       +-----+-----+          +-----+-----+
  sourceQueue_            agcQueue_           costasQueue_           rrcQueue_
read_     write_      read_     write_      read_     write_      read_     write_

costas: agcQueue_->popForRead() pops an item from agcQueue_.read_

                  AGC                costas                   RRC
                   +                    +                      +
                   |                    |                      |
              +----+------+       +-----+-----+          +-----+-----+
  sourceQueue_            agcQueue_           costasQueue_           rrcQueue_
read_     write_      read_     write_      read_     write_      read_     write_

costas: costasQueue_->popForWrite() pops an item from costasQueue_.write_
write_.size(): 1 element_size: 1 capacity_size: 2

                  AGC                costas                   RRC
                   +                    +                      +
                   |                    |                      |
              +----+------+       +-----+-----+          +-----+-----+
  sourceQueue_            agcQueue_           costasQueue_           rrcQueue_
read_     write_      read_     write_      read_     write_      read_     write_

costas: agcQueue_->pushRead() adds an item to agcQueue_.write_
pushRead() calls notify_one(), but no threads blocked.

                  AGC                costas                   RRC
                   +                    +                      +
                   |                    |                      |
              +----+------+       +-----+-----+          +-----+-----+
  sourceQueue_            agcQueue_           costasQueue_           rrcQueue_
read_     write_      read_     write_      read_     write_      read_     write_

costas: costasQueue_->pushWrite() adds an item to costasQueue_.read_
pushWrite() calls notify_one(), but no threads blocked.

                  AGC                costas                   RRC
                   +                    +                      +
                   |                    |                      |
              +----+------+       +-----+-----+          +-----+-----+
  sourceQueue_            agcQueue_           costasQueue_           rrcQueue_
read_     write_      read_     write_      read_     write_      read_     write_

rrc: costasQueue_->popForRead() pops an item from costasQuee_.read_

                  AGC                costas                   RRC
                   +                    +                      +
                   |                    |                      |
              +----+------+       +-----+-----+          +-----+-----+
  sourceQueue_            agcQueue_           costasQueue_           rrcQueue_
read_     write_      read_     write_      read_     write_      read_     write_

rrc: rrcQueue_->popForWrite() pops an item from rrcQueue_.write_
write_.size(): 1 element_size: 1 capacity_size: 2

                  AGC                costas                   RRC
                   +                    +                      +
                   |                    |                      |
              +----+------+       +-----+-----+          +-----+-----+
  sourceQueue_            agcQueue_           costasQueue_           rrcQueue_
read_     write_      read_     write_      read_     write_      read_     write_

rrc: costasQueue_->pushRead() adds an item to costasQueue_.write_
pushRead() calls notify_one(), but no threads blocked.

                  AGC                costas                   RRC
                   +                    +                      +
                   |                    |                      |
              +----+------+       +-----+-----+          +-----+-----+
  sourceQueue_            agcQueue_           costasQueue_           rrcQueue_
read_     write_      read_     write_      read_     write_      read_     write_

rrc: rrcQueue->pushWrite() adds an item to rrcQueue_.read_
pushWrite() calls notify_one(), but no threads blocked.

                  AGC                costas                   RRC
                   +                    +                      +
                   |                    |                      |
              +----+------+       +-----+-----+          +-----+-----+
  sourceQueue_            agcQueue_           costasQueue_           rrcQueue_
read_     write_      read_     write_      read_     write_      read_     write_

```
