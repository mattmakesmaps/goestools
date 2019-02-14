## `decoder` has a thread.

```
1953494096 decoder: queue_->popForRead()
1953494096 popForRead()
# decoder is the only thread that blocks
1953494096 popForRead(): BLOCKING (pushWrite() unblocks me)
[...]
# decoder is the only thread that unblocks
1953494096 popForRead(): UNBLOCKED
[...]
1953494096 decoder queue_->pushRead()
1953494096 pushRead(), notify_one
1953494096 decoder: queue_->popForRead()
1953494096 popForRead()
1953494096 popForRead(): BLOCKING (pushWrite() unblocks me)
[...]
1953494096 popForRead(): UNBLOCKED
```

## `rtlsource::handle` has a thread.

```
1963979856 rtlsdr_source::handle queue_->popForWrite()
1963979856 popForWrite()
1963979856 rtlsdr_source::handle queue_->pushWrite()
1963979856 pushWrite(), notify_one
[...]
1963979856 rtlsdr_source::handle queue_->popForWrite()
1963979856 popForWrite()
[...]
1963979856 rtlsdr_source::handle queue_->pushWrite()
1963979856 pushWrite(), notify_one
1963979856 rtlsdr_source::handle queue_->popForWrite()
1963979856 popForWrite()
1963979856 popForWrite(): write_.size(): 1 element_size: 2 capacity_size: 4
1963979856 rtlsdr_source::handle queue_->pushWrite()
1963979856 pushWrite(), notify_one
[...]
1963979856 rtlsdr_source::handle queue_->popForWrite()
1963979856 popForWrite()
1963979856 rtlsdr_source::handle queue_->pushWrite()
1963979856 pushWrite(), notify_one
1963979856 rtlsdr_source::handle queue_->popForWrite()
1963979856 popForWrite()
1963979856 rtlsdr_source::handle queue_->pushWrite()
1963979856 pushWrite(), notify_one
[...]
1963979856 rtlsdr_source::handle queue_->popForWrite()
1963979856 popForWrite()
## `rtlsource::handle` is the only thread that blocks `popForWrite()`
1963979856 popForWrite(): BLOCKING write_.size(): 0 element_size: 4 capacity_size: 4
```

## The `work()` methods operate in a thread as well.

```
1974113360 AGC qin->popForRead()
1974113360 popForRead()
1974113360 AGC qout->popForWrite()
1974113360 popForWrite()
1974113360 popForWrite(): write_.size(): 1 element_size: 1 capacity_size: 2
1974113360 AGC qin->pushRead()
1974113360 pushRead(), notify_one
1974113360 AGC qout->pushWrite()
1974113360 pushWrite(), notify_one
1974113360 costas: qin->pushRead()
1974113360 popForRead()
1974113360 costas: qout->popForWrite()
1974113360 popForWrite()
1974113360 popForWrite(): write_.size(): 1 element_size: 1 capacity_size: 2
[...]
1974113360 costas: qin->pushRead()
1974113360 pushRead(), notify_one
1974113360 costas: qout->pushWrite()
1974113360 pushWrite(), notify_one
1974113360 rrc: qin->popForRead()
1974113360 popForRead()
1974113360 rrc: qout->popForWrite()
1974113360 popForWrite()
1974113360 popForWrite(): write_.size(): 1 element_size: 1 capacity_size: 2
[...]
1974113360 rrc: qin->pushRead()
1974113360 pushRead(), notify_one
1974113360 rrc: qout->pushWrite()
1974113360 pushWrite(), notify_one
1974113360 clock_recovery: qin->popForRead()
1974113360 popForRead()
1974113360 clock_recovery: qout->popForWrite()
1974113360 popForWrite()
1974113360 popForWrite(): write_.size(): 1 element_size: 1 capacity_size: 2
1974113360 clock_recovery: qin->pushRead()
1974113360 pushRead(), notify_one
1974113360 clock_recovery: qout->pushWrite()
1974113360 pushWrite(), notify_one
1974113360 quantize: qin->popForRead()
1974113360 popForRead()
1974113360 quantize: qout->popForWrite()
1974113360 popForWrite()
1974113360 popForWrite(): write_.size(): 1 element_size: 1 capacity_size: 2
1974113360 quantize: qin->pushRead()
1974113360 pushRead(), notify_one
1974113360 quantize: qout->pushWrite()
1974113360 pushWrite(), notify_one
```