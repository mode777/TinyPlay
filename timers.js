var _timeouts_ = {}
var _timeout_ctr_ = 0

function setTimeout(cb, ms){
    var ctr = _timeout_ctr_++
    _timeouts_[ctr] = [ticks()+ms,cb]
    return ctr
}

function _run_timers_(){
    var t = ticks()
    for (var key in _timeouts_) {
        var to = _timeouts_[key]
        if(to[0] <= t){
            delete _timeouts_[key]
            to[1]()
        }
    }
}