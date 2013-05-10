
TimerComponent = pc.components.Component('TimerComponent' ,
    {
        create:function (start_time, duration)
        {
            var n = this._super();
            n.config(start_time, duration);
            return n;
        }
    },
    {
        start_time:0,
        duration:0,

        init:function (start_time, duration)
        {
            this._super(this.Class.shortName);
            this.config(start_time, duration);
        },

        config:function (start_time, duration)
        {
            this.start_time = start_time;
            this.duration = duration;
        },

        getTimeLeft: function () {
            // helper : give us the time left
            return this.duration - (pc.device.now - this.start_time);
        }

    });

